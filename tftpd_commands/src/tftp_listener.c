/**
 * @file tftp_listener.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftpd_commands/tftp_listener.h"

bool
tftp_listener (void (*rrq_handler)(), void (*wrq_handler)())
{
  bool rrqSupport = true;

  bool wrqSupport = true;

  if (rrq_handler == NULL || wrq_handler == NULL)
  {
    fprintf (stderr, "request handlers do not exist\n");

    rrqSupport = rrq_handler != NULL;

    wrqSupport = wrq_handler != NULL;
  }

  char buf[BUFSIZ];

  int counter;

  tftphdr_t *hdr;

  struct sockaddr_in caddr;

  socklen_t caddrLen;

  int opcode;

  caddrLen = sizeof (tftp_conn->addr);

  hdr = (tftphdr_t *)buf;

  while (1)
  {
    counter = 0;

    while (counter <= 0)
    {
      counter = recvfrom (tftp_conn->fd, buf, BUFSIZ, 0, (struct sockaddr *)&caddr,
                          &caddrLen);
    }

    opcode = ntohs (hdr->th_opcode);

    if (rrqSupport && opcode == RRQ)
    {
      // TODO
    }
    else if (wrqSupport && opcode == WRQ)
    {
      // TODO
    }
    else
    {
      // TODO
    }
  }
}