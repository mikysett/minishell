#include "minishell.h"

static int	add_env_vars(t_minishell *ms, int args_nb, char **argv);
static bool	add_sgl_env_var(t_minishell *ms, char *var_str);

int	export_builtin(char **argv)
{
	const int	args_nb = args_count(argv);
	t_minishell	*ms;
	int			i;

	ms = get_minishell(NULL);
	i = 0;
	if (args_nb < 2)
	{
		print_env_vars(*ms->env_vars);
		return (EXIT_SUCCESS);
	}
	else
		return (add_env_vars(ms, args_nb, argv));
}

static int	add_env_vars(t_minishell *ms, int args_nb, char **argv)
{
	int			exit_code;
	bool		vars_changed;
	int			i;

	vars_changed = false;
	exit_code = EXIT_SUCCESS;
	i = 0;
	while (i < args_nb)
	{
		if (!add_sgl_env_var(ms, argv[i]))
			exit_code = EXIT_FAILURE;
		else
			vars_changed = true;
		i++;
	}
	if (vars_changed)
		save_envp(ms);
	return (exit_code);
}

static bool	add_sgl_env_var(t_minishell *ms, char *var_str)
{
	t_list		*new_env_var_lst;
	t_env_var	*new_env_var;

	new_env_var_lst = save_env_var(var_str, env_key_len(var_str));
	new_env_var = (t_env_var *)new_env_var_lst->content;
	if (!is_valid_identifier(new_env_var->key))
	{
		print_identifier_error(ms->prog_name, "export", var_str);
		ft_lstdelone(new_env_var_lst, del_env_var);
		return (false);
	}
	else
	{
		ft_lstadd_back(ms->env_vars, new_env_var_lst);
		return (true);
	}
}