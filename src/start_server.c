/*
** EPITECH PROJECT, 2024
** forest
** File description:
** start_server.c
*/

#include "forest.h"
#include <time.h>

void manage_connections(forest_server_t *server)
{
    int activity;

    activity = pselect(server->max_fd + 1, &server->read_fd_set, NULL, NULL,
        &server->timeout, NULL);
    if (activity < 0) {
        perror("[FOREST] Select failed");
        exit(84);
    }
    if (FD_ISSET(server->fd, &server->read_fd_set))
        check_new_connections(server);
}

void start_server(forest_server_t *server)
{
    printf("🌳 Server started !\n");
    printf("[FOREST] server port: %d\n", ntohs(server->address.sin_port));
    printf("[FOREST] server host: %s\n", inet_ntoa(server->address.sin_addr));
    while (1) {
        add_sockets_to_set(server);
        manage_connections(server);
        handle_client_requests(server);
        if (server->live_handler != NULL)
            server->live_handler(server->data_ptr);
    }
    printf("[FOREST] server shutting down\n");
}
