#ifndef DEBUG_H
# define DEBUG_H

void	print_tokens(t_list **tokens);
void	create_fake_cmd0(t_minishell *ms);
void	create_fake_cmd1(t_minishell *ms);
void	create_fake_cmd2(t_minishell *ms);
void	create_fake_cmd3(t_minishell *ms);
void	create_fake_cmd4(t_minishell *ms);
void	create_fake_cmd5(t_minishell *ms);
void	print_redirections(t_list **redir);
void	print_instructions(t_list **instr);

#endif