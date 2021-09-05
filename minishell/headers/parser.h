#ifndef PARSER_H
# define PARSER_H

t_minishell		*parser(char *line, t_minishell *minishell);

// LEXER
t_list			**lexer(char *line, t_list **tokens);
t_token			*init_token(char *token_start);
t_quote_type	get_quote_type(char token_start);

// TOKENS
t_token_type	get_token_type(char *token_start);
char			*get_token_end(char *str, t_token *token);
void			save_token(t_list **tokens, t_token *curr_token);

// LEXER_UTILS
bool			is_operator(char *str);
char			*next_token(char *s, t_quote_type token_type);

// PARSER_UTILS
int				is_paren_op(char *str);
int				is_logic_op(char *str);
int				is_redir_op(char *str);
int				take_length_of_command(t_list *node);
t_cmd			*init_instruction(t_minishell *ms);
int				get_redir_type(t_token *token);

#endif
