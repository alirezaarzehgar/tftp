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

  char newbuf[PACKET_SIZE];

  char n;

  int block;

  int user_opcode;

  int user_block;

  socklen_t len;

  hdr = (tftphdr_t *)newbuf;

  filename = ((tftphdr_t *)buf)->th_stuff;

  block = 1;

  user_opcode = 0;

  user_block = 0;

  len = sizeof (clientAddress);

  if (!have_read_access (filename))
  {
    nak (clientAddress, ENOENT);

    goto abort;
  }

  fd = open (filename, O_RDONLY);

  if (fd == -1)
  {
    nak (clientAddress, errno);

    goto abort;
  }

  do
  {
    do
    {
      size = read (fd, fbuf, SEGMENT_SIZE);
    }
    while (size < 0);

    /* fill data */
    hdr->th_opcode = htons (DATA);

    memcpy (hdr->th_data, fbuf, size);

    hdr->th_block = htons (block);

    /* send data */
    n = sendto (tftp_conn->fd, newbuf, size + 4, 0,
                (struct sockaddr *)&clientAddress,
                sizeof (clientAddress));
    if (n == -1)
    {
      nak (clientAddress, errno);

      goto abort;
    }

    do
    {
      n = recvfrom (tftp_conn->fd, buf, PACKET_SIZE, 0,
                    (struct sockaddr *)&clientAddress,
                    &len);

      user_opcode = ntohs (hdr->th_opcode);

      user_block = ntohs (hdr->th_block);
    }
    while (n <= 0 || user_opcode != DATA || user_block != block);

    /**
     * @brief Fix unknow bug on this project cause
     * htons(65535 + 1) is equal to zero!
     *
     * @param block
     */
    if (user_block == 65535)
    {
      nak (clientAddress, EDOM);

      goto abort;
    }

    block++;

    bzero (newbuf, PACKET_SIZE);
  }
  while (size == SEGMENT_SIZE);

abort:

  close (fd);

  bzero (fbuf, strlen (fbuf));

  bzero (filename, strlen (filename));

  bzero (buf, PACKET_SIZE);

  bzero (newbuf, PACKET_SIZE);
}