/**
 * @file tftp_put.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftp_commands/tftp_put.h"

extern tftp_socket_t
*global_tst;     /* global tftp socket strcuture for connection info */
extern char buf[BUFSIZ];              /* buffer for holding packet contents */

void
tftp_put (int argc, char **argv)
{

}
