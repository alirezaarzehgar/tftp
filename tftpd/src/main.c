/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "main.h"

static struct option long_opt[] =
{
  {"listen", no_argument, NULL, 'l'},
  {"foreground", no_argument, NULL, 'f'},
  {"secure", required_argument, NULL, 's'},
  {"user", required_argument, NULL, 'u'},
  {"address", required_argument, NULL, 'a'},
  {"help", no_argument, NULL, 'h'},
  {"verbose", no_argument, NULL, 'v'}
};

int
main (int argc, char const *argv[])
{
  /* option variables */
  int index_opt;

  int c;

  /* flags */
  bool standlone = false;

  bool foreground = false;

  bool secure = false;

  bool setuid = false;

  bool setaddress = false;

  bool verbose = false;

  /* arguments */
  const char *user = "nobody";

  char *address = (char *)malloc (sizeof (char) * 16);

  char *ip = (char *)malloc (sizeof (char) * 16);

  int port = 0;

  char *chroot_dir = (char *)malloc (sizeof (char) * 16);

  /* common */
  struct passwd *pwd;

  /* parsing arguments */
  do
  {
    switch ((c = getopt_long (argc, (char *const *)argv, "vhlfs:u:a:", long_opt,
                              &index_opt)))
    {
    case 'l':
      standlone = true;
      foreground = false;
      break;

    case 'f':
      standlone = false;
      foreground = true;
      break;

    case 'h':
      usage();
      break;

    case 's':
      secure = true;
      if (xvalidate_dir_path_exists (optarg))
        chroot_dir = optarg;

      break;

    case 'a':
      setaddress = true;
      if (xvalidate_address (optarg))
        address = optarg;

      break;

    case 'u':
      setuid = true;
      user = optarg;
      break;

    case 'v':
      verbose = true;
      break;
    }
  }
  while (c != -1);

  if (!setaddress)
  {
    xset_default_address (&address);
    setaddress = true;
  }

  /**
   * @brief binding addresses before changing root permission
   *
   */
  if (setaddress && parse_address (address, &ip, &port))
    xtftp_sock_init (ip, port);

  /**
   * @brief get passwd information before chroot and setuid
   * cause when we change root we haven't access to /etc/passwd.
   * and setting uid or gid is meaningless without pwd struct.
   *
   */
  if ((pwd = getpwnam (user)) == NULL)
    FAIL_MSG ("Unable to get passwd info : %s\n", strerror (errno));

  if (secure && chroot_dir != NULL)
    xchroot (chroot_dir);

  if (setuid && user != NULL)
    xset_user (pwd);

  if (standlone && !foreground)
    xdaemonize (verbose);

  if (tftp_conn == NULL)
    FAIL_MSG ("Not initialized\n", NULL);

  printf ("%s->%d\n", inet_ntoa (tftp_conn->addr.sin_addr),
          ntohs (tftp_conn->addr.sin_port));

  while (1)
  {
    int counter = 0;

    struct sockaddr_in caddr;

    socklen_t caddrLen = sizeof (tftp_conn->addr);

    char buf[BUFSIZ];

    while (counter <= 0)
    {
      counter = recvfrom (tftp_conn->fd, buf, BUFSIZ, 0, (struct sockaddr *)&caddr,
                          &caddrLen);
    }

    printf ("msg: %s\n", buf);
  }

  return EXIT_SUCCESS;
}

void
usage()
{
  printf ("Help\n");
  for (size_t i = 0; i < sizeof (long_opt) / sizeof (struct option); i++)
    printf ("-%c\t--%s\n", long_opt[i].val, long_opt[i].name);
}