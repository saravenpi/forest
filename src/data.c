void handle_completed_request(server_t *server, int client_fd, int index)
{
    server->buffers[index][strlen(server->buffers[index]) - 2] = '\0';
    printf("[FOREST] Received message from client %d: %s\n", client_fd,
        server->buffers[index]);
    server->handler(client_fd, server->buffers[index]);
    memset(server->buffers[index], 0, BUFFER_SIZE);
}

void process_client_data(server_t *server, int client_fd, int index)
{
    int valread;
    char buffer[BUFFER_SIZE];
    int request_complete;

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
    request_complete =
        strstr(server->buffers[index], server->default_end_of_message) != NULL;
    if (request_complete)
        handle_completed_request(server, client_fd, index);
}