/**
 * @file tftp_handle_rrq.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftpd_commands/tftp_handle_rrq.h"

void
tftp_handle_rrq (char *buf, struct sockaddr_in clientAddress)
{
  tftphdr_t *hdr;

  char *filename;

  int fd;

  int size;

  char fbuf[SEGMENT_SIZE];

  char n;

  int block;

  hdr = (tftphdr_t *)buf;

  filename = hdr->th_stuff;

  block = 1;

  if (!have_read_access (filename))
    nak (clientAddress, ENOENT);

  fd = open (filename, O_RDONLY);

  if (fd == -1)
    nak (clientAddress, errno);

  do
  {
    do
    {
      size = read (fd, fbuf, SEGMENT_SIZE);
    }
    while (size < 0);

    /* TODO */

    n = sendto (tftp_conn->fd, buf, size, 0, (struct sockaddr *)&clientAddress,
                sizeof (clientAddress));
    if (n == -1)
      nak (clientAddress, errno);
      
    /* TODO */
  }
  while (size == PACKET_SIZE);

  close (fd);
}