/**
 * @file tftp_get.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftp_commands/tftp_get.h"

extern tftp_socket_t
*global_tst;     /* global tftp socket strcuture for connection info */
extern char buf[BUFSIZ];              /* buffer for holding packet contents */

void
tftp_get (int argc, char **argv)
{
  if (argument_error (argc, 2))
    return;

  tftphdr_t *tst;

  int size;

  int block;

  char *mode;

  int retval;

  int tst_opcode;

  int tst_block;

  char *filename;

  int fd;

  int port;

  int firsttrap;

  int n;

  tst = (tftphdr_t *)buf;

  port = ntohs (global_tst->saddr.sin_port);

  if (global_tst->empty)
  {
    tftp_sock_init (port, inet_ntoa (global_tst->saddr.sin_addr),
                    global_tst->mode);

    printf ("reinit\n");
  }

  size = 0;

  block = 1;

  mode = global_tst->mode;

  retval = 0;

  tst_opcode = 0;

  tst_block = 0;

  filename = argv[1];

  firsttrap = 1;

  if (!current_folder_waccess())
    fprintf (stderr, MSG_CURRENT_PERMISSION_DENIED);

#ifndef DEBUG
  fd = open (filename, O_RDWR | O_CREAT | O_ASYNC | O_TRUNC, 0644);
#endif

  do
  {
    if (firsttrap)
    {
      size = make_request (RRQ, tst, filename, mode);
      firsttrap = 0;
    }
    else
    {
      tst->th_opcode = htons ((u_short) ACK);

      tst->th_block = htons ((u_short)block);

      /* clear previos data */
      memset (tst->th_data, 0, SEGMENT_SIZE);

      size = 4;

      block++;
    }

    retval = sendto (global_tst->fd, buf, size, 0,
                     (struct sockaddr *)&global_tst->saddr, global_tst->saddrLen);
    if (retval != size)
      return perror ("tftp : sendto");

    /* repeat giving data packet until packet is not standard */
    while (1)
    {
      do
      {
        n = recvfrom (global_tst->fd, buf, PACKET_SIZE, 0,
                      (struct sockaddr *)&global_tst->saddr, &global_tst->saddrLen);
      }
      while (n <= 0);

      tst_opcode = ntohs (tst->th_opcode);

      tst_block = ntohs (tst->th_block);

      if (tst_opcode == DATA && block == tst_block)
        break;

      if (tst_opcode == ERROR)
      {
        fprintf (stderr, "%s : %s\n", filename, tst->th_msg);

        tftp_sock_restart (port);

        return;
      }
    }

#ifdef DEBUG
    printf ("%s", tst->th_data);
    size = strlen (tst->th_data);
#else
    size = write (fd, tst->th_data, n - 4);
#endif
  }
  while (size == SEGMENT_SIZE);

  tst->th_opcode = htons ((u_short) ACK);
  tst->th_block = htons ((u_short) block);

  sendto (global_tst->fd, buf, 4, 0, (struct sockaddr *)&global_tst->saddr,
          global_tst->saddrLen);

  tftp_sock_restart (port);
}
