#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

// CMD_BUILTIN_UTIL
int	args_count(char **argv);

int	echo_builtin(char **argv);
int	cd_builtin(char **argv);
int	pwd_builtin(char **argv);

#endif
