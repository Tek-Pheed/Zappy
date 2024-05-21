/*
** EPITECH PROJECT, 2024
** B-PDG-300-TLS-3-1-PDGD04pm-lucas.loustalot
** File description:
** list_generic
*/

#include <stdlib.h>
#include "list.h"

unsigned int list_get_size(list_t *list)
{
    list_t *lst = list;
    unsigned int ct = 0;

    while (lst != NULL) {
        lst = lst->next;
        ct++;
    }
    return (ct);
}

bool list_is_empty(const list_t *list)
{
    return (list == NULL);
}

bool list_add_elem_at_front(list_t **front_ptr, void *elem)
{
    list_t *lst = NULL;
    list_t *new = NULL;

    if (front_ptr == NULL)
        return (false);
    new = malloc(sizeof(list_t));
    if (new == NULL)
        return (false);
    lst = *front_ptr;
    *front_ptr = new;
    new->next = lst;
    new->value = elem;
    return (true);
}

bool list_add_elem_at_back(list_t **front_ptr, void *elem)
{
    list_t *lst = NULL;

    if (front_ptr == NULL)
        return (false);
    if (*front_ptr == NULL)
        return (list_add_elem_at_front(front_ptr, elem));
    lst = *front_ptr;
    while (lst->next != NULL)
        lst = lst->next;
    lst->next = malloc(sizeof(list_t));
    if (lst->next == NULL)
        return (false);
    lst->next->value = elem;
    lst->next->next = NULL;
    return (true);
}

bool list_add_elem_at_position(
    list_t **front_ptr, void *elem, unsigned int pos)
{
    list_t *lst = NULL;
    list_t *new = NULL;

    if (*front_ptr == NULL || pos == 0)
        return list_add_elem_at_front(front_ptr, elem);
    if (pos == list_get_size(*front_ptr))
        return (list_add_elem_at_back(front_ptr, elem));
    if (pos >= list_get_size(*front_ptr))
        return (false);
    lst = *front_ptr;
    for (size_t i = 0; i < pos - 1; i++) {
        lst = lst->next;
    }
    new = malloc(sizeof(list_t));
    if (new == NULL)
        return (false);
    new->next = lst->next;
    new->value = elem;
    lst->next = new;
    return (true);
}
