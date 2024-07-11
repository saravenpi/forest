/*
** EPITECH PROJECT, 2024
** forest
** File description:
** data.c
*/

#include "forest.h"

void handle_completed_message(
    forest_server_t *server, int client_fd, int index)
{
    server->buffers[index][strlen(server->buffers[index]) - 2] = '\0';
    printf("[FOREST] Received message from client %d: %s\n", client_fd,
        server->buffers[index]);
    server->message_handler(
        client_fd, server->buffers[index], server->data_ptr);
    memset(server->buffers[index], 0, BUFFER_SIZE);
}

void process_client_data(forest_server_t *server, int client_fd, int index)
{
    int valread;
    char buffer[BUFFER_SIZE];
    int message_complete;

    memset(buffer, 0, BUFFER_SIZE);
    valread = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (valread == 0)
        return disconnect_client(server, client_fd);
    if (valread < 0) {
        perror("[FOREST] Read failed");
        return disconnect_client(server, client_fd);
    }
    buffer[valread] = '\0';
    strncat(server->buffers[index], buffer,
        BUFFER_SIZE - strlen(server->buffers[index]) - 1);
    message_complete =
        strstr(server->buffers[index], server->end_of_message) != NULL;
    if (message_complete)
        handle_completed_message(server, client_fd, index);
}
