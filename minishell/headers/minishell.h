#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef DEBUG_MODE
#  define DEBUG(x) x
# else
#  define DEBUG(x)
# endif

# define __FD_SETSIZE 1024

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stddef.h>
# include <sys/errno.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "get_next_line.h"
# include "types.h"

# include "debug.h"

# include "main.h"
# include "core.h"
# include "parser.h"
# include "executor.h"
# include "environment.h"
# include "cmd_builtin.h"

#endif
