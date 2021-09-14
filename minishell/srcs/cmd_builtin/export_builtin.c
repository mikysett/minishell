#include "minishell.h"

static int	add_env_vars(t_minishell *ms, int args_nb, char **argv);
static int	add_sgl_env_var(t_minishell *ms, char *var_str);

int	export_builtin(char **argv)
{
	const int	args_nb = args_count(argv);
	t_minishell	*ms;

	ms = get_minishell(NULL);
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
	int		exit_code;
	bool	vars_changed;
	int		add_sgl_result;
	int		i;

	vars_changed = false;
	exit_code = EXIT_SUCCESS;
	i = 1;
	while (i < args_nb)
	{
		add_sgl_result = add_sgl_env_var(ms, argv[i]);
		if (add_sgl_result == -1)
			exit_code = EXIT_FAILURE;
		else if (add_sgl_result == 1)
			vars_changed = true;
		i++;
	}
	if (vars_changed)
	{
		save_envp(ms);
		ms->paths = ft_set_paths(ms->envp);
	}
	return (exit_code);
}

static int	add_sgl_env_var(t_minishell *ms, char *var_str)
{
	t_list		*new_env_var_lst;
	t_env_var	*new_env_var;

	new_env_var_lst = save_env_var(var_str, env_key_len(var_str));
	new_env_var = (t_env_var *)new_env_var_lst->content;
	if (!is_valid_identifier(new_env_var->key))
	{
		print_identifier_error(ms->prog_name, "export", var_str);
		ft_lstdelone(new_env_var_lst, del_env_var);
		return (-1);
	}
	else
	{
		if (set_env_var(ms->env_vars, new_env_var_lst) == true)
			return (1);
		else
			return (0);
	}
}