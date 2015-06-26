#include "malamute.h"
#include <string>

#include <cstdlib>
#include <zsys.h>
#include <unistd.h>

static
int
s_stoi(const char* inp, int def)
{
    if (!inp)
        return def;

    try
    {
        return std::stoi(inp);
    }
    catch (const std::exception& e)
    {}

    return def;
}

int main (int argc, char *argv []) {
    zsys_init();
    zsys_set_logstream(stderr);
    mlm_client_verbose = 1;
    
    const char *addr = "ipc://@/malamute";
    std::string agent_name = "test-agent-producer";

    if ( argc > 1 )
        agent_name = agent_name + std::string(argv[1]); 

    zsys_set_logident(agent_name.c_str());

    mlm_client_t *client = mlm_client_new();

    if ( !client )
        return 1;

    if ( mlm_client_connect (client, addr, 1000, agent_name.c_str()) != 0 )
    {
        mlm_client_destroy (&client);
        return 2;
    }

    mlm_client_set_producer (client, "test_stream"); 

    long unsigned count = 0;
    int delay = s_stoi(::getenv("SLEEP"), 1000000);

    zsys_debug("########## usleep(%d)", delay);

    while ( ( !zsys_interrupted ) && (count <= 100000 ) )
    {
        std::string topic = "from:" + agent_name + " #" + std::to_string (count);
        zmsg_t *msg_to_send = zmsg_new();
        mlm_client_send(client, topic.c_str(), &msg_to_send);
        count++;
        if ( count % 20 == 0 )
        {
            zsys_debug ("########## count is %lu", count);
        }
        usleep(delay);
    }
    zsys_debug ("########## total_count = %lu" , count);
    mlm_client_destroy(&client);
    return 0;
}
