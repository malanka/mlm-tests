#include "malamute.h"
#include <string>

#include <zsys.h>
#include <unistd.h>

int main (int argc, char *argv []) {

    zsys_init();
    zsys_set_logident("consumer");
    zsys_set_logstream(stderr);
    
    const char *addr = "ipc://@/malamute";
    std::string agent_name = "test-agent";

    if ( argc > 1 )
        agent_name = agent_name + std::string(argv[1]); 

    mlm_client_t *client = mlm_client_new();

    if ( !client )
        return 1;

    if ( mlm_client_connect (client, addr, 1000, agent_name.c_str()) != 0 )
    {
        mlm_client_destroy (&client);
        return 2;
    }

    mlm_client_set_consumer (client, "test_stream", ".*"); 
    long unsigned count = 0;
    while ( !zsys_interrupted )
    {
        zmsg_t *msg = mlm_client_recv (client);
        if ( msg == NULL )
            continue;
        count++;
        std::string topic = mlm_client_subject (client);
        zsys_debug ("topic = %s", topic.c_str());
    }

    zsys_debug ("total_count = %lu\n" , count);
    mlm_client_destroy (&client);
    return 0;
}
