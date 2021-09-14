/**
 * @file tftp_handle_wrq.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftpd_commands/tftp_handle_wrq.h"

void
tftp_handle_wrq (char *buf, struct sockaddr_in clientAddress)
{
  tftphdr_t *hdr;

  char *filename;

  int fd;

  int size;

  char fbuf[SEGMENT_SIZE];

  char newbuf[PACKET_SIZE];

  char n;

  int block;

  int user_opcode;

  int user_block;

  socklen_t len;

  bool f;

  hdr = (tftphdr_t *)newbuf;

  filename = ((tftphdr_t *)buf)->th_stuff;

  block = 0;

  user_opcode = 0;

  user_block = 0;

  int acksize;

  len = sizeof (clientAddress);

  if (!have_write_access_current_dir())
  {
    nak (clientAddress, EACCES);

    goto abort;
  }

  fd = open (filename, O_RDWR | O_CREAT | O_ASYNC | O_TRUNC, 0644);

  if (fd == -1)
  {
    nak (clientAddress, errno);

    goto abort;
  }

  f = true;

  do
  {
    bzero (newbuf, PACKET_SIZE);

    hdr->th_opcode = htons ((u_short) ACK);

    hdr->th_block = htons ((u_short) block);

    block++;

    size = 4;

    n = sendto (tftp_conn->fd, newbuf, size, 0, (struct sockaddr *)&clientAddress,
                sizeof (clientAddress));

    if (n == -1)
    {
      nak (clientAddress, errno);

      goto abort;
    }

    do
    {
      bzero (newbuf, PACKET_SIZE);

      do
      {
        size = recvfrom (tftp_conn->fd, newbuf, PACKET_SIZE, 0,
                         (struct sockaddr *)&clientAddress, &len);
      }
      while (size <= 0);

      user_opcode = ntohs ((u_short) hdr->th_opcode);

      user_block = ntohs ((u_short) hdr->th_block);

      if (user_opcode == DATA && user_block == block)
        break;
    }
    while (1);

    size = write (fd, hdr->th_data, strlen (hdr->th_data));

    if (user_block == 65535)
    {
      nak (clientAddress, EDOM);

      goto abort;
    }
  }
  while (size == SEGMENT_SIZE);
  hdr->th_opcode = htons ((u_short) ACK);

  hdr->th_block = htons ((u_short) block);

  block++;

  size = 4;

  n = sendto (tftp_conn->fd, newbuf, size, 0, (struct sockaddr *)&clientAddress,
              sizeof (clientAddress));

abort:

  close (fd);

  bzero (fbuf, strlen (fbuf));

  bzero (filename, strlen (filename));

  bzero (buf, PACKET_SIZE);

  bzero (newbuf, PACKET_SIZE);
}