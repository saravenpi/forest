/*
** EPITECH PROJECT, 2024
** forest
** File description:
** client.c
*/

#include "forest.h"

void disconnect_client(forest_server_t *server, int client_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] != client_fd)
            continue;
        close(client_fd);
        server->clients[i] = 0;
        memset(server->buffers[i], 0, BUFFER_SIZE);
        if (server->disconnect_handler != NULL)
            server->disconnect_handler(client_fd, server->data_ptr);
        printf("[FOREST] Client disconnected, socket fd is %d\n", client_fd);
        break;
    }
}
