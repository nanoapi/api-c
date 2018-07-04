#include "nano.h"
#include "accounts.pb-c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    const char* connection = argc > 1 ? argv[1] : "local:///tmp/nano";
    struct nano_session* session = nano_connect (connection);
    if (!session)
    {
        printf("Could not connect. Make sure the server is running and that the transport is supported\n");
    }

    // Pending query
    ReqAccountPending pending;
    req_account_pending__init (&pending);
    pending.count = 10;    

    // Optional threshold field
    nano_optional_string threshold;
    nano_optional_string_init (&threshold);
    threshold.value = "200000000000000000000";
    pending.threshold = &threshold;

    const char* accounts [] = {
        "xrb_1111111111111111111111111111111111111111111111111111hifc8npp", 
        "xrb_3t6k35gi95xu6tergt6p69ck76ogmitsa8mnijtpxm9fkcm736xtoncuohr3"};

    pending.n_accounts = 2;
    pending.accounts = (char**) malloc(sizeof(char*) * pending.n_accounts);
    for(int i=0;i<pending.n_accounts; i++)
    {
        pending.accounts[i] = (char*) malloc(sizeof(char) * strlen(accounts[i]) + 1);
        strcpy(pending.accounts[i], accounts[i]);
    }

    // Pack query
    size_t len = req_account_pending__get_packed_size (&pending);
    void* buf = (void*) malloc (len); 
    req_account_pending__pack (&pending, (uint8_t*)buf);

    // Query and unpack result
    void* result = NULL;
    size_t result_size = 0;
    if (!nano_request (session, REQUEST_TYPE__ACCOUNT_PENDING, buf, len, &result, &result_size))
    {
        ResAccountPending * pending_result = res_account_pending__unpack (NULL, result_size, result);
        for (int i=0; i < pending_result->n_pending; i++)
        {
            printf("Account: %s\n", pending_result->pending[i]->account);
        }

        res_account_pending__free_unpacked (pending_result, NULL);
        free (result);
    }

    // Clean up
    free(buf);
    for(int i=0;i<pending.n_accounts; i++)
        free(pending.accounts[i]);
    free(pending.accounts);

    nano_disconnect (session);

    return 0;
}
