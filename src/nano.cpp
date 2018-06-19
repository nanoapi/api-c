#include "nano.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/endian/conversion.hpp>
#include <google/protobuf/util/json_util.h>

using boost::asio::ip::tcp;
#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
    using boost::asio::local::stream_protocol;
#endif
static int NANO_API_PROTOCOL_VERSION = 1;

enum class session_type {tcp, domain, shared};

struct nano_session
{
    session_type type;
    virtual ~nano_session() = default;
    virtual int write (void* buffer, size_t len) { return 1; }
    virtual int read (void* buffer, size_t len) { return 1; }
    
    int last_error = 0;
    std::string last_error_string {""};
    std::string last_error_category {""};
    std::mutex session_mutex;
};

struct nano_session_tcp : public nano_session
{
    nano_session_tcp () : socket (io_context)
    {}

    ~nano_session_tcp() override
    {
        socket.close();
    }

    void connect (std::string host, std::string port)
    {
        tcp::resolver resolver(io_context);
        tcp::resolver::query query(host.c_str(), port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::connect(socket, endpoint_iterator); 
    }

    int write (void* buffer, size_t len) override
    { 
        try
        {
            boost::asio::write (socket, boost::asio::buffer(buffer, len));
        }
        catch (boost::system::system_error const & ex)
        {
            return 1;
        }
        
        return 0;
    }

    int read (void* buffer, size_t len) override
    {        
        try
        {
            boost::asio::read (socket, boost::asio::buffer(buffer, len));
        }
        catch (boost::system::system_error const & ex)
        {
            return 1;
        }

        return 0;
    }

    boost::asio::io_context io_context;
    tcp::socket socket;
};

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
struct nano_session_domain : public nano_session
{
    nano_session_domain () : socket (io_context)
    {}

    ~nano_session_domain()
    {
        socket.close();
    }

    void connect (std::string path)
    {
        socket.connect(stream_protocol::endpoint(path));
    }

    int write (void* buffer, size_t len) override
    { 
        try
        {
            boost::asio::write (socket, boost::asio::buffer(buffer, len));
        }
        catch (boost::system::system_error const & ex)
        {
            return 1;
        }
        
        return 0;
    }

    int read (void* buffer, size_t len) override
    {        
        try
        {
            boost::asio::read (socket, boost::asio::buffer(buffer, len));
        }
        catch (boost::system::system_error const & ex)
        {
            return 1;
        }

        return 0;
    }

    boost::asio::io_context io_context;
    stream_protocol::socket socket;
};
#else
    struct nano_session_domain : public nano_session 
    {
    };
#endif

struct nano_session_sharedmem
{};

static struct nano_session* nano_connect_tcp (std::string host, std::string port)
{
    nano_session_tcp* session = new nano_session_tcp();
    session->connect(host, port);
    return session;
}

static struct nano_session* nano_connect_domain (std::string path)
{
#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)  
    nano_session_domain* session = new nano_session_domain();
    session->connect(path);
    return session;
#else
    return nullptr;
#endif
}

struct nano_session* nano_connect (const char* connection)
{
    nano_session* session = nullptr;
    if (connection)
    {
        // std::cout << "connecting to " << connection << std::endl;

        std::string conn (connection);
        if (boost::starts_with(connection, "tcp://"))
        {
            std::string url = conn.substr(6, std::string::npos);
            std::vector<std::string> parts;
            boost::split(parts, url, boost::is_any_of(":"));
            if (parts.size() == 2)
            {
                session = nano_connect_tcp (parts[0], parts[1]);
            }            
        }
        else if (boost::starts_with(connection, "local://"))
        {
            std::string path = conn.substr(8, std::string::npos);
            session = nano_connect_domain (path);
        }
        else
        {
            return nullptr;
        }        
    }

