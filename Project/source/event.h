/**
 * @file event.h
 * @author D. Funke
 * @brief An implementation of the publish and subscribe pattern
 * @details Depends on an underlying list module
 * @date 2022-10-23
 * 
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "list.h"

/**
 * @brief Event construct containing a list of handler functions
 * 
 */
typedef struct event {
    struct list handlers;
} event_t;

/**
 * @brief Event handler construct...
 * 
 */
typedef struct event_handler {
    /**
     * @brief Handler function pointer
     * 
     * @param evt   Pointer to the event being published
     * @param ctx   Pointer to the contect that was passed to the published event
     * 
     */
    void (*fun)(event_t *evt, void *ctx);

    list_element_t element; // List element for attaching handler to an event
    event_t *evt;           // Pointer to keep track of which event to subscribe to once handler finished
    unsigned char flags;    // Flag used to indicate if the handler should be removed
} event_handler_t;

/**
 * @brief Function-like macro that allows for static initialization of an event_handler
 * 
 * @param handler function to attached to handler
 * 
 * @example event_handler_t my_handler = EVENT_HANDLER_INIT(my_handler_function);
 */
#define EVENT_HANDLER_INIT(handler) {           \
    .fun = handler,                             \
    .element = (list_element_t){NULL, NULL},    \
    .evt = NULL,                                \
    .flags = 0                                  \
}

/**
 * @brief Initializes an event handler
 * 
 * @param handler   Pointer to event handler to be initialized
 * @param fun       Pointer to function with handler prototype
 * 
 * @return 0 if successful, otherwise -1
 */
int event_handler_init(event_handler_t *handler, void (*fun)(event_t *, void *));

/**
 * @brief Initializes an event
 * 
 * @param evt Pointer to event to be initialized
 * 
 * @return 0 if successful, otherwise -1
 */
int event_init(event_t *evt);

/**
 * @brief Macro that allows for static initialization of an event
 * @details event_t my_event = EVENT_INIT(my_event);
 * 
 */
#define EVENT_INIT(event) {.handlers = LIST_INIT((event).handlers)}

/**
 * @brief Attach an event_handler to an event
 *          Note: If one subscribes to an event from within a handler for that
 *          event, the newly subscribed handler won't be called until the next
 *          time that event is published
 * 
 * @param evt       Pointer to an initialized event to which the handler will be attached
 * @param handler   Pointer to an initialized event_handler to attach to evt 
 *
 * @return 0 if successful, otherwise -1 
 */
int event_subscribe(event_t *evt, event_handler_t *handler);

/**
 * @brief Detach an event_handler from an event
 *          Note: Unsubscribing a handler from within that handler's
 *          callback function is undefined behavior
 * 
 * @param evt       Pointer to an initialized event
 * @param handler   Pointer to an initialized event_handler
 * 
 * @return 0 if successful, otherwise -1
 */
int event_unsubscribe(event_t *evt, event_handler_t *handler);

/**
 * @brief 
 * 
 * @param evt
 * 
 * @return int 
 */
int event_publish(event_t *evt, void *ctx);


#endif /* EVENT_H_ */