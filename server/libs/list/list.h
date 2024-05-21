/*
** EPITECH PROJECT, 2024
** B-PDG-300-TLS-3-1-PDGD04pm-lucas.loustalot
** File description:
** List Data Structure
*/

#ifndef LIST_H
    #define LIST_H
    #include <stdbool.h>

typedef struct list_s {
    void *value;
    struct list_s *next;
} list_t;

unsigned int list_get_size(list_t *list);
bool list_is_empty(const list_t *list);
int *get_user_sockets(list_t *lst);

typedef void (*value_displayer_t)(const void *value);

void list_dump(list_t *list, value_displayer_t val_disp);

bool list_add_elem_at_front(list_t **front_ptr, void *elem);
bool list_add_elem_at_back(list_t **front_ptr, void *elem);
bool list_add_elem_at_position(
    list_t **front_ptr, void *elem, unsigned int position);

bool list_del_elem_at_front(list_t **front_ptr);
bool list_del_elem_at_back(list_t **front_ptr);
bool list_del_elem_at_position(list_t **front_ptr, unsigned int position);

void list_clear(list_t **front_ptr);

void *list_get_elem_at_front(const list_t *list);
void *list_get_elem_at_back(list_t *list);
void *list_get_elem_at_position(list_t *list, unsigned int position);

#endif /*LIST_H*/
