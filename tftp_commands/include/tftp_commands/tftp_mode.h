#include "tftp_commands/tftp_sock_init.h"
#include "tftp_commands/validator.h"
#include "tftp_commands/tftp_helper.h"

#if !defined(TFTP_MODE_H)
#define TFTP_MODE_H

void tftp_setbinary (int argc, char **argv);

void tftp_setascii (int argc, char **argv);

void set_mode (int argc, char *mode);

#endif // TFTP_MODE_H
