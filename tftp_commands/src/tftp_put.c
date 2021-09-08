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
  if (argument_error (argc, 2))
    return;

  tftphdr_t *tst;

  int size;

  char *filename;

  char *mode;

  int firsttrap;

  int hdr_opcode;

  int hdr_block;

  int block;

  int fd;

  int retval;

  int port;

  tst = (tftphdr_t *)buf;

  filename = argv[1];

  mode = global_tst->mode;

  firsttrap = 1;

  block = 0;

  fd = open (filename, O_RDONLY);

  port = ntohs (global_tst->saddr.sin_port);

  if (fd == -1)
  {
    fprintf (stderr, "file %s : %s\n", filename, strerror (errno));
    return;
  }

  if (global_tst->empty)
  {
    tftp_sock_init (port, inet_ntoa (global_tst->saddr.sin_addr),
                    global_tst->mode);

    printf ("reinit\n");
  }

  do
  {
    if (firsttrap)
    {
      size = make_request (WRQ, tst, filename, mode) - 4;
      firsttrap = 0;
    }
    else
    {
      /* clear previos data */
      memset (tst->th_data, 0, SEGMENT_SIZE);

      make_request (DATA, tst, filename, mode);

      char *cp;

      cp = (char *)tst->th_data;

      size = read (fd, cp, SEGMENT_SIZE);

      cp += size;

      *cp++ = '\0';

      tst->th_block = htons ((u_short) block);

      tst->th_opcode = htons ((u_short) DATA);
    }

    retval = sendto (global_tst->fd, buf, size + 4, 0,
                     (struct sockaddr *)&global_tst->saddr, global_tst->saddrLen);
    if (retval < 0)
      perror ("sendto : error");

    while (1)
    {
      do
      {
        retval = recvfrom (global_tst->fd, buf, PACKET_SIZE, 0,
                           (struct sockaddr *)&global_tst->saddr, &global_tst->saddrLen);
      }
      while (retval <= 0);

      hdr_block = ntohs (tst->th_block);

      hdr_opcode = ntohs (tst->th_opcode);

      if (hdr_opcode == ACK && hdr_block == block)
        break;

      if (hdr_opcode == ERROR)
        fprintf (stderr, "error : %d\n", tst->th_code);
    }

    block++;
  }
  while (size == SEGMENT_SIZE || block == 1);

  tftp_sock_restart (port);
}
