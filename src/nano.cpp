#include "core.pb-c.h"
#include "nano.h"
#include <iostream>
#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/endian/conversion.hpp>

using boost::asio::ip::tcp;
using boost::asio::local::stream_protocol;

static int CLIENT_VERSION = 1;

enum class session_type {tcp, domain, shared};

struct nano_session
{
    session_type type; 
    virtual ~nano_session() = default;
    virtual int write (void* buffer, size_t len) { return 1; }
    virtual int read (void* buffer, size_t len) { return 1; }
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

struct nano_session_sharedmem
{};

static struct nano_session_tcp* nano_connect_tcp (std::string host, std::string port)
{
    nano_session_tcp* session = new nano_session_tcp();
    session->connect(host, port);
    return session;
}

static struct nano_session_domain* nano_connect_domain (std::string path)
{
    nano_session_domain* session = new nano_session_domain();
    session->connect(path);
    return session;
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
                session = static_cast<nano_session*> (nano_connect_tcp (parts[0], parts[1]));
            }            
        }
        else if (boost::starts_with(connection, "local://"))
        {
            std::string path = conn.substr(8, std::string::npos);
            session = static_cast<nano_session*> (nano_connect_domain (path));
        }
        else
        {
            return nullptr;
        }        
    }

    return session;
}

int nano_disconnect (struct nano_session* session)
{
    delete session;
    return 0;
}

int nano_query (struct nano_session* session, QueryType type, void* query, size_t query_size, void** response, size_t* response_size)
{
    int result_code = 0;
    Query query_header;
    query__init (&query_header);
    query_header.type = type;

    // Pack and write header
    uint32_t len = (uint32_t)query__get_packed_size (&query_header);
    void* buf = (void*) malloc (len); 
    query__pack (&query_header, (uint8_t*)buf);
    
    uint32_t network_len = boost::endian::native_to_big ((uint32_t) len);
    session->write(&network_len,4);
    session->write(buf,len);
    free(buf);

    // Write query
    network_len = boost::endian::native_to_big ((uint32_t) query_size);
    session->write(&network_len, 4);
    session->write(query, query_size);

    // Read response
    session->read(&len, 4);
    boost::endian::big_to_native_inplace (len);
    buf = (void*) malloc(len);
    if (!session->read(buf, len))
    {
        Response* response_header = response__unpack (NULL, len, (const uint8_t*)buf);
        free(buf);
        if (response_header->result != RESULT__OK || response_header->type != type)
        {
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
        response__free_unpacked(response_header, NULL);
    }
    else
    {
        std::cerr << "Could not read" << std::endl;
        result_code = 1;
    }
    return result_code;
}
