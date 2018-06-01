#pragma once

#include "core.pb.h"
#include "nano.h"

namespace nano {
namespace api {

/** A session between the client and a Nano node */
class nano_session
{
public:
    nano_session(std::string connection);
    ~nano_session();
    inline bool is_connected () { return session != nullptr; }
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

    int query (nano::api::QueryType type, std::string query, std::string & response);

private:
    void* session = nullptr;
};

}}//ns