/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command_handler
*/

#include "command_handler.h"
#include <string.h>
#include "server.h"
#include "strings_array.h"

bool run_gui(server_t *serv, client_t *client, const char *cmd, char **args)
{
    for (size_t i = 0; i != sizeof(gui_cmds) / sizeof(gui_cmds[0]); i++) {
        if (strcmp(gui_cmds[i].command, cmd) == 0
            && (str_array_length(args) - 1) >= gui_cmds[i].nb_args) {
            return (gui_cmds[i].ptr.gui_ptr(serv, client, args));
        }
    }
    return (false);
}

bool run_command(server_t *serv, client_t *client, const char *cmd)
{
    bool retval = true;
    char **args = str_to_array(cmd, " ", 4);

    retval = run_gui(serv, client, cmd, args);
    str_array_destroy(args);
    return (retval);
}
// if (client->state == AI) {
//     retval = run_ai(serv, client, cmd, args[1]);
// } else {
//     retval = run_gui(serv, client, cmd, args);
// }

// bool run_ai(server_t *serv, client_t *client, const char *cmd, const char
// *arg)
// {
//     for (size_t i = 0; i != sizeof(gui_cmds) / sizeof(gui_cmds[0]); i++) {
//         if (strcmp(ai_cmds[i].command, cmd) == 0) {
//             return (ai_cmds[i].ptr.ai_ptr(serv, client, arg));
//         }
//     }
//     return (false);
// }
