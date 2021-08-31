#ifndef DEBUG_H
# define DEBUG_H

void	print_tokens(t_list **tokens);
void	create_fake_cmd(t_minishell *ms);
void	print_redirections(t_list **redir);
void	print_instructions(t_list **instr);

#endif