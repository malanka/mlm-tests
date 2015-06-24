#include "malamute.h"
#include <string>

#include <stdio.h>
#include <zsys.h>
#include <unistd.h>
int main (int argc, char *argv []) {
    
    const char *addr = "ipc://@/malamute";
    std::string agent_name = "test-agent-producer";

    if ( argc > 1 )
        agent_name = agent_name + std::string(argv[1]); 
    mlm_client_t *client = mlm_client_new();
    if ( !client ) {
        return 1;
    }
    if ( mlm_client_connect (client, addr, 1000, agent_name.c_str()) != 0 )
    {
        mlm_client_destroy(&client);
        return 2;
    }

    mlm_client_set_producer (client, "test_stream"); 
    uint64_t count = 0;
    while ( ( !zsys_interrupted ) && (count <= 100000 ) )
    {
        std::string topic = "from:" + agent_name + " #" + std::to_string (count);
        zmsg_t *msg_to_send = zmsg_new();
        mlm_client_send(client, topic.c_str(), &msg_to_send);
        sleep(1);
        count++;
        if ( count % 20 == 0 )
        {
            printf ("count is %lu\n", count );
        }
    }
    printf ("total_count = %lu\n" , count);
    mlm_client_destroy(&client);
    return 0;
}
