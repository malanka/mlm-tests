#include "malamute.h"
#include <string>

#include <zsys.h>
#include <unistd.h>

int main (int argc, char *argv []) {

    zsys_init();
    zsys_set_logstream(stderr);
    mlm_client_verbose = 1;
    
    bool WORKAROUND = (::getenv("WORKAROUND")?true:false);


    const char *addr = "ipc://@/malamute";
    std::string agent_name = "test-agent";

    if ( argc > 1 )
        agent_name = agent_name + std::string(argv[1]); 

    zsys_set_logident(agent_name.c_str());
    
    if ( WORKAROUND )
        zsys_debug("########## with workaround");
        
    mlm_client_t *client = mlm_client_new();

    if ( !client )
        return 1;

    if ( mlm_client_connect (client, addr, 1000, agent_name.c_str()) != 0 )
    {
        mlm_client_destroy (&client);
        return 2;
    }

    mlm_client_set_consumer (client, "test_stream", ".*"); 
    mlm_client_set_producer (client, "i_am_alive"); 
    long unsigned count = 0;
    while ( !zsys_interrupted )
    {
        zmsg_t *msg = mlm_client_recv (client);
        if ( msg == NULL )
            continue;
        count++;
        std::string topic = mlm_client_subject (client);
        zsys_debug ("########## topic = %s", topic.c_str());
        if ( WORKAROUND )
        {
            if ( count % 5 == 0 )
            {
                std::string send_topic = "I_AM_ALIVE " + std::to_string (count);
                zmsg_t *msg_to_send = zmsg_new();
                mlm_client_send(client, send_topic.c_str(), &msg_to_send);
                zsys_debug ("########## send %s", send_topic.c_str());
            }
        }
    }

    zsys_debug ("########## total_count = %lu\n" , count);
    mlm_client_destroy (&client);
    return 0;
}
