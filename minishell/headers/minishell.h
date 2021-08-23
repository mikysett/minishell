#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "types.h"
# include "core.h"
# include "parser.h"

#endif
