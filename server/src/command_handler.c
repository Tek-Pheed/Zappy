/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** command_handler
*/

#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "list.h"
#include "server.h"
#include "strings_array.h"

static bool run_gui(
    server_t *serv, client_t *client, const char *cmd, char **args)
{
    for (size_t i = 0; i != sizeof(gui_cmds) / sizeof(gui_cmds[0]); i++) {
        if (strncmp(gui_cmds[i].command, cmd, strlen(gui_cmds[i].command)) == 0
            && (str_array_length(args) - 1) >= gui_cmds[i].nb_args) {
            server_log(serv, PROCESS, client->fd, cmd);
            return (gui_cmds[i].ptr.gui_ptr(serv, client, args));
        }
    }
    server_log(serv, WARNING, 0, "Unknown command");
    server_send_data(client, "suc\n");
    return (true);
}

static void broadcast_map_content(server_t *serv)
{
    size_t size = list_get_size(serv->client);
    client_t *cli = NULL;

    for (size_t i = 0; i != size; i++) {
        cli = list_get_elem_at_position(serv->client, i);
        if (cli == NULL || cli->fd == -1 || cli->state != GRAPHICAL)
            continue;
        gui_map_content(serv, cli, NULL);
    }
}

static bool check_cmd(int i, const char *cmd, const char *arg)
{
    if (strncmp(ai_cmds[i].command, cmd, strlen(ai_cmds[i].command)) == 0) {
        if (ai_cmds[i].nb_args > 0 && arg == NULL)
            return (false);
        return (true);
    }
    return (false);
}

static bool run_ai(
    server_t *serv, client_t *client, const char *cmd, const char *arg)
{
    bool ret = true;

    for (size_t i = 0; i != sizeof(ai_cmds) / sizeof(ai_cmds[0]); i++) {
        if (check_cmd(i, cmd, arg)) {
            server_log(serv, PROCESS, client->fd, cmd);
            ret = ai_cmds[i].ptr.ai_ptr(serv, client, arg);
            broadcast_map_content(serv);
            return (ret);
        }
    }
    server_log(serv, WARNING, 0, "Unknown command");
    return (false);
}

bool run_command(server_t *serv, client_t *client, const char *cmd)
{
    bool retval = true;
    char **args = str_to_array(cmd, " ", 4);

    if (client->state == AI && !client->player.is_dead) {
        retval = run_ai(serv, client, cmd, args[1]);
    } else {
        run_gui(serv, client, cmd, args);
    }
    str_array_destroy(args);
    return (retval);
}
