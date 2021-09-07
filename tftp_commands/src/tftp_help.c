/**
 * @file tftp_help.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-07
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftp_commands/tftp_help.h"

extern struct cmd cmdTable[];

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
