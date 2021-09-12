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


#if !defined(VALIDATOR_H)
#define VALIDATOR_H

#define MAX_PORT_NUMBER   6553

bool validate_dir_path_exists(char *path);

bool validate_address(char *addr);

#endif // VALIDATOR_H
