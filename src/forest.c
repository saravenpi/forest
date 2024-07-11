/*
** EPITECH PROJECT, 2024
** forest
** File description:
** forest.c
*/

#include "forest.h"

void set_address(server_t *server, int port)
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

void set_client_slots(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i] = 0;
        memset(server->buffers[i], 0, BUFFER_SIZE);
    }
    server->max_fd = server->fd;
}

server_t *init_server(int port)
{
    server_t *server = (server_t *)malloc(sizeof(server_t));

    if (!server) {
        perror("[FOREST] Failed to allocate memory for server");
        exit(EXIT_FAILURE);
    }
    set_address(server, port);
    if (listen(server->fd, 3) < 0) {
        perror("[FOREST] Listen failed");
        close(server->fd);
        free(server);
        exit(EXIT_FAILURE);
    }
    set_client_slots(server);
    server->message_handler = default_message_handler;
    server->end_of_message = "\r\n";
    server->welcome_message = "Welcome to the forest";
    server->data = NULL;
    return server;
}

void start_server(server_t *server)
{
    int activity;

    printf("🌳 Server started !\n");
    printf("[FOREST] server port: %d\n", ntohs(server->address.sin_port));
    printf("[FOREST] server host: %s\n", inet_ntoa(server->address.sin_addr));
    while (1) {
        add_sockets_to_set(server);
        activity =
            select(server->max_fd + 1, &server->read_fd_set, NULL, NULL, NULL);
        if (activity < 0) {
            perror("[FOREST] Select failed");
            break;
        }
        if (FD_ISSET(server->fd, &server->read_fd_set))
            check_new_connections(server);
        handle_client_requests(server);
    }
    printf("[FOREST] server shutting down\n");
}
