#include "shared_objects.h"

#if !defined(TFTP_HANDLE_NAK_H)
#define TFTP_HANDLE_NAK_H

void nak (struct sockaddr_in clientAddress);

void tftp_handle_nak (char *buf, struct sockaddr_in clientAddress);

#endif // TFTP_HANDLE_NAK_H
