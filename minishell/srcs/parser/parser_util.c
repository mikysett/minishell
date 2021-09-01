#include "minishell.h"

int		is_redir_op(char *str)
{
	return (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0
			|| ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0
			|| ft_strncmp(str, "|", 1) == 0)
}

int		is_logic_op(char *str)
{
	return (ft_strncmp(str, "||", 2) == 0 || ft_strncmp(str, "&&", 2) == 0)
}

int		is_paren_op(char *str)
{
	return (ft_strncmp(str, "(", 1) == 0 || ft_strncmp(str, ")", 1) == 0)
}
