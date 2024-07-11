/*
** EPITECH PROJECT, 2024
** forest
** File description:
** message.c
*/

#include "forest.h"

void default_message_handler(int client_fd, const char *message, void *data)
{
    send_response(client_fd, message, "\r\n");
}
