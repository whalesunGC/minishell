/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:01:18 by wichee            #+#    #+#             */
/*   Updated: 2024/10/05 12:02:06 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef	LEXER_H
# define LEXER_H

typedef enum
{
	TOKEN_COMMAND,      // Represents commands like "echo", "ls"
	TOKEN_STRING,       // Represents strings like "Hello, World"
	TOKEN_PIPE,     // Represents operators like ">", "|"
	TOKEN_REDIRECTION,   // Represents redirection symbols like ">", "<"
	TOKEN_HEREDOC,
	TOKEN_PARENTHESIS_L,
	TOKEN_PARENTHESIS_R
}	token_type;

typedef struct	s_lex_data
{
	token_type	type;
	char	*raw_string;
}	t_lex_data;

int		lexer(char *input);
char 	**tokenize(char *input);

//Lexer Utils
void	ft_free_split(char **split);

//ft_split_ignore_quotes.c
char	**ft_split_ignore_quotes(const char *s, char c);
char	*ft_strchr_ignore_quotes(const char *s, int c);

#endif