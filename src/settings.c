/*
** EPITECH PROJECT, 2024
** forest
** File description:
** response.c
*/

#include "forest.h"

void set_data(forest_server_t *server, void *data_ptr)
{
    server->data_ptr = data_ptr;
}

void set_message_handler(forest_server_t *server, message_handler_t handler)
{
    server->message_handler = handler;
}

void set_end_of_message(forest_server_t *server, char *end_of_message)
{
    server->end_of_message = end_of_message;
}

void set_welcome_message(forest_server_t *server, char *welcome_message)
{
    server->welcome_message = welcome_message;
}

void set_new_client_handler(
    forest_server_t *server, new_client_handler_t handler)
{
    server->new_client_handler = handler;
}
