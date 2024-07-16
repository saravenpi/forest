/*
** EPITECH PROJECT, 2024
** forest
** File description:
** handlers.c
*/

#include "forest.h"

void set_live_handler(forest_server_t *server, live_handler_t handler)
{
    server->live_handler = handler;
}

void set_message_handler(forest_server_t *server, message_handler_t handler)
{
    server->message_handler = handler;
}

void set_new_client_handler(
    forest_server_t *server, new_client_handler_t handler)
{
    server->new_client_handler = handler;
}

void set_stop_handler(forest_server_t *server, stop_handler_t handler)
{
    server->stop_handler = handler;
}

void set_disconnect_handler(
    forest_server_t *server, disconnect_handler_t handler)
{
    server->disconnect_handler = handler;
}
