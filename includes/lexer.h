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
	TOKEN_PIPE,
	TOKEN_REDIRECTION_STDOUT,
	TOKEN_REDIRECTION_STDIN,
	TOKEN_REDIRECTION_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PARENTHESIS_L,
	TOKEN_PARENTHESIS_R,
}	t_token_type;

typedef struct s_lex_data
{
	t_token_type	type;
	char			*raw_string;
}	t_lex_data;

//Lexer.c
t_list	*lexer(char *input);
char	**tokenize(char *input);
//Lexer Utils
void	ft_free_split(char **split);
void	ft_free_lex_data(void *data);
//ft_split_ignore_quotes.c
char	**ft_split_ignore_quotes(const char *s, char c);
char	*ft_strchr_ignore_quotes(const char *s, int c);
#endif
