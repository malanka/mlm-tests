#include "malamute.h"
#include <string>

#include <stdio.h>
#include <zsys.h>

int main (int argc, char *argv []) {
    
    const char *addr = "ipc://@/malamute";

    // Create a client
    mlm_client_t *client = mlm_client_new();
    if ( !client ) {
        return 1;
    }
    if ( mlm_client_connect (client, addr, 1000, "test-agent-producer") != 0 )
    {
        mlm_client_destroy(&client);
        return 2;
    }

    mlm_client_set_producer (client, "test_stream"); 
    uint64_t count = 0;
    while ( ( !zsys_interrupted ) && (count <= 20000000 ) )
    {
        std::string topic = "the topic is:" + std::to_string (count);
        zmsg_t *msg_to_send = zmsg_new();
        mlm_client_send(client, topic.c_str(), &msg_to_send);
        count++;
        if ( count % 10000 == 0 )
        {
            printf ("count is %lu\n", count );
        }
    }
    printf ("total_count = %lu\n" , count);
    mlm_client_destroy(&client);
    return 0;
}
