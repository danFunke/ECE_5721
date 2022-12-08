/**
 * @file list.c
 * @author D. Funke
 * @brief An intrusive circular doubly linked list
 * @date 2022-09-16
 * 
 */

#include "list.h"

int list_element_init(list_element_t *element)
{
    // Return with error if *element does not exist
    if (!element) {
        return -1;
    }

    // Initialize previous and next pointers to NULL value
    element->prev = NULL;
    element->next = NULL;

    return 0;
}

int list_element_in_list(list_element_t *element, bool *in_list)
{
    // Return with error if *element or *in_list does not exist
    if (!element || !in_list) {
        return -1;
    }

    // Check for list membership
    *in_list = element->prev != NULL;

    return 0;
}

int list_element_insert_after(list_element_t *after, list_element_t *element)
{
    // Return with error if first element is not already in a list
    bool in_list;
    if (list_element_in_list(after, &in_list) != 0 || !in_list) {
        return -1;
    }

    // Return with error if second element is already in a list
    if (list_element_in_list(element, &in_list) != 0 || in_list) {
        return -1;
    }

    // Assign list pointers
    element->next = after->next;
    element->prev = after;
    after->next->prev = element;
    after->next = element;

    return 0;
}

int list_element_insert_before(list_element_t *before, list_element_t *element)
{
    // Return with error if first element is not already in a list
    bool in_list;
    if (list_element_in_list(before, &in_list) != 0 || !in_list) {
        return -1;
    }

    // Return with error if second element is already in a list
    if (list_element_in_list(element, &in_list) != 0 || in_list) {
        return -1;
    }

    // Assign list pointers
    element->prev = before->prev;
    element->next = before;
    before->prev->next = element;
    before->prev = element;

    return 0;
}

int list_element_remove(list_element_t *element)
{
    // Return with error if element is not a member of a list
    bool in_list;
    if (list_element_in_list(element, &in_list) != 0 || !in_list) {
        return -1;
    }

    // Reassign list pointers
    element->prev->next = element->next;
    element->next->prev = element->prev;
    element->prev = NULL;
    element->next = NULL;

    return 0;
}

int list_init(list_t *list)
{
    // Return with error if list does not exist
    if (!list) {
        return -1;
    }

    // Initialize list head to point to itself
    list->head.prev = &list->head; 
    list->head.next = &list->head;

    return 0; 
}

int list_is_empty(list_t *list, bool *is_empty)
{
    // Return with error if either input argument does not exist
    if (!list || !is_empty) {
        return -1;
    }

    // List is empty if head element is pointing to itself
    *is_empty = list->head.prev == list->head.next;

    return 0;
}

int list_prepend(list_t *list, list_element_t *element)
{
    // Return with error if list does not exist
    if (!list || !element) {
        return -1;
    }

    return list_element_insert_after(&list->head, element);
}

int list_append(list_t *list, list_element_t *element)
{
    // Return with error if list does not exist
    if (!list || !element) {
        return -1;
    }

    return list_element_insert_before(&list->head, element);
}

int list_remove(list_t *list, list_element_t *element)
{
    // Return with error if list or element does not exist
    if (!list || !element) {
        return -1;
    }

    // Check if element is member of list
    bool does_contain;
    list_contains(list, element, &does_contain);

    // return with error if element not in list; otherwise remove it from list
    if (does_contain) {
        return list_element_remove(element);
    } else {
        return -1;
    }
}

int list_contains(list_t *list, list_element_t *element, bool *does_contain)
{
    // Return with error if any input argument does not exist
    if (!list || !element || !does_contain) {
        return -1;
    }

    // Iterate through list to check contents
    list_iterator_t iter;
    list_iterator_init(&iter, list);
    list_element_t *current;
    *does_contain = false;
    while (list_iterator_next(&iter, &current) == 0) {
        // Set does_contain to true if element is found in list
        if (current == element) {
            *does_contain = true;
        }
    }

    return 0;
}

int list_clear(list_t *list)
{
    // Return with error if list does not exist
    if (!list) {
        return -1;
    }

    // Iterate through list and clear links
    list_iterator_t iter;
    list_iterator_init(&iter, list);
    list_element_t *last = NULL;
    list_element_t *element;
    while (list_iterator_next(&iter, &element) == 0) {
        if (last != NULL) {
            list_remove(list, last);
        }
        last = element;
    }

    if (last != NULL) {
        list_remove(list, last);
    }

    return 0;
}

int list_iterator_init(list_iterator_t *iter, list_t *list)
{
    // Return with error if either input argument does not exist
    if (!iter || !list) {
        return -1;
    }

    iter->list = list;
    iter->current = &list->head;

    return 0;
}

int list_iterator_next(list_iterator_t *iter, list_element_t **element)
{
    // Return with error if either input argument does not exist
    if (!iter || !element) {
        return -1;
    }

    // Return with error if at end of list
    if (iter->current->next == &iter->list->head) {
        return -1;
    }

    // Reassign "current" element of iterator to next
    iter->current = iter->current->next;
    *element = iter->current;

    return 0;
}

int list_iterator_prev(list_iterator_t *iter, list_element_t **element)
{
    // Return with error if either input argument does not exist
    if (!iter || !element) {
        return -1;
    }

    // Return with error if at front of list
    if (iter->current->prev == &iter->list->head) {
        return -1;
    }

    // Reassign "current" element of iterator to previous
    iter->current = iter->current->prev;
    *element = iter->current;

    return 0;
}