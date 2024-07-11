#include "forest.h"

void set_message_handler(server_t *server, message_handler_t handler)
{
    server->handler = handler;
}

void set_default_end_of_message(server_t *server, char *end_of_message)
{
    server->end_of_message = end_of_message;
}

void set_default_welcome_message(server_t *server, char *welcome_message)
{
    server->welcome_message = welcome_message;
}

void default_handler(int client_fd, const char *message)
{
    return send_response(client_fd, "Hello, World!", "\r\n");
}
