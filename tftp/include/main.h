
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "error_handling.h"

#include "tftp_commands/tftp.h"
#include "tftp_commands/messages.h"
#include "tftp_commands/validator.h"
#include "tftp_commands/tftp_cmdtbl.h"

#include "messages.h"

#if !defined(MAIN_H)
#define MAIN_H

#define PROMPT_GET_IP   "(to) "
#define PROMPT          "tftp> "

#endif // MAIN_H
