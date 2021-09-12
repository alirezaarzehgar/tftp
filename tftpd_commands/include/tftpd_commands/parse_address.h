#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#if !defined(ADDRESS_PARSER_H)
#define ADDRESS_PARSER_H

#define MAX_PORT_NUMBER   6553

bool parse_address (char *addr, char **ip, int *port);

#endif // ADDRESS_PARSER_H
