#include "minishell.h"

static void	update_env_var(t_env_var *old_var, t_env_var *new_var);

char	*get_env_var_value(t_list *env_vars, char *key)
{
	t_env_var	*curr_var;
	const int	key_size = ft_strlen(key) + 1;

	if (!key || !env_vars)
		return (NULL);
	while (env_vars)
	{
		curr_var = (t_env_var *)env_vars->content;
		if (!ft_strncmp(key, curr_var->key, key_size))
			return (curr_var->value);
		env_vars = env_vars->next;
	}
	return (NULL);
}

void	set_env_var(t_list **env_vars, t_list *new_var_lst)
{
	t_env_var	*new_var;
	t_list		*curr_var;
	t_env_var	*var_sel;
	int			new_var_key_size;

	new_var = (t_env_var *)new_var_lst->content;
	new_var_key_size = ft_strlen(new_var->key) + 1;
	curr_var = *env_vars;
	while (curr_var)
	{
		var_sel = (t_env_var *)curr_var->content;
		if (!ft_strncmp(var_sel->key, new_var->key, new_var_key_size))
		{
			update_env_var(var_sel, new_var);
			free(new_var_lst);
			return ;
		}
		curr_var = curr_var->next;
	}
	ft_lstadd_back(env_vars, new_var_lst);
}

static void	update_env_var(t_env_var *old_var, t_env_var *new_var)
{
	free(new_var->key);
	if (old_var->value)
		free(old_var->value);
	old_var->value = new_var->value;
	free(new_var);
}

bool	unset_env_var(t_list **env_vars, char *key)
{
	t_list		*curr_var;
	t_list		*prev_var;
	t_env_var	*var_sel;
	const int	key_size = ft_strlen(key) + 1;

	prev_var = NULL;
	curr_var = *env_vars;
	while (curr_var)
	{
		var_sel = (t_env_var *)curr_var->content;
		if (!ft_strncmp(var_sel->key, key, key_size))
		{
			if (!prev_var)
				*env_vars = curr_var->next;
			else
				prev_var->next = curr_var->next;
			ft_lstdelone(curr_var, del_env_var);
			return (true);
		}
		curr_var = curr_var->next;
	}
	return (false);
}