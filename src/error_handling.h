#if !defined(ERROR_HANDLING_H)
#define ERROR_HANDLING_H

#include "tftp.h"

/**
 * @brief helper function for handle `tftp_sock_init` errors
 *
 * @param port
 * @param ip
 * @return tftp_socket_t*
 */
static inline void
xtftp_sock_init (int port, const char *ip, char *mode)
{
  if (tftp_sock_init (port, ip, mode) == -1)
    {
      fprintf (stderr, "Couldn't create socket\n");
      exit (EXIT_FAILURE);
    }
}

#endif // ERROR_HANDLING_H
