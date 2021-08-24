#ifndef PARSER_H
# define PARSER_H

t_minishell		*parser(char *line, t_minishell *minishell);

// LEXER
t_list			**lexer(char *line, t_list **tokens);
char			*next_non_space(char *str);
t_token			*init_token(char *token_start);
t_quote_type	get_quote_type(char token_start);
t_token_type	get_token_type(char *token_start);
char			*get_token_end(char *str, t_token *token);
char			*get_token_operator_end(char *str);
char			*get_token_word_end(char *str, t_quote_type quote_type);
bool			is_operator(char *str);
void			save_token(t_list **tokens, t_token *curr_token);
char			*next_token(char *s, t_quote_type token_type);

#endif
