#include "minishell.h"

static char	*expand_exit_code(char *start_name, t_token *token);
static char	*expand_std_parameter(char *start_name, const char *par_name,
	t_token *token);

void	expand_parameter(char *start_name, int size_name, t_token *token)
{
	const char	*par_name = ft_strndup(start_name, size_name);

	if (!ft_strncmp(par_name, "$?", 3))
		token->str = expand_exit_code(start_name, token);
	else
		token->str = expand_std_parameter(start_name, par_name, token);
	free((void *)par_name);
}

static char	*expand_exit_code(char *start_name, t_token *token)
{
	const char	*exit_code = ft_itoa(get_minishell(NULL)->exit_code);
	const int	new_len = ft_strlen(token->str) + ft_strlen(exit_code) - 2;
	char		*new_str;

	new_str = calloc_or_exit(1, new_len + 1);
	ft_strlcat(new_str, token->str, start_name - token->str + 1);
	ft_strlcat(new_str, exit_code,
		ft_strlen(new_str) + ft_strlen(exit_code) + 1);
	ft_strlcat(new_str, start_name + 2,
		ft_strlen(new_str) + ft_strlen(start_name + 2) + 1);
	free((void *)exit_code);
	free(token->str);
	return (new_str);
}

static char	*expand_std_parameter(char *start_name, const char *par_name,
	t_token *token)
{
	const char	*par_value = get_env_var_value(*(get_minishell(NULL)->env_vars),
		par_name + 1);
	const int	par_name_len = ft_strlen(par_name);
	char		*new_str;

	if (par_value == NULL)
	{
		new_str = calloc_or_exit(1, ft_strlen(token->str)
			- par_name_len + 1);
		ft_strlcat(new_str, token->str, start_name - token->str + 1);
		ft_strlcat(new_str, start_name + par_name_len,
			ft_strlen(new_str) + ft_strlen(start_name + par_name_len) + 1);
	}
	else
	{
		new_str = calloc_or_exit(1, ft_strlen(token->str)
			+ ft_strlen(par_value) - par_name_len + 1);
		ft_strlcat(new_str, token->str, start_name - token->str + 1);
		ft_strlcat(new_str, par_value,
			ft_strlen(new_str) + ft_strlen(par_value) + 1);
		ft_strlcat(new_str, start_name + par_name_len,
			ft_strlen(new_str) + ft_strlen(start_name + par_name_len) + 1);
	}
	free(token->str);
	return (new_str);
}
