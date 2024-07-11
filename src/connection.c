#include "forest.h"

void check_new_connections(server_t *server)
{
    int new_socket;

    new_socket = accept(server->fd, (struct sockaddr *)&server->address,
        (socklen_t *)&server->addrlen);
    if (new_socket < 0) {
        perror("[FOREST] Accept failed");
        return;
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] == 0) {
            server->clients[i] = new_socket;
            printf("[FOREST] New connection, socket fd is: %d"
                   "%d\n",
                new_socket, i);
            if (server->welcome_message != NULL)
                send_response(new_socket, server->welcome_message,
                    server->end_of_message);
            server->new_client_handler(new_socket);
            break;
        }
    }
}

void add_client_to_set(server_t *server, int client_fd)
{
    if (client_fd > 0) {
        FD_SET(client_fd, &server->read_fd_set);
        if (client_fd > server->max_fd)
            server->max_fd = client_fd;
    }
}

void add_sockets_to_set(server_t *server)
{
    FD_ZERO(&server->read_fd_set);
    FD_SET(server->fd, &server->read_fd_set);
    server->max_fd = server->fd;
    for (int i = 0; i < MAX_CLIENTS; i++)
        add_client_to_set(server, server->clients[i]);
}

void handle_client_requests(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] > 0 &&
            FD_ISSET(server->clients[i], &server->read_fd_set)) {
            process_client_data(server, server->clients[i], i);
        }
    }
}
