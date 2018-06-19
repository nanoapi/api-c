#include "nano.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    const char* connection = argc > 1 ? argv[1] : "local:///tmp/nano";
    nano::api::nano_session session (connection);
    if (session.is_connected())
    {
        // Get pending blocks
        nano::api::req_account_pending request;
        request.mutable_threshold()->set_value("1000000000000000000000000");
        request.set_count(10);
        request.set_source(true);
        request.add_accounts ("xrb_1111111111111111111111111111111111111111111111111111hifc8npp");
        request.add_accounts ("xrb_3t6k35gi95xu6tergt6p69ck76ogmitsa8mnijtpxm9fkcm736xtoncuohr3");

        nano::api::res_account_pending pending;
        if (!session.request(request, pending))
        {
            if (pending.pending_size() > 0)
            {
                std::cout << "First account in reply: " << pending.pending (0).account () << std::endl;

                // Test JSON roundtrip
                std::string json_out;
                session.to_json(pending, json_out);
                std::cout << "JSON:\n" << json_out << std::endl; 
                nano::api::res_account_pending pending_parsed;  
                session.from_json(pending_parsed, json_out);    
                std::cout << "First account in parsed json: " << pending_parsed.pending (0).account () << std::endl;
            }
            else
            {
                std::cout << "No pending accounts" << std::endl;
            }
        }
        else
        {
            std::cerr << "Request failed: " << session.last_error_string() << std::endl;
        }     
    }
    else
    {
        std::cerr << "Could not connect. Make sure the server is running and that the transport is supported" << std::endl;
    }
    return 0;
}
