/*
** EPITECH PROJECT, 2024
** B-PDG-300-TLS-3-1-PDGD04pm-lucas.loustalot
** File description:
** list_generic_get
*/

#include <stdlib.h>
#include "list.h"

void *list_get_elem_at_front(const list_t *list)
{
    if (list == NULL)
        return (0);
    return (list->value);
}

void *list_get_elem_at_back(list_t *list)
{
    list_t *lst = list;

    if (list == NULL)
        return (0);
    while (lst->next != NULL)
        lst = lst->next;
    return (lst->value);
}

void *list_get_elem_at_position(list_t *list, unsigned int position)
{
    list_t *lst = list;

    if (list == NULL)
        return (NULL);
    if (position == 0)
        return list_get_elem_at_front(list);
    if (position >= list_get_size(list))
        return (NULL);
    for (size_t i = 0; i < position; i++) {
        if (lst == NULL)
            return (NULL);
        lst = lst->next;
    }
    return (lst->value);
}
