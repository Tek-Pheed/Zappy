/*
** EPITECH PROJECT, 2024
** B-PDG-300-TLS-3-1-PDGD04pm-lucas.loustalot
** File description:
** list_generic_display
*/

#include <stdlib.h>
#include "list.h"

void list_dump(list_t *list, value_displayer_t val_disp)
{
    list_t *lst = list;

    if (list == NULL)
        return;
    while (lst != NULL) {
        val_disp(lst->value);
        lst = lst->next;
    }
}
