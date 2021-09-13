#include "shared_objects.h"

#if !defined(TFTP_LISTENER_H)
#define TFTP_LISTENER_H

bool tftp_listener (void (*rrq_handler)(), void (*wrq_handler)());

#endif // TFTP_LISTENER_H
