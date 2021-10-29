/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:08 by apinto            #+#    #+#             */
/*   Updated: 2021/10/26 14:12:18 by apinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_signals(t_minishell *ms);
static void	new_line_handler(int signal);
static char	*update_prompt(char *prog_name, int exit_code, char separator);
static void	handle_null_line(t_minishell *ms);

void	interactive_mode(t_minishell *ms)
{
	char	*line;

	set_signals(ms);
	prog_state(PROG_READ);
	while (1)
	{
		ms->prompt = update_prompt(ms->prog_name, ms->exit_code, '$');
		line = readline(ms->prompt);
		if (prog_state(TAKE_STATE) == PROG_READ)
			prog_state(PROG_OK);
		if (!line)
			handle_null_line(ms);
		else if (*line)
		{
			add_history(line);
			process_line(ms, line);
		}
		if (line)
			free(line);
		prog_state(PROG_READ);
	}
}

static void	set_signals(t_minishell *ms)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror(ms->prog_name);
	if (signal(SIGINT, new_line_handler) == SIG_ERR)
		perror(ms->prog_name);
}

static void	new_line_handler(int signal)
{
	t_minishell			*ms;
	const t_prog_state	old_state = prog_state(TAKE_STATE);

	ms = get_minishell(NULL);
	ms->exit_code = EXIT_SIGINT;
	prog_state(SIGINT_RECEIVED);
	write(STDIN_FILENO, "\n", 1);
	if (signal == SIGINT && old_state == PROG_READ)
	{
		ms->streams.stdin_fd = ft_set_dup(STDIN_FILENO);
		if (ms->streams.stdin_fd == -1)
			ft_error_exit(ERR_NO_PRINT);
		close(STDIN_FILENO);
	}
}

// TODO this function should be heavely refactored
static char	*update_prompt(char *prog_name, int exit_code, char separator)
{
	static char	prompt[MAX_PROMPT_SIZE];

	sprintf(prompt, "%s (%d)%c ", prog_name, exit_code, separator);
	return (prompt);
}

static void	handle_null_line(t_minishell *ms)
{
	if (prog_state(TAKE_STATE) == SIGINT_RECEIVED)
	{
		ft_set_dup2(ms->streams.stdin_fd, STDIN_FILENO);
		close(ms->streams.stdin_fd);
	}
	else
		exit_builtin(NULL);
}
