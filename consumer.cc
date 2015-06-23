#include "malamute.h"
#include <string>

#include <stdio.h>
#include <zsys.h>

int main (int argc, char *argv []) {
    
    const char *addr = "ipc://@/malamute";

    mlm_client_t *client = mlm_client_new();
    if ( !client ) {
        return 1;
    }
    if ( mlm_client_connect (client, addr, 1000, "test-agent") != 0 )
    {
        mlm_client_destroy(&client);
        return 2;
    }

    mlm_client_set_consumer (client, "test_stream", ".*"); 
    uint64_t count = 0;
    while ( !zsys_interrupted )
    {
        zmsg_t *msg = mlm_client_recv (client);
        if ( msg == NULL )
            continue;
        count++;
        std::string topic = mlm_client_subject (client);
        if ( count % 10000 == 0 )
        {
            printf ("count is %lu\n", count );
            printf ("topic = %s\n", topic.c_str());
        }
    }
    printf ("total_count = %lu\n" , count);
    mlm_client_destroy(&client);
    return 0;
}
