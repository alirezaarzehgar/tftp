#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>

#include "xvalidator.h"
#include "tftpd_commands/tftp_sock_init.h"

#if !defined(TFTPD_MAIN_H)
#define TFTPD_MAIN_H

void usage();

inline static void
xchroot (char *chroot_dir)
{
  if (chdir (chroot_dir) == -1)
    FAIL_MSG ("Couldn't change directory cause : %s\n", strerror (errno));

  if (chroot (".") == -1)
    FAIL_MSG ("Couldn't chroot cause : %s\n", strerror (errno));
}

inline static void
xset_user (struct passwd *pwd)
{
  if (setegid (pwd->pw_gid) == -1)
    FAIL_MSG ("Unable to set effective group id : %d\n", pwd->pw_gid);

  if (seteuid (pwd->pw_uid) == -1)
    FAIL_MSG ("Unable to set effective user id : %d\n", pwd->pw_uid);
}

inline static void
xdaemonize (bool verbose)
{
  if (daemon (1, verbose) != 0)
    FAIL_MSG ("Couldn't daemonize\n", NULL);
}

#endif // TFTPD_MAIN_H
