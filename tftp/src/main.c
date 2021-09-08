/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief main file for doing anything
 * @version 0.1
 * @date 2021-09-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "main.h"

/**
 * @brief endpoint
 *
 * @param argc
 * @param argv
 * @return int
 */
int
main (int argc, char const *argv[])
{
  char *ip;

#ifdef TFTP_PORT
  u_short port = TFTP_PORT;
#else
  u_short port = 69;
#endif // TFTP_PORT

  char mode[MAXMODELEN] = "netascii";

  char command[MAX_ARG_CMD_LEN];

  char filename[MAX_FILENAME_LEN];

  int opt;

  char *commandHolder;

  size_t commandHolderLen;

  int ipflag = 0;

  int cmdflag = 0;        /* cmd flag is off for getting from prompt */
  /* if cmdflag == 1 means to executing externcal command argument */
  int fflag = 0;          /* when cmd flag == 1 file flag should on */

  /* init */
  ip = (char *)calloc (sizeof (char), MAXIPLEN);

  memset (command, 0, MAX_ARG_CMD_LEN);

  memset (filename, 0, MAX_FILENAME_LEN);

  commandHolder = (char *)malloc (sizeof (char) * MAX_USER_CMD_LEN);

  commandHolderLen = sizeof (commandHolder);

  /* set signal */
  signal (SIGINT, SIG_IGN);

  /* parse arguments */
  while ((opt = getopt (argc, (char *const *) argv, "a:c:f:m:p:")) != -1)
  {
    switch (opt)
    {
    case 'a':
      ipflag = 1;

      if (ip_validator (optarg))
        strncpy (ip, optarg, MAXIPLEN);
      else
      {
        fprintf (stderr, ERROR_INVALID_IP, optarg);
#ifdef HAVE_CONFIG
        strncpy (ip, DEFAULT_IP, MAXIPLEN);
#else
        strncpy (ip, "127.0.0.1", MAXIPLEN);
#endif // HAVE_CONFIG
      }

      break;

    case 'f':
      if (filename_validator (command, optarg))
      {
        strncpy (filename, optarg, MAX_FILENAME_LEN);
        fflag = 1;
      }
      else
        perror (optarg);

      break;

    case 'm':
      if (mode_validator (optarg))
        strncpy (mode, optarg, MAXMODELEN);
      else
        fprintf (stderr, ERROR_INVALID_MODE, optarg);

      break;

    case 'p':
      if (port_validator (atoi (optarg)))
        port = atoi (optarg);
      else
        fprintf (stderr, ERROR_INVALID_PORT, port);

      break;

    case 'c':
      if (cmd_validator (optarg))
      {
        strncpy (command, optarg, MAX_ARG_CMD_LEN);
        cmdflag = 1;
      }
      else
      {
        fprintf (stderr, ERROR_INVALID_CMD, optarg);
        exit (EXIT_FAILURE);
      }

      break;

    default:
      break;
    }
  }

  /**
   * @brief If first ip char equal to '\0' means to ip doesn't set.
   * We should get server ip from user
   *
   */
  if (!ipflag)
  {
    while (!ip_validator (ip))
    {
      size_t ipLen = sizeof (ip);

      printf (PROMPT_GET_IP);

      getline ((char **)&ip, &ipLen, stdin);

      ip[strlen (ip) - 1] = '\0';
    }

    ipflag = 1;
  }

  /* connect to ip and port after getting this stuffs */
  xtftp_sock_init (port, ip, mode);

  /**
   * @brief If -c option set we should just execute that command
   * If first character of `command` variable equal to '\0`
   * means to command is set
   *
   */
  if (cmdflag)
  {
    char *argv[] = {command, filename};

    if (!fflag || !ipflag)
      fprintf (stderr, MSG_INCOMPLETE_FLAG);

    for (size_t i = 0; i < sizeof (cmdTable) / sizeof (struct cmd); i++)
    {
      if (cmdTable[i].name == NULL)
        continue;

      if (strcmp (cmdTable[i].name, command) == 0)
        cmdTable[i].handler (2, argv);
    }
    return EXIT_SUCCESS;
  }

  /**
   * @brief main loop for executing command
   *
   */
  while (1)
  {
    int argc;

    char **argv;

    bool notfound = 1;

    commandHolderLen = sizeof (commandHolder);

    printf (PROMPT);

    getline (&commandHolder, &commandHolderLen, stdin);

    if (commandHolderLen > MAX_USER_CMD_LEN)
    {
      fprintf (stderr, "command is too long\n");

      continue;
    }

    tftp_extract_argv (commandHolder, &argc, &argv);

    for (size_t i = 0; i < sizeof (cmdTable) / sizeof (struct cmd); i++)
    {
      if (cmdTable[i].name == NULL)
        continue;

      if (strcmp (cmdTable[i].name, argv[0]) == 0)
      {
        cmdTable[i].handler (argc, argv);

        notfound = !notfound;
      }
    }

    if (notfound)
      printf (MSG_NOTFOUND);
  }

  return EXIT_SUCCESS;
}