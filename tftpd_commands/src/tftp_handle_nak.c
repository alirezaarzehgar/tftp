/**
 * @file tftp_handle_nak.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftpd_commands/tftp_handle_nak.h"

void
nak (struct sockaddr_in clientAddress, int errorCode)
{
  tftphdr_t *hdr;

  char buf[BUFSIZ];

  char msg[BUFSIZ];

  int len;

  socklen_t sockLen = sizeof (clientAddress);

  hdr = (tftphdr_t *)&buf;

  len = strlen (strerror (errorCode)) + 1;

  if (errorCode == 0)
  {
    strcpy (msg, "Unknow request");
    len = 15;
  }
  else
    strncpy (msg, strerror (errorCode), len);

  hdr->th_opcode = htons ((u_short)ERROR);

  hdr->th_code = htons ((u_short)errorCode);

  memcpy (hdr->th_msg, msg, len);

  len += 4; /* Space for header */

  if (sendto (tftp_conn->fd, buf, len, 0, (struct sockaddr *)&clientAddress,
              sockLen) <= 0)
    perror ("Unable sending nak");
}

void
tftp_handle_nak (char *unused, struct sockaddr_in clientAddress)
{
  nak (clientAddress, errno);

  (void *)unused; /* Quit unused warning */
}