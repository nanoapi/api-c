#pragma once

#include "core.pb.h"
#include "accounts.pb.h"
#include "util.pb.h"
#include "nano.h"
#include <algorithm>

namespace nano {
namespace api {

/** A session between the client and a Nano node */
class nano_session
{
public:
    /**
     * Construct a session using the supplied connection string
     * @param connection A 'tcp://' or 'local://' connection string
     */
    nano_session(std::string connection);

    /**
     * Closes the connection
     */
    ~nano_session();

    /** Returns true if connected to the node */
    inline bool is_connected () { return session != nullptr; }

    /**
     * Send a request. The request type is derived from the request message.
     * @param request_a Request message
     * @param response_a Response output message
     * @returns 0 on success. Otherwise, call last_error(_string) for more information.
     */
    template <typename REQUEST_TYPE, typename RESPONSE_TYPE>
    int request (REQUEST_TYPE const & request_a, RESPONSE_TYPE & response_a)
    {
        int res = 0;
        assert (request_a.descriptor() && request_a.descriptor()->name().size() > 4);
        auto request_name_enum = request_a.descriptor()->name();
        request_name_enum = request_name_enum.substr(4, std::string::npos);
        std::transform(request_name_enum.begin(), request_name_enum.end(),request_name_enum.begin(), ::toupper);

        nano::api::RequestType qt;
        if (nano::api::RequestType_Parse(request_name_enum, &qt))
        {
            res = request(qt, request_a, response_a);
        }
        else
        {
            last_error_set (1, std::string("No matching request type found: ") + request_name_enum);
        }
        return res;
    }

    /** 
     * Send a request with the type specified manually. This is slighty faster than letting the API figure out the type.
     * @param type Request type
     * @param request_a Request message
     * @param response_a Response output message
     * @returns 0 on success. Otherwise, call last_error(_string) for more information.
     */
    template <typename REQUEST_TYPE, typename RESPONSE_TYPE>
    int request (nano::api::RequestType type, REQUEST_TYPE const & request_a, RESPONSE_TYPE & response_a)
    {
        std::string msg = request_a.SerializeAsString ();
        std::string result;

        int res = request (type, msg, result);
        if (!res)
        {
            response_a = RESPONSE_TYPE();
            response_a.ParseFromString (result);
        }

        return res;
    }

    /** 
     * Send request to the node using raw buffers
     * @param type Request type
     * @param request Request buffer
     * @param response_a Response output buffer
     * @returns 0 on success. Otherwise, call last_error(_string) for more information.
     */
    int request (nano::api::RequestType type, std::string request, std::string & response);

    int to_json (google::protobuf::Message & message, std::string & json_output);
    int from_json (google::protobuf::Message & message, std::string json_input);

    /**
     * Get most recent error code
     * @returns The last error or 0 if there is no error.
     */
    int last_error ();

    /**
     * Get string representation of the most recent error code
     * @returns The string representation of the last error, or an empty string if there is no string mapping available or
     * there is no error.
     */
    std::string last_error_string ();

    /**
     * Returns the category of the last error, or an empty string if there is no category mapping available or
     * there is no current error state.
     * @returns The error category or an empty string.
     */
    std::string last_error_category ();

    /**
     * Clears the error state. 
     */
    void last_error_clear ();

private:
    /** Update current error state */
    void last_error_set (int error_code, std::string description);

    /** Session state */
    void* session = nullptr;
};

}}//ns