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

#endif
