#include "tftp_commands/tftp_sock_init.h"
#include "tftp_commands/tftp_help.h"
#include "tftp_commands/messages.h"
#include "tftp_commands/malloc3d.h"

#if !defined(TFTP_HELPER_H)
#define TFTP_HELPER_H

bool argument_error (int argc, int allowed);

int make_request (int opcode, tftphdr_t *hdr, char *filename, char *mode);

void tftp_extract_argv (char *cmd, int *argc, char ***argv);

void tftp_nothing (int argc, char **argv);

void nak(int error, const char *msg);

#endif // TFTP_HELPER_H
