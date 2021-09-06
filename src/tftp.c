/**
 * @file tftp.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "common/common.h"
#include "tftp.h"
#include "common/messages.h"
#include "common/malloc3d.h"
#include "argparse.h"
#include "common/file.h"

static tftp_socket_t
*global_tst;     /* global tftp socket strcuture for connection info */
static char buf[BUFSIZ];              /* buffer for holding packet contents */

/**
 * @brief initialize a socket for tftp connections
 *
 * @param port
 * @param ip
 * @return int
 */
int
tftp_sock_init (int port, const char *ip, char *mode)
{
  int retval;

  global_tst = malloc (sizeof (tftp_socket_t));

  /* create socket */

  global_tst->fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (global_tst->fd == -1)
    return -1;

  /* binding */
  global_tst->saddr.sin_family = AF_INET;

  global_tst->saddr.sin_port = htons (port);

  global_tst->saddr.sin_addr.s_addr = inet_addr (ip);

  global_tst->saddrLen = sizeof (global_tst->saddr);

  /* set default mode */
  global_tst->empty = false;

  strncpy (global_tst->mode, mode, MAXMODELEN);

  return 0;
}

/* helpers */

void
set_mode (int argc, char *mode)
{
  if (global_tst == NULL)
    global_tst = malloc (sizeof (tftp_socket_t));


  if (mode_validator (mode))
    strncpy (global_tst->mode, mode, MAXMODELEN);
}

void
usage (char *name)
{
  int flag = 0;
  for (size_t i = 0; i < N_CMDS; i++)
  {
    if (cmdTable[i].name != NULL && strcmp (name, cmdTable[i].name) == 0)
    {
      printf ("%s\t\t%s\n", cmdTable[i].name, cmdTable[i].help);
      flag = 1;
    }
  }

  if (!flag)
    printf ("%s not found\n", name);
}

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

/* user interface commands */

void
tftp_quit (int argc, char **argv)
{
  (void)argc;
  (void)argv;     /* Quit unused compier warning */

  printf (MSG_GOODBYE);
  exit (EXIT_SUCCESS);
}

void
tftp_help (int argc, char **argv)
{
  if (argc == 1)
  {
    for (size_t i = 0; i < N_CMDS; i++)
      usage ((char *)cmdTable[i].name);

    return;
  }

  for (size_t i = 1; i < argc; i++)
    usage (argv[i]);
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
tftp_put (int argc, char **argv)
{

}

void
tftp_get (int argc, char **argv)
{
  tftphdr_t *tst;

  int size;

  int block;

  char *mode;

  int retval;

  int tst_opcode;

  int tst_block;

  tst = (tftphdr_t *)buf;

  size = 0;

  block = 0;

  mode = global_tst->mode;

  retval = 0;

  tst_opcode = 0;

  tst_block = 0;

  if (argument_error (argc, 2))
    return;

  if (!current_folder_waccess())
    fprintf (stderr, MSG_CURRENT_PERMISSION_DENIED);

  do
  {
    if (block == 0)
      size = make_request (RRQ, tst, argv[1], mode);
    else
    {
      tst->th_opcode = htons ((u_short) ACK);
      tst->th_block = htons ((u_short)block);

      size = sizeof (tftphdr_t);

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
        size = recvfrom (global_tst->fd, buf, PACKET_SIZE, 0,
                         (struct sockaddr *)&global_tst->saddr, &global_tst->saddrLen);
      }
      while (size <= 0);

      tst_opcode = ntohs (tst->th_opcode);

      tst_block = htons (tst->th_block);

      if (tst_opcode == DATA)
      {
        printf ("%s\n", tst->th_data);

        break;
      }
    }
  }
  while (size == SEGMENT_SIZE);
}

void
tftp_status (int argc, char **argv)
{
  if (global_tst == NULL || global_tst->empty != false)
  {
    fprintf (stderr, MSG_CONNECTION_INIT_ERR);
    exit (EXIT_FAILURE);
  }

  char *ip = inet_ntoa (global_tst->saddr.sin_addr);

  printf (MSG_CONNECTED_TO_FORMAT, ip != NULL ? ip : MSG_UNDEFINED);

  printf (MSG_PORT_STATUS, htons (global_tst->saddr.sin_port));

  printf (MSG_MODE_FORMAT, mode_validator (global_tst->mode) ? global_tst->mode :
          MSG_UNDEFINED);
}

void
tftp_setbinary (int argc, char **argv)
{
  if (argument_error (argc, 1))
    return;

  set_mode (argc, "octet");
}

void
tftp_setascii (int argc, char **argv)
{
  if (argument_error (argc, 1))
    return;


  set_mode (argc, "netascii");
}

void
tftp_connect (int argc, char **argv)
{
  if (argument_error (argc, 2))
    return;

  if (global_tst == NULL)
    global_tst = malloc (sizeof (tftp_socket_t));

  if (ip_validator (argv[1]))
    global_tst->saddr.sin_addr.s_addr = inet_addr (argv[1]);
  else
    fprintf (stderr, MSG_INVALID_IP, argv[1]);
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