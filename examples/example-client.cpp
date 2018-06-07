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
        nano::api::query_account_pending query;
        query.mutable_threshold()->set_value("200");
        query.add_accounts ("xrb_26u1uufyoig8777y6r8iqjtrw8sg8maqrm36zzcm95jmbd9i9aj5i8abr8u5");
        query.add_accounts ("xrb_3dcfozsmekr1tr9skf1oa5wbgmxt81qepfdnt7zicq5x3hk65fg4fqj58mbr");

        nano::api::res_account_pending pending;
        if (!session.query(nano::api::QueryType::ACCOUNT_PENDING, query, pending))
        {
            std::cout << "First account in reply: " << pending.pending (0).account () << std::endl;
        }

        std::string json_out;
        session.to_json(pending, json_out);
        std::cout << "JSON:\n" << json_out << std::endl; 
        nano::api::res_account_pending pending_parsed;  
        session.from_json(pending_parsed, json_out);    
        std::cout << "First account in parsed json: " << pending_parsed.pending (0).account () << std::endl;
    }
    else
    {
        std::cerr << "Could not connect. Make sure the server is running and that the transport is supported" << std::endl;
    }
    return 0;
}
