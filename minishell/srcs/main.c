#include "minishell.h"

static void	interactive_mode(t_minishell *minishell);
static void	non_interactive_mode(t_minishell *minishell, char *bash_file);
static void	process_line(t_minishell *ms, char *line);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	int			exit_code;

	minishell = init_minishell(envp);
	if (argc == 1)
		interactive_mode(minishell);
	else
		non_interactive_mode(minishell, argv[1]);
	exit_code = minishell->exit_code;
	free_minishell(minishell);
	return (exit_code);
}

static void	interactive_mode(t_minishell *ms)
{
	char	*line;

	while (1)
	{
		DEBUG(
			char prompt[80];
			sprintf(prompt, "minishell (%d)$ ", ms->exit_code);
			line = readline(prompt);
		)
		if (line && *line)
		{
			add_history(line);
			process_line(ms, line);
		}
		if (line)
			free(line);
		prog_state(PROG_OK);
	}
	// rl_clear_history(); // Compatibility issues with mac os
}

static void	non_interactive_mode(t_minishell *ms, char *bash_file)
{
	const int	bash_file_fd = ft_init_file_fd(bash_file, O_RDONLY, 0);
	char		*line;
	int			line_read_result;

	if (bash_file_fd == -1)
	{
		ms->exit_code = EXIT_FILE_NOT_FOUND;
		return ;
	}
	line_read_result = 1;
	while (line_read_result && prog_state(TAKE_STATE) == PROG_OK)
	{
		line_read_result = get_next_line(bash_file_fd, &line);
		if (line_read_result == -1)
		{
			perror(ms->prog_name);
			ms->exit_code = EXIT_FAILURE;
			break ;
		}	
		process_line(ms, line);
		free(line);
	}
	close(bash_file_fd);
}

static void	process_line(t_minishell *ms, char *line)
{
	if (line && *line)
	{
		ms = parser(line, ms);
		if (prog_state(TAKE_STATE) == PROG_OK)
		{
			ms->exit_code = executor(ms, *ms->instructions, EXIT_SUCCESS);
			restore_std_io(false, false);
		}
		else
			ms->exit_code = EXIT_INCORRECT_USAGE;
		reset_minishell(ms);
	}
}
