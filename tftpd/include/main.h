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
#include "tftpd_commands/shared_objects.h"
#include "tftpd_commands/tftp_listener.h"

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

inline static void
xtftp_sock_init (char *ip, int port)
{
  if (!tftp_sock_init (ip, port))
    FAIL_MSG ("binding : %s\n", strerror (errno));
}

inline static void
xset_default_address (char **address)
{
  strcpy (*address, "127.0.0.1:69");
}

#endif // TFTPD_MAIN_H
