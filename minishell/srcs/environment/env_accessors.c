#include "minishell.h"

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

bool	set_env_var(t_list **env_vars, t_env_var *new_var)
{
	
	return (true);
}