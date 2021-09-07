/**
 * @file file.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "tftp_commands/file.h"

#define CURRENT_FOLDER "."

bool
current_folder_waccess()
{
  return (bool)!access (CURRENT_FOLDER, W_OK);
}