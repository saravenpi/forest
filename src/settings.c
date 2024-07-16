/*
** EPITECH PROJECT, 2024
** forest
** File description:
** response.c
*/

#include "forest.h"

void set_data_ptr(forest_server_t *server, void *data_ptr)
{
    server->data_ptr = data_ptr;
}

void set_end_of_message(forest_server_t *server, char *end_of_message)
{
    server->end_of_message = end_of_message;
}

void set_welcome_message(forest_server_t *server, char *welcome_message)
{
    server->welcome_message = welcome_message;
}

void set_timeout_sec(forest_server_t *server, long socket_interval_sec)
{
    server->timeout.tv_sec = socket_interval_sec;
}

void set_timeout_nsec(
    forest_server_t *server, long socket_interval_nsec)
{
    server->timeout.tv_nsec = socket_interval_nsec;
}
