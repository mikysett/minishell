#include "minishell.h"

static int	nb_vars_with_value(t_list *env_vars);
static char	*save_var_in_envp(t_env_var *env_var);

void	save_envp(t_minishell *ms)
{
	const int	vars_nb = nb_vars_with_value(*ms->env_vars);
	int			i;
	t_list		*env_var;
	t_env_var	*curr_var;

	i = 0;
	env_var = *ms->env_vars;
	ft_free_str_arr(ms->envp);
	ms->envp = calloc_or_exit(vars_nb + 1, sizeof(char *));
	while (env_var)
	{
		curr_var = (t_env_var *)env_var->content;
		if (curr_var->value)
		{
			ms->envp[i] = save_var_in_envp(curr_var);
			i++;
		}
		env_var = env_var->next;
	}
}

static int	nb_vars_with_value(t_list *env_vars)
{
	int			vars_nb;
	t_env_var	*curr_env_var;

	vars_nb = 0;
	while (env_vars)
	{
		curr_env_var = (t_env_var *)env_vars->content;
		if (curr_env_var->value)
			vars_nb++;
		env_vars = env_vars->next;
	}
	return (vars_nb);
}

static char	*save_var_in_envp(t_env_var *env_var)
{
	const int	tot_str_len = ft_strlen(env_var->key)
		+ ft_strlen(env_var->value) + 2;
	char		*var_str;

	var_str = calloc_or_exit(tot_str_len, sizeof(char));
	ft_strlcat(var_str, env_var->key, tot_str_len);
	ft_strlcat(var_str, "=", tot_str_len);
	ft_strlcat(var_str, env_var->value, tot_str_len);
	return (var_str);
}
