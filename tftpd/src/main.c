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

  /**
   * @brief permission test
   *
   */
  FILE *f = fopen ("test.txt", "w+");

  if (f == NULL)
    FAIL_MSG ("Access denied to parent directory\n", NULL);

  while (1)
  {
    fputs ("hello world\n", f);

    fflush (f);

    sleep (1);
  }

  fclose (f);

  return EXIT_SUCCESS;
}

void
usage()
{
  printf ("Help\n");
  for (size_t i = 0; i < sizeof (long_opt) / sizeof (struct option); i++)
    printf ("-%c\t--%s\n", long_opt[i].val, long_opt[i].name);
}