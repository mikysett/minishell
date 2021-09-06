#include "minishell.h"

t_list	**init_env_vars(char **envp)
{
	t_list		**env_vars;
	int			i;
	int			curr_key_len;

	if (!envp || !*envp)
		return (NULL);
	env_vars = calloc_or_exit(1, sizeof(t_list *));
	i = -1;
	while (envp[++i])
	{
		curr_key_len = env_key_len(envp[i]);
		if (!strncmp("OLDPWD=", envp[i], curr_key_len + 1))
			continue ;
		ft_lstadd_back(env_vars, save_env_var(envp[i], curr_key_len));
	}
	ft_lstadd_back(env_vars, save_env_var("OLDPWD", 6));
	return (env_vars);
}

int	env_key_len(char *str)
{
	const char	*o_str = str;

	if (!str)
		return (0);
	while (*str && *str != '=')
		str++;
	return (str - o_str);
}

t_list	*save_env_var(char *var_str, int key_len)
{
	t_list		*new_var;
	t_env_var	*curr_var;

	curr_var = calloc_or_exit(1, sizeof(t_env_var));
	curr_var->key = ft_strndup(var_str, key_len);
	if (var_str[key_len] == '=')
		curr_var->value = ft_strdup(var_str + key_len + 1);
	new_var = ft_lstnew(curr_var);
	if (!new_var)
		ft_error_exit(MEMORY_FAIL);
	return (new_var);
}
