/*
** EPITECH PROJECT, 2024
** forest
** File description:
** stop_handler.c
*/

#include "forest.h"

void stop_server(forest_server_t *server)
{
    if (server->stop_handler != NULL)
        server->stop_handler(server);
    for (int i = 0; i < server->max_fd; i++) {
        if (FD_ISSET(i, &server->read_fd_set))
            close(i);
    }
    close(server->fd);
    printf("[FOREST] server stopped\n");
}
