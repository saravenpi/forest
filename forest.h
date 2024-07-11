/*
** EPITECH PROJECT, 2024
** forest
** File description:
** message.c
*/

#pragma once
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define MAX_CLIENTS 1000

typedef void (*message_handler_t)(
    int client_fd, const char *message, void *data);
typedef void (*new_client_handler_t)(int client_fd, void *data);

struct server_t {
    int fd;
    int max_fd;
    int clients[MAX_CLIENTS];
    char buffers[MAX_CLIENTS][BUFFER_SIZE];
    struct sockaddr_in address;
    fd_set read_fd_set;
    int addrlen;
    char *end_of_message;
    char *welcome_message;
    new_client_handler_t new_client_handler;
    message_handler_t message_handler;
    void *data;
};
typedef struct server_t server_t;

void add_sockets_to_set(server_t *server);
void check_new_connections(server_t *server);
void handle_client_requests(server_t *server);
void process_client_data(server_t *server, int client_fd, int index);
void disconnect_client(server_t *server, int client_fd);

server_t *init_server(int port);
void start_server(server_t *server);
void send_response(int client_fd, const char *message, char *end_of_message);
void send_to_all_clients(server_t *server, const char *message);

void set_end_of_message(server_t *server, char *end_of_message);
void set_welcome_message(server_t *server, char *welcome_message);
void set_message_handler(server_t *server, message_handler_t handler);
void set_new_client_handler(server_t *server, new_client_handler_t handler);
void set_server_data(server_t *server, void *data);

void default_message_handler(int client_fd, const char *message, void *data);
