#include "config.h"

#include "tftp_sock_init.h"
#include "validator.h"
#include "file.h"
#include "messages.h"
#include "tftp_helper.h"
#include <sys/fcntl.h>

#if !defined(TFTP_GET_H)
#define TFTP_GET_H

void tftp_get (int argc, char **argv);

#endif // TFTP_GET_H
