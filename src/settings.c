/*
** EPITECH PROJECT, 2024
** forest
** File description:
** response.c
*/

#include "forest.h"

void set_server_data(server_t *server, void *data)
{
    server->data = data;
}

void set_message_handler(server_t *server, message_handler_t handler)
{
    server->message_handler = handler;
}

void set_end_of_message(server_t *server, char *end_of_message)
{
    server->end_of_message = end_of_message;
}

void set_welcome_message(server_t *server, char *welcome_message)
{
    server->welcome_message = welcome_message;
}

void set_new_client_handler(server_t *server, new_client_handler_t handler)
{
    server->new_client_handler = handler;
}
