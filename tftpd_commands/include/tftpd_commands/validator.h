#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/fcntl.h>
#include <sys/types.h>
#include <dirent.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "parse_address.h"


#if !defined(VALIDATOR_H)
#define VALIDATOR_H

bool validate_dir_path_exists (char *path);

bool validate_address (char *addr);

bool have_read_access (char *filename);

bool have_write_access (char *filename);

bool have_write_access_current_dir();

#endif // VALIDATOR_H
