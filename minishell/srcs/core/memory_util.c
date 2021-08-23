#include "minishell.h"

void	*calloc_or_exit(size_t count, size_t size)
{
	void	*result;
	
	result = ft_calloc(count, size);
	if (!result)
		ft_error_exit(MEMORY_FAIL);
	return (result);
}