#ifndef CMD_BUILTIN_H
# define CMD_BUILTIN_H

// CMD_BUILTIN_UTIL
<<<<<<< HEAD
int	args_count(char **argv);

int	echo_builtin(char **argv);
int	cd_builtin(char **argv);
int	pwd_builtin(char **argv);
=======
int		args_count(char **argv);
bool	is_valid_identifier(char *str);
void	print_identifier_error(char *prog_name, char *builtin_name,
	char *invalid_identifier);

int		echo_builtin(char **argv);
int		cd_builtin(char **argv);
int		pwd_builtin(char **argv);
int		export_builtin(char **argv);
int		unset_builtin(char **argv);
int		env_builtin(char **argv);
int		exit_builtin(char **argv);
>>>>>>> master

#endif
