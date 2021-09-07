#ifndef PARSER_H
# define PARSER_H

t_minishell		*parser(char *line, t_minishell *minishell);

// LEXER
t_list			**lexer(char *line, t_list **tokens);

// TOKENS
char			*get_token_end(char *str, t_token *token);

// LEXER_UTILS
bool			is_operator(char *str);
char			*next_non_space(char *str);

// PARSER_UTILS
int				is_paren_op(t_token *token);
int				is_logic_op(t_token *token);
int				is_redir_op(t_token *token);
int				take_length_of_command(t_list *node);
t_cmd			*init_instruction(t_minishell *ms, t_instr_type type);
int				get_redir_type(t_token *token);

#endif
