#pragma once

#include "core.pb.h"
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
     * Query the node. The query type is derived from the query message.
     * @param query_a Query message
     * @param response_a Response output message
     * @returns 0 on success. Otherwise, call last_error(_string) for more information.
     */
    template <typename QUERY_TYPE, typename RESPONSE_TYPE>
    int query (QUERY_TYPE const & query_a, RESPONSE_TYPE & response_a)
    {
        int res = 0;
        assert (query_a.descriptor() && query_a.descriptor()->name().size() > 6);
        auto query_name_enum = query_a.descriptor()->name();
        query_name_enum = query_name_enum.substr(6, std::string::npos);
        std::transform(query_name_enum.begin(), query_name_enum.end(),query_name_enum.begin(), ::toupper);

        nano::api::QueryType qt;
        if (nano::api::QueryType_Parse(query_name_enum, &qt))
        {
            res = query(qt, query_a, response_a);
        }
        else
        {
            last_error_set (1, std::string("No matching query type found: ") + query_name_enum);
        }
        return res;
    }

    /** 
     * Query the node
     * @param type Query type
     * @param query_a Query message
     * @param response_a Response output message
     * @returns 0 on success. Otherwise, call last_error(_string) for more information.
     */
    template <typename QUERY_TYPE, typename RESPONSE_TYPE>
    int query (nano::api::QueryType type, QUERY_TYPE const & query_a, RESPONSE_TYPE & response_a)
    {
        std::string msg = query_a.SerializeAsString ();
        std::string result;

        int res = query (nano::api::QueryType::ACCOUNT_PENDING, msg, result);
        if (!res)
        {
            response_a = RESPONSE_TYPE();
            response_a.ParseFromString (result);
        }

        return res;
    }

    /** 
     * Query the node using raw buffers
     * @param type Query type
     * @param query_a Query buffer
     * @param response_a Response output buffer
     * @returns 0 on success. Otherwise, call last_error(_string) for more information.
     */
    int query (nano::api::QueryType type, std::string query, std::string & response);

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