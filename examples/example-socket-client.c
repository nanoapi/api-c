#include "nano.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    const char* connection = argc > 1 ? argv[1] : "local:///tmp/nano";
    struct nano_session* session = nano_connect (connection);

    // Pending query
    QueryAccountPending pending;
    query_account_pending__init (&pending);
    pending.count = 10;    

    // Optional threshold field
    nano_optional_string threshold;
    nano_optional_string_init (&threshold);
    threshold.value = "20000000000000000000";
    pending.threshold = &threshold;

    const char* accounts [] = {
        "xrb_26u1uufyoig8777y6r8iqjtrw8sg8maqrm36zzcm95jmbd9i9aj5i8abr8u5", 
        "xrb_3dcfozsmekr1tr9skf1oa5wbgmxt81qepfdnt7zicq5x3hk65fg4fqj58mbr"};

    pending.n_accounts = 2;
    pending.accounts = (char**) malloc(sizeof(char*) * pending.n_accounts);
    for(int i=0;i<pending.n_accounts; i++)
    {
        pending.accounts[i] = (char*) malloc(sizeof(char) * strlen(accounts[i]) + 1);
        strcpy(pending.accounts[i], accounts[i]);
    }

    // Pack query
    size_t len = query_account_pending__get_packed_size (&pending);
    void* buf = (void*) malloc (len); 
    query_account_pending__pack (&pending, (uint8_t*)buf);

    // Query and unpack result
    void* result = NULL;
    size_t result_size = 0;
    if (!nano_query (session, QUERY_TYPE__ACCOUNT_PENDING, buf, len, &result, &result_size))
    {
        ResAccountPending * pending_result = res_account_pending__unpack (NULL, result_size, result);
        for (int i=0; i < pending_result->n_pending; i++)
        {
            printf("Account: %s\n", pending_result->pending[i]->account);
        }

        res_account_pending__free_unpacked (pending_result, NULL);
    }

    // Clean up
    free(buf);
    for(int i=0;i<pending.n_accounts; i++)
        free(pending.accounts[i]);
    free(pending.accounts);

    nano_disconnect (session);

    return 0;
}
