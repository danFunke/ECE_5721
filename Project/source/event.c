/**
 * @file event.c
 * @author D. Funke
 * @brief An implementation of the publish and subscribe pattern
 * @details Depends on an underlying list module
 * @date 2022-11-16
 * 
 */
#include "event.h"

enum event_flags {
    ACTIVE = 0x01
};

int event_handler_init(event_handler_t *handler, void (*fun)(event_t *, void *))
{
    // Return with error if handler does not exist
    if (!handler) {
        return -1;
    }

    list_element_init(&handler->element);
    handler->fun = fun;
    handler->evt = NULL;
    handler->flags = 0;

    return 0;
}

int event_init(event_t *evt)
{
    // Return with error if event does not exist
    if (!evt) {
        return -1;
    }

    return list_init(&evt->handlers);
}

int event_subscribe(event_t *evt, event_handler_t *handler)
{
    // Return with error if either the event or handler does not exist
    if (!evt || !handler) {
        return -1;
    }

    // If handler is active and already subscribed to an event
    if ((handler->flags & ACTIVE) && handler->evt) {
        return -1;
    }
    // If handler is active, and not subscribed to an event
    else if ((handler->flags & ACTIVE) && !handler->evt) {
        handler->evt = evt;
        return 0;
    }
    // NOT ENTIRELY SURE WHAT IS HAPPENING HERE YET
    else {
        int error_code = list_prepend(&evt->handlers, &handler->element);

        if (!error_code) {
            handler->evt = evt;
        }

        return error_code;
    }
}

int event_unsubscribe(event_t *evt, event_handler_t *handler)
{
    // Return with error if either the event or handler does not exist
    if (!evt || !handler) {
        return - 1;
    }

    // Handler subscribed to an event
    if ((handler->flags & ACTIVE) && handler->evt) {
        handler->evt = NULL;
        return 0;
    }    
    // Handler not subscribed to an event
    else if ((handler->flags & ACTIVE) && !handler->evt) {
        return -1;
    }
    // 
    else {
        int error_code = list_remove(&evt->handlers, &handler->element);

        if (!error_code) {
            handler->evt = NULL;
        }

        return error_code;
    }
}

/**
 * @brief 
 * 
 */
static void event_update_subscription(event_t *evt, event_handler_t *handler)
{
    // Return to caller if handler does not exist
    if (!handler) {
        return;
    }

    // 
    if (!handler->evt) {
        event_unsubscribe(evt, handler);
    }

    if ((handler->evt) && (handler->evt != evt)) {
        event_t *new_evt = handler->evt;
        event_unsubscribe(evt, handler);
        event_subscribe(new_evt, handler);
    }
}

int event_publish(event_t *evt, void *ctx)
{
    // Return with error if event does not exist
    if (!evt) {
        return -1;
    }

    list_iterator_t iter;
    list_iterator_init(&iter, &evt->handlers);
    list_element_t *element;
    event_handler_t *last_handler = NULL;

    while (list_iterator_next(&iter, &element) == 0) {
        // Calculate address of element's event_handler
        event_handler_t *handler = (event_handler_t *)((char*)element - offsetof(event_handler_t, element));

        // Set handler ACTIVE flag, execute handler function, clear handler ACTIVE flag  
        handler->flags |= ACTIVE;
        if (handler->fun) {
            handler->fun(evt, ctx);
        }
        handler->flags &= ~ACTIVE;
        
        // Update subscription and last_handler
        event_update_subscription(evt, last_handler);
        last_handler = handler;
    }

    event_update_subscription(evt, last_handler);
    return 0;
}