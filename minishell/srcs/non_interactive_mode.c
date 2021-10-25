#include "minishell.h"

void	non_interactive_mode(t_minishell *ms, char *bash_file)
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

void	process_line(t_minishell *ms, char *line)
{
	if (line && *line)
	{
		ms = parser(line, ms);
		if (prog_state(TAKE_STATE) == PROG_OK)
		{
			ms->exit_code = executor(ms, *ms->instructions, ms->exit_code);
			restore_std_io(false, false);
		}
		else
			ms->exit_code = EXIT_PARSER_ERROR;
		reset_minishell(ms);
	}
}
