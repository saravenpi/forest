#ifndef WAVE_H
#define WAVE_H

#include <netinet/in.h>
#define BUFFER_SIZE 4096
#define MAX_CLIENTS 100
#define MAX_ROUTES 50

typedef void (*message_handler_t)(int client_fd, const char *message);

typedef struct {
    int fd;
    int max_fd;
    int clients[MAX_CLIENTS];
    char buffers[MAX_CLIENTS][BUFFER_SIZE];
    struct sockaddr_in address;
    fd_set read_fd_set;
    int addrlen;
    char *default_end_of_message;
    message_handler_t handler;
} server_t;

typedef struct {
    char *method;
    char *path;
    char *version;
    char *headers;
    char *body;
} request_t;

server_t *init_server(int port);
void start_server(server_t *server);
void send_response(int client_fd, const char *body);
void send_to_all_clients(server_t *server, const char *message);
void set_default_end_of_message(server_t *server, char *end_of_message);
void set_message_handler(server_t *server, message_handler_t handler);
void default_handler(int client_fd, const char *request);
#endif
