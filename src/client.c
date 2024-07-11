#include "forest.h"

void disconnect_client(server_t *server, int client_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] == client_fd) {
            close(client_fd);
            server->clients[i] = 0;
            memset(server->buffers[i], 0, BUFFER_SIZE);
            printf(
                "[FOREST] Client disconnected, socket fd is %d\n", client_fd);
            break;
        }
    }
}

void set_new_client_handler(server_t *server, new_client_handler_t handler)
{
    server->new_client_handler = handler;
}

void default_new_client_handler(int client_fd)
{
    return send_response(client_fd, "Welcome to the forest", "\r\n");
}
