/*
** EPITECH PROJECT, 2024
** B-PDG-300-TLS-3-1-PDGD04pm-lucas.loustalot
** File description:
** list_generic_del
*/

#include <stdlib.h>
#include "list.h"

bool list_del_elem_at_front(list_t **front_ptr)
{
    list_t *tmp = NULL;

    if (front_ptr == NULL || *front_ptr == NULL)
        return (false);
    if ((*front_ptr)->next != NULL) {
        tmp = *front_ptr;
        *front_ptr = (*front_ptr)->next;
        free(tmp);
    } else {
        free(*front_ptr);
        *front_ptr = NULL;
    }
    return (true);
}

bool list_del_elem_at_back(list_t **front_ptr)
{
    list_t *lst = NULL;

    if (front_ptr == NULL || *front_ptr == NULL)
        return (false);
    lst = *front_ptr;
    if (lst->next == NULL) {
        free(lst);
        *front_ptr = NULL;
        return (true);
    }
    while (lst->next->next != NULL)
        lst = lst->next;
    free(lst->next);
    lst->next = NULL;
    return (true);
}

bool list_del_elem_at_position(list_t **front_ptr, unsigned int position)
{
    list_t *lst = NULL;
    list_t *tmp = NULL;

    if (front_ptr == NULL || *front_ptr == NULL)
        return (false);
    lst = *front_ptr;
    if (position == 0)
        return (list_del_elem_at_front(front_ptr));
    if (position + 1 == list_get_size(*front_ptr))
        return (list_del_elem_at_back(front_ptr));
    if (position >= list_get_size(*front_ptr))
        return (false);
    for (size_t i = 0; i < position; i++) {
        tmp = lst;
        lst = lst->next;
    }
    tmp->next = lst->next;
    free(lst);
    return (true);
}

void list_clear(list_t **front)
{
    list_t *lst = *front;
    list_t *temp = NULL;

    while (lst != NULL) {
        temp = lst;
        lst = temp->next;
        free(temp);
    }
    *front = NULL;
}
