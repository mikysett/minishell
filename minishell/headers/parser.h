#ifndef PARSER_H
# define PARSER_H

// PARSER
t_minishell		*parser(char *line, t_minishell *minishell);

// LEXER
t_list			**lexer(char *line, t_list **tokens);

// QUOTE_UTIL
t_quote_type	get_quote_type(char c);
bool			update_quote_type(t_quote_type curr, t_quote_type *prev);

// TOKENS
char			*get_token_end(char *str, t_token *token);

// PERFORM_EXPANSIONS
void			perform_expansions(t_list **tokens);

// FILENAME_EXPANSION
void			filename_expansion(t_list **tokens);
void			save_expansion_if_match(t_list **new_tokens, char *d_name,
					char *token_str);

// QUOTE_REMOVAL
void			quote_removal(t_list *curr_token_lst);

// LEXER_UTILS
bool			is_operator(char *str);
char			*next_non_space(char *str);

// PARSER_UTILS
int				is_paren_op(t_token *token);
int				is_logic_op(t_token *token);
int				is_redir_op(t_token *token);
int				take_length_of_command(t_list *node);
t_cmd			*init_instruction(t_minishell *ms, t_instr_type type);
t_redirect		*init_redirection(t_minishell *ms, t_redir_type type);
int				get_redir_type(t_token *token);

#endif
