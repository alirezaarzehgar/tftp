#include "shared_objects.h"

#if !defined(TFTP_HANDLE_RRQ_H)
#define TFTP_HANDLE_RRQ_H

void tftp_handle_rrq(char *buf, struct sockaddr_in clientAddress);

#endif // TFTP_HANDLE_RRQ_H
