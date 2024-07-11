#include "forest.h"

void send_response(int client_fd, const char *message, char *end_of_message)
{
    char response[BUFFER_SIZE];
    ssize_t result;

    if (end_of_message == NULL)
        end_of_message = "\r\n";
    if (strlen(message) >= BUFFER_SIZE) {
        fprintf(stderr, "[FOREST] Message is too large\n");
        return;
    }
    if (message == NULL) {
        fprintf(stderr, "[FOREST] Message is NULL\n");
        return;
    }
    sprintf(response, "%s%s", message, end_of_message);
    result = write(client_fd, response, strlen(response));
    if (result == -1)
        perror("[FOREST] Failed to send response");
}

void send_to_all_clients(server_t *server, const char *message)
{
    char response[BUFFER_SIZE];

    memset(response, 0, BUFFER_SIZE);
    sprintf(response, "%s\r\n", message);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i] > 0)
            send_response(server->clients[i], response, NULL);
    }
}
