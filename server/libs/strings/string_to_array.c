/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** string_to_array
*/

#include <stdlib.h>
#include <string.h>

char **str_to_array(const char *buffer, const char *delim, size_t max_delim)
{
    char *dup = NULL;
    char *token = NULL;
    char **commands = NULL;

    if (buffer == NULL || buffer[0] == '\0')
        return (NULL);
    dup = strdup(buffer);
    commands = calloc(max_delim + 1, sizeof(char *));
    token = strtok(dup, delim);
    for (size_t i = 0; token != NULL && i != max_delim; i++) {
        commands[i] = strdup(token);
        token = strtok(NULL, delim);
    }
    free(dup);
    return (commands);
}

char *get_str_part(
    const char *buffer, const char *delim, size_t max_delim, size_t index)
{
    char *dup = NULL;
    char *token = NULL;
    char *part = NULL;

    if (buffer == NULL || buffer[0] == '\0')
        return (NULL);
    dup = strdup(buffer);
    token = strtok(dup, delim);
    for (size_t i = 0; token != NULL && i != max_delim; i++) {
        if (i == index) {
            part = strdup(token);
            break;
        }
        token = strtok(NULL, delim);
    }
    free(dup);
    return (part);
}

void str_array_destroy(char **array)
{
    if (array == NULL)
        return;
    for (size_t i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
