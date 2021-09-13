#include "shared_objects.h"

#if !defined(TFTP_HANDLER_WRQ)
#define TFTP_HANDLER_WRQ

void tftp_handle_wrq(char *buf, struct sockaddr_in clientAddress);

#endif // TFTP_HANDLER_WRQ
