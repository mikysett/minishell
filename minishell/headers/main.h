#ifndef MAIN_H
# define MAIN_H

// INTERACTIVE_MODE
void	interactive_mode(t_minishell *ms);

// NON_INTERACTIVE_MODE
void	non_interactive_mode(t_minishell *ms, char *bash_file);
void	process_line(t_minishell *ms, char *line);

#endif