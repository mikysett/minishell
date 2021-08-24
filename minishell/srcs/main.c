#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	*minishell;

	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
		{
			add_history(line);
			minishell = parser(line);
			printf("line result: %s\n", line);
		}
		if (line)
			free(line);
	}
	// rl_clear_history(); // Compatibility issues with mac os
	return (0);
}
