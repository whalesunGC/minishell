/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:01:18 by wichee            #+#    #+#             */
/*   Updated: 2024/10/19 18:24:06 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_STRING,
	TOKEN_INQUOTE,
	TOKEN_PIPE,
	TOKEN_REDIRECTION_OUT,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PARENTHESIS_L,
	TOKEN_PARENTHESIS_R,
	TOKEN_AND_SEQ,
	TOKEN_OR_SEQ,
	TOKEN_VARIABLE,
	TOKEN_HD_DELIMITER_Q,
	TOKEN_HD_DELIMITER_NQ,
	TOKEN_RD_FD
}					t_token_type;

typedef struct s_lex_data
{
	t_token_type	type;
	char			*raw_string;
	int				in_quote;
	int				is_first_token;
	int				is_hd_delimiter;
	int				is_fd;
	int				is_variable;
}					t_lex_data;

typedef struct s_lex_init_state
{
	int				i;
	int				in_quote;
	int				is_first_token;
	int				is_hd_delimiter;
	int				is_fd;
}					t_lex_init_state;

// lexer.c
t_list				*lexer(char *input, char **env);
t_lex_data			*lexer_token_data(char *input, int is_first_token,
						int is_hd_delimiter, int is_fd);
t_list				*lexer_init_data(char **tokens, char **env);

// tokenize.c
char				**tokenize(char *input);
t_token_type		lexer_token_type_a(char *input, int is_first_token);
t_token_type		lexer_token_type_b(char *input, int in_quote,
						int is_hd_delimiter, int is_fd);
t_token_type		lexer_token_type_c(char *input, int in_quote,
						int is_hd_delimiter, int is_fd);
void				handle_retokenize(t_lex_data *data);
// lexer Utils
void				ft_free_split(char **split);
void				ft_free_lex_data(void *data);
void				ft_print_tokens(t_list *token_data);
t_lex_init_state	*ft_lexer_init_state(t_lex_init_state *state);
int					has_valid_variable(char *input, char **env);

// ft_split_ignore_quotes.c
char				**ft_split_ignore_quotes(const char *s, char c);
char				*ft_strchr_ignore_quotes(const char *s, int c);
#endif
