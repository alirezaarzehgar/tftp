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
static inline tftp_socket_t *
xtftp_sock_init (int port, const char *ip)
{
  tftp_socket_t *tst = tftp_sock_init (port, ip);

  if (tst == NULL)
    {
      fprintf (stderr, "Couldn't create socket\n");
      exit (EXIT_FAILURE);
    }

  return tst;
}

#endif // ERROR_HANDLING_H
