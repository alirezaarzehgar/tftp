/**
 * @file tftp_quit.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "tftp_commands/tftp_quit.h"

void
tftp_quit (int argc, char **argv)
{
  (void)argc;
  (void)argv;     /* Quit unused compier warning */

  printf (MSG_GOODBYE);
  exit (EXIT_SUCCESS);
}