    return session;
}

int nano_last_error (struct nano_session* session)
{
    std::lock_guard<std::mutex> lock(session->session_mutex);
    int err = session->last_error;
    return err;
}

const char* nano_last_error_string (struct nano_session* session)
{
    std::lock_guard<std::mutex> lock(session->session_mutex);
    std::string err = session->last_error_string;
    return err.c_str();
}

const char* nano_last_error_category (struct nano_session* session)
{
    std::lock_guard<std::mutex> lock(session->session_mutex);
    std::string err = session->last_error_category;
    return err.c_str();
}

void nano_last_error_clear (struct nano_session* session)
{
    std::lock_guard<std::mutex> lock(session->session_mutex);
    session->last_error_string = "";
    session->last_error_category = "";
    session->last_error = 0;
}

int nano_disconnect (struct nano_session* session)
{
    nano_last_error_clear (session);
    std::lock_guard<std::mutex> lock(session->session_mutex);
    delete session;
    return 0;
}

int nano_request (struct nano_session* session, RequestType type, void* request, size_t request_size, void** response, size_t* response_size)
{
    nano_last_error_clear (session);
    std::lock_guard<std::mutex> lock(session->session_mutex);

    // Write preamble
    uint8_t preamble[4] { PREAMBLE_1, PREAMBLE_2, PREAMBLE_VERSION_MAJOR, PREAMBLE_VERSION_MINOR };
    session->write(preamble, 4);

    int result_code = 0;
    Request request_header;
    request__init (&request_header);
    request_header.type = type;

    // Pack and write header
    uint32_t len = (uint32_t)request__get_packed_size (&request_header);
    void* buf = (void*) malloc (len); 
    request__pack (&request_header, (uint8_t*)buf);
    
    uint32_t network_len = boost::endian::native_to_big ((uint32_t) len);
    session->write(&network_len,4);
    session->write(buf,len);
    free(buf);

    // Write request
    network_len = boost::endian::native_to_big ((uint32_t) request_size);
    session->write(&network_len, 4);
    session->write(request, request_size);

    // Read response
    session->read(&len, 4);
    boost::endian::big_to_native_inplace (len);
    buf = (void*) malloc(len);
    if (!session->read(buf, len))
    {
        Response* response_header = response__unpack (NULL, len, (const uint8_t*)buf);
        free(buf);
        if (response_header == nullptr)
        {
            session->last_error = 1;
            session->last_error_string = "Could not parse response";
            result_code = 1;
        }
        else if (response_header->error_code != 0 || response_header->type != type)
        {
            if (response_header->error_message)
            {
                session->last_error_string = std::string(response_header->error_message);
            }
            session->last_error = response_header->error_code;
            session->last_error_category = response_header->error_category;
            result_code = 1;
        }
        else
        {
            session->read(&len, 4);
            boost::endian::big_to_native_inplace (len);
            // Caller frees output parameters
            *response = (void*) malloc(len);
            session->read(*response, len);
            *response_size = len;
        }

        if (response_header)
        {
            response__free_unpacked(response_header, NULL);
        }
    }
    else
    {
        session->last_error_string = "Could not read from node";
        session->last_error = 1;
        result_code = 1;
    }
    return result_code;
}

nano::api::nano_session::nano_session(std::string connection)
{
    this->session = nano_connect (connection.c_str());
}
nano::api::nano_session::~nano_session()
{
    if (this->session)
    {
        nano_disconnect (static_cast<::nano_session*>(this->session));
    }
}

int nano::api::nano_session::request (nano::api::RequestType type, std::string request, std::string & response)
{
    void* buf;
    size_t buf_size;
    int res = nano_request (static_cast<::nano_session*>(this->session), (::RequestType)type, (void*)request.data(), request.size(), &buf, &buf_size);
    if (!res)
    {
        response = std::string (static_cast<char*>(buf), buf_size);
        free(buf);
    }

    return res;
}

int nano::api::nano_session::to_json (google::protobuf::Message & message, std::string & json_output)
{
    auto result = google::protobuf::util::MessageToJsonString(message, &json_output);
    return result.ok();
}

int nano::api::nano_session::from_json (google::protobuf::Message & message, std::string json_input)
{
    google::protobuf::util::JsonParseOptions parse_options;
    auto result = google::protobuf::util::JsonStringToMessage(json_input, &message, parse_options);
    return result.ok();
}

int nano::api::nano_session::last_error ()
{
    return static_cast<::nano_session*>(this->session)->last_error;
}

std::string nano::api::nano_session::last_error_string ()
{
    return static_cast<::nano_session*>(this->session)->last_error_string;
}

std::string nano::api::nano_session::last_error_category ()
{
    return static_cast<::nano_session*>(this->session)->last_error_category;
}

void nano::api::nano_session::last_error_clear ()
{
    nano_last_error_clear (static_cast<::nano_session*>(this->session));
}

void nano::api::nano_session::last_error_set (int error_code, std::string description)
{
    auto session = static_cast<::nano_session*>(this->session);
    session->last_error = error_code;
    session->last_error_string = description;
}