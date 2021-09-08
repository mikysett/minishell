#include "minishell.h"

static void	update_pwd_vars(t_list **env_vars);

int	cd_builtin(char **argv)
{
	const int	args_nb = args_count(argv);
	t_minishell	*ms;

	ms = get_minishell(NULL);
	if (args_nb > 2)
	{
		ft_putstr_fd(ms->prog_name, STDERR_FILENO);
		ft_putstr_fd(": cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (args_nb != 2 || !*argv[1])
		return (EXIT_SUCCESS);
	if (chdir(argv[1]) == -1)
	{
		ft_putstr_fd(ms->prog_name, STDERR_FILENO);
		perror(": cd");
		return (EXIT_FAILURE);
	}
	update_pwd_vars(ms->env_vars);
	return (EXIT_SUCCESS);
}

// CD do not update OLDPWD if the chdir() is not successful
// CD do not create OLDPWD if it doesn't exist already
// same thing for PWD

// TODO implement it so it works as stated above

static void	update_pwd_vars(t_list **env_vars)
{
	const t_env_var *oldpwd = get_env_var(*env_vars, "OLDPWD");
	const t_env_var *pwd = get_env_var(*env_vars, "PWD");

	if (oldpwd && pwd)
	{
	}
}