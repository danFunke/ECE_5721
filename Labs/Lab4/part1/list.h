/**
 * @file list.h
 * @author D. Funke
 * @brief An intrusive circular doubly linked list.
 * @date 2022-09-16
 * 
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief List element
 * 
 * @details A list element represents a single member of a linked list
 */
typedef struct list_element {
    struct list_element  *prev;  // Pointer to previous list element
    struct list_element  *next;  // Pointer to next list element
} list_element_t;

/**
 * @brief Initialize a list element
 * 
 * @param element Pointer to list_element_t to be initialized
 * 
 * @return 0 if successful, otherwise -1
 */
int list_element_init(list_element_t *element);

/**
 * @brief Checks if an element is in a list
 * 
 * @param element   Pointer to list_element_t to check for list membership
 * @param in_list   Pointer to boolean result of function
 * 
 * @return 0 if successful, otherwise -1
 * 
 */
int list_element_in_list(list_element_t *element, bool *in_list);

/**
 * @brief Insert a list element after another
 * 
 * @param after     Pointer to the element after which to insert new element
 * @param element   Pointer to the element to be inserted
 * 
 * @return 0 if successful, otherwise -1
 */
int list_element_insert_after(list_element_t *after, list_element_t *element);

/**
 * @brief Insert a list element before another
 * 
 * @param before    Pointer to the element before which to insert new element
 * @param element   Pointer to the element to be inserted
 * 
 * @return 0 if successful, otherwise -1
 */
int list_element_insert_before(list_element_t *before, list_element_t *element);

/**
 * @brief Removes a list element form a list
 * 
 * @param element Pointer to the element to be removed
 * 
 * @return 0 if successful, otherwise -1
 */
int list_element_remove(list_element_t *element);

/**
 * @brief List state
 * 
 * @details A struct representing the head of a circular doubly-linked list
 */
typedef struct list {
    list_element_t  head;
} list_t;

/**
 * @brief Function-like macro that allows for static initialization of a list
 * 
 * @param list List struct to initialize
 * 
 */
#define LIST_INIT(list) { .head.prev = &(list).head, .head.next = &(list).head }

/**
 * @brief Initialize a list
 * 
 * @param list  Pointer to the list to be initialized
 * 
 * @return 0 if successful, otherwise -1
 */
int list_init(list_t *list);

/**
 * @brief Checks if a list is empty
 * 
 * @param list      Pointer to the list to check for emptiness
 * @param is_empty  Pointer to the boolean result of the function
 * 
 * @return 0 if successful, otherwise -1
 */
int list_is_empty(list_t *list, bool *is_empty);

/**
 * @brief Prepends an element to a list
 * 
 * @param list      Pointer to list to which the element will be prepended
 * @param element   Pointer to the element to prepend to list
 * 
 * @return 0 if successful, otherwise -1
 */
int list_prepend(list_t *list, list_element_t *element);

/**
 * @brief Appends an element to a list
 * 
 * @param list      Pointer to List to which to append the new element
 * @param element   Pointer to element to append to list
 * 
 * @return 0 if successful, otherwise -1
 */
int list_append(list_t *list, list_element_t *element);

/**
 * @brief Removes an element from a list
 * 
 * @param list      Pointer to the list from which to remove element
 * @param element   Pointer to the element to be removed from list
 * 
 * @return 0 if successful, otherwise -1
 */
int list_remove(list_t *list, list_element_t *element);

/**
 * @brief Checks if an element is contained in a list
 * 
 * @param list          Input poiinter to list_t in which to check for element
 * @param element       Input pointer to list_element_t to check for in list
 * @param does_contain  Return pointer to boolean value
 * 
 * @return 0 if successful, otherwise -1
 */
int list_contains(list_t *list, list_element_t *element, bool *does_contain);

/**
 * @brief Removes all elements from a list
 * 
 * @param list  Pointer to the list to be cleared
 * 
 * @return 0 if successful, otherwise -1
 */
int list_clear(list_t *list);

/**
 * @brief List iterator state
 * 
 * @details Struct with elements pointing to a list and a particular element within it
 */
typedef struct list_iterator {
    list_t          *list;
    list_element_t  *current;
} list_iterator_t;

/**
 * @brief Initialize a list iterator
 * 
 * @param iter Pointer to list_iterator_t to initialize
 * @param list Pointer to list over which to iterate
 * 
 * @return 0 if successful, otherwise -1
 */
int list_iterator_init(list_iterator_t *iter, list_t *list);

/**
 * @brief Retrieves the next list element from a list iterator
 * 
 * @param iter      Pointer to list_iterator_t to get next element from
 * @param element   Pointer to list_element_t return next element
 * 
 * @return 0 if successful, otherwise -1
 * 
 */
int list_iterator_next(list_iterator_t *iter, list_element_t **element);

/**
 * @brief Retrieves the previous list element from a list iterator
 * 
 * @param iter      Pointer to list_iterator_t to get previous element from
 * @param element   Pointer to list_element_t return previous element
 * 
 * @return 0 if successful, otherwise -1
 */
int list_iterator_prev(list_iterator_t *iter, list_element_t **element);

#endif /* LIST_H_ */