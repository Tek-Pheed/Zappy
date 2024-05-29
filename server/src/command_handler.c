/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command_handler
*/

#include "command_handler.h"
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "strings_array.h"

bool run_ai(server_t *serv, client_t *client, const char *cmd, const char *arg)
{
    for (size_t i = 0; i != sizeof(ai_cmds); i++) {
        if (strcmp(ai_cmds[i].command, cmd) == 0) {
            return (ai_cmds[i].ptr(serv, client, arg));
        }
    }
    return (false);
}

// Do it for gui also
bool run_command(server_t *serv, client_t *client, const char *cmd)
{
    bool retval = true;
    char **args = str_to_array(cmd, " ", 4);

    if (client->state == AI) {
        retval = run_ai(serv, client, cmd, args[0]);
    }
    str_array_destroy(args);
    return (retval);
}
