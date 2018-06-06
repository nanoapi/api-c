#pragma once

#include "core.pb.h"
#include "nano.h"

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
     * Query the node
     * @param type Query type
     * @param query_a Query message
     * @param response_a Response output message
     */
    template <typename QUERY_TYPE, typename RESPONSE_TYPE>
    int query (nano::api::QueryType type, QUERY_TYPE query_a, RESPONSE_TYPE & response_a)
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
     */
    int query (nano::api::QueryType type, std::string query, std::string & response);

private:
    void* session = nullptr;
};

}}//ns