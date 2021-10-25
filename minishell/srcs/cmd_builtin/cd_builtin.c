#include "minishell.h"

static int	update_pwd_vars(t_list **env_vars, const char *old_pwd_str);
static void	update_oldpwd_var(t_env_var *oldpwd, const char *old_pwd_str);
static int	update_pwd_var(t_env_var *pwd);

int	cd_builtin(char **argv)
{
	const int			args_nb = args_count(argv);
	const t_minishell	*ms = get_minishell(NULL);
	char				*old_pwd_str;

	if (args_nb > 2)
	{
		ft_putstr_fd(ms->prog_name, STDERR_FILENO);
		ft_putstr_fd(": cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (args_nb != 2 || !*argv[1])
		return (EXIT_SUCCESS);
	old_pwd_str = getcwd(NULL, 0);
	if (!old_pwd_str || chdir(argv[1]) == -1)
	{
		if (old_pwd_str)
			free((char *)old_pwd_str);
		ft_putstr_fd(ms->prog_name, STDERR_FILENO);
		perror(": cd");
		return (EXIT_FAILURE);
	}
	return (update_pwd_vars(ms->env_vars, old_pwd_str));
}

static int	update_pwd_vars(t_list **env_vars, const char *old_pwd_str)
{
	t_env_var	*oldpwd;
	t_env_var	*pwd;

	oldpwd = get_env_var(*env_vars, "OLDPWD");
	if (oldpwd)
		update_oldpwd_var(oldpwd, old_pwd_str);
	free((char *)old_pwd_str);
	pwd = get_env_var(*env_vars, "PWD");
	if (pwd)
		return (update_pwd_var(pwd));
	return (EXIT_SUCCESS);
}

static void	update_oldpwd_var(t_env_var *oldpwd, const char *old_pwd_str)
{
	if (oldpwd->value)
		free(oldpwd->value);
	oldpwd->value = strdup_or_exit((char *)old_pwd_str);
}

static int	update_pwd_var(t_env_var *pwd)
{
	if (pwd->value)
		free(pwd->value);
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
	{
		ft_putstr_fd(get_minishell(NULL)->prog_name, STDERR_FILENO);
		perror(": cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
