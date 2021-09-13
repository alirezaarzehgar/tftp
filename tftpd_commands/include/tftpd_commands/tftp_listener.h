#include "shared_objects.h"

#if !defined(TFTP_LISTENER_H)
#define TFTP_LISTENER_H

typedef void (*request_handler_t) (char *);

bool tftp_listener (request_handler_t rrq_handler,
                    request_handler_t wrq_handler,
                    request_handler_t nak_handler);

#endif // TFTP_LISTENER_H
