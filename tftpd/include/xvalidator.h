#include "tftpd_commands/validator.h"

#if !defined(XVALIDATOR_H)
#define XVALIDATOR_H

#define FAIL_MSG(msg, param) do { \
    fprintf (stderr, msg, param);  \
    exit (EXIT_FAILURE);            \
}while(0); \

inline static bool
xvalidate_dir_path_exists (char *path)
{
  int retval;

  if ((retval = validate_dir_path_exists (path)))
    return retval;
  else
    FAIL_MSG ("Invalid pathname : %s\n", path);
}

inline static  bool
xvalidate_address (char *addr)
{
  int retval;

  if ((retval = validate_address (addr)))
    return  retval;
  else
    FAIL_MSG ("Invalid address : %s\n", addr);
}

#endif // XVALIDATOR_H
