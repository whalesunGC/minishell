/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:01:18 by wichee            #+#    #+#             */
/*   Updated: 2024/10/13 16:13:21 by wichee           ###   ########.fr       */
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
	TOKEN_WILDCARD,
	TOKEN_VARIABLE
}					t_token_type;

typedef struct s_lex_data
{
	t_token_type	type;
	char			*raw_string;
	int				in_quote;
	int				is_first_token;
}					t_lex_data;

// lexer.c
t_list			*lexer(char *input);
t_lex_data		*lexer_token_data(char *input, int is_first_token);
t_list			*lexer_init_data(char **tokens);
t_token_type	lexer_token_type(const char *input, int is_first_token,
	int in_quote, int is_var);

// tokenize.c
char			**tokenize(char *input);

// lexer Utils
void			ft_free_split(char **split);
void			ft_free_lex_data(void *data);
void			ft_print_tokens(t_list *token_data);

// ft_split_ignore_quotes.c
char			**ft_split_ignore_quotes(const char *s, char c);
char			*ft_strchr_ignore_quotes(const char *s, int c);
#endif
