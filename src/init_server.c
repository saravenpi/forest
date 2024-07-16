/*
** EPITECH PROJECT, 2024
** forest
** File description:
** init_server.c
*/

#include "forest.h"

void set_address(forest_server_t *server, int port)
{
    server->addrlen = sizeof(struct sockaddr_in);
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fd == 0) {
        perror("[FOREST] Socket creation failed");
        free(server);
        exit(EXIT_FAILURE);
    }
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);
    if (bind(server->fd, (struct sockaddr *)&server->address,
            server->addrlen) < 0) {
        perror("[FOREST] Bind failed");
        close(server->fd);
        free(server);
        exit(EXIT_FAILURE);
    }
}

void set_client_slots(forest_server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i] = 0;
        memset(server->buffers[i], 0, BUFFER_SIZE);
    }
    server->max_fd = server->fd;
}

void init_server_settings(forest_server_t *server)
{
    server->timeout.tv_sec = 0;
    server->timeout.tv_nsec = SELECT_INTERVAL_NSEC;
    server->message_handler = NULL;
    server->new_client_handler = NULL;
    server->disconnect_handler = NULL;
    server->live_handler = NULL;
    server->stop_handler = NULL;
    server->end_of_message = "\r\n";
    server->welcome_message = NULL;
    server->data_ptr = NULL;
    FD_ZERO(&server->read_fd_set);
    FD_SET(server->fd, &server->read_fd_set);
}

forest_server_t *init_server(int port)
{
    forest_server_t *server =
        (forest_server_t *)malloc(sizeof(forest_server_t));

    if (!server) {
        perror("[FOREST] Failed to allocate memory for server");
        exit(EXIT_FAILURE);
    }
    init_server_settings(server);
    set_address(server, port);
    if (listen(server->fd, 3) < 0) {
        perror("[FOREST] Listen failed");
        close(server->fd);
        free(server);
        exit(EXIT_FAILURE);
    }
    set_client_slots(server);
    return server;
}
