/**
 * @file tftp_helper.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftp_commands/tftp_helper.h"

extern tftp_socket_t
*global_tst;     /* global tftp socket strcuture for connection info */
extern char buf[BUFSIZ];              /* buffer for holding packet contents */

bool
argument_error (int argc, int allowed)
{
  if (argc != allowed && allowed != -1)
  {
    fprintf (stderr, MSG_WRONG_USAGE);
    return true;
  }

  return false;
}

int
make_request (int opcode, tftphdr_t *hdr, char *filename, char *mode)
{
  char *cp;

  /* assign operation code */
  hdr->th_opcode = htons ((u_short)opcode);

  cp = (char *)&hdr->th_stuff;

  /* assign filename to `th_u1.tu_stuff` and terminate with null */
  strncpy (cp, filename, strlen (filename));

  cp += strlen (filename);

  *cp++ = '\0';

  /* append mode to filename and terminate with null */
  strncpy (cp, mode, strlen (mode));

  cp += strlen (mode);

  *cp++ = '\0';

  /* return size of packet */
  return (cp - (char *)hdr);
}

void
tftp_extract_argv (char *cmd, int *argc, char ***argv)
{
  char *tmp;

  char *ch;

  int cpArgc;

  char **cpArgv;

  *argv = NULL;

  cpArgv = (char **)malloc3d (20, sizeof (char) * 15);

  cpArgc = 0;

  cpArgv[cpArgc++] = strtok (cmd, " ");

  while ((tmp = strtok (NULL, " ")) != NULL)
    cpArgv[cpArgc++] = tmp;

  ch = (char *)&cpArgv[cpArgc - 1][strlen (cpArgv[cpArgc - 1]) - 1];

  *ch = *ch == '\n' ? '\0' : *ch;

  ch = (char *)&cpArgv[cpArgc - 1][0];

  if (ch[0] == '\0')
    cpArgc--;

  *argc = cpArgc;

  *argv = cpArgv;
}

void
tftp_nothing (int argc, char **argv)
{
  (void)argc;
  (void)argv;   /* Quit unused compier warning */
}

void
nak (int error, const char *msg)
{
  tftphdr_t *tst;

  int len;

  tst = (tftphdr_t *)buf;

  tst->th_opcode = htons ((u_short)ERROR);

  tst->th_code = htonl ((u_short) error);

  if (msg)
  {
    len = strlen (msg) + 1;

    memcpy (tst->th_msg, msg, len);
    len += 4;     /* Add space for header */
  }

  if (sendto (global_tst->fd, buf, len, 0, (struct sockaddr *)&global_tst->saddr,
              global_tst->saddrLen))
    perror ("nak");
}