/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:25:30 by wichee            #+#    #+#             */
/*   Updated: 2024/10/07 12:26:02 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: lexer_token_type_a
 * @brief: to match the input string to the correct token type
 *
 * @param input: input token that will be a string
 * @param is_first_token: flag to indicate if the token is the first token
 * @return: the correct token type
 */
t_token_type	lexer_token_type_a(char *input, int is_first_token)
{
	if (ft_strncmp(input, ">>", 2) == 0)
		return (TOKEN_REDIRECTION_APPEND);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(input, ">", 1) == 0)
		return (TOKEN_REDIRECTION_OUT);
	else if (ft_strncmp(input, "<", 1) == 0)
		return (TOKEN_REDIRECTION_IN);
	else if (ft_strncmp(input, "(", 1) == 0)
		return (TOKEN_PARENTHESIS_L);
	else if (ft_strncmp(input, ")", 1) == 0)
		return (TOKEN_PARENTHESIS_R);
	else if (ft_strncmp(input, "&&", 2) == 0)
		return (TOKEN_AND_SEQ);
	else if (ft_strncmp(input, "||", 2) == 0)
		return (TOKEN_OR_SEQ);
	else if (ft_strncmp(input, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (is_first_token)
		return (TOKEN_COMMAND);
	else
		return (42);
}

/**
 * @function: lexer_token_type_b
 * @brief: to match the input string to the correct token type
 *
 * @param input: input token that will be a string
 * @param in_quote: flag to indicate if token is in_quotes
 * @param is_hd_delimiter: flag to indicate if token is a delimiter for
 * heredoc
 * @param is_fd: flag to indicate if a token is a file descriptor that follows
 * a redirection
 * @return: the correct token type
 */
t_token_type	lexer_token_type_b(char *input, int in_quote,
		int is_hd_delimiter, int is_fd)
{
	if (is_hd_delimiter && in_quote)
		return (TOKEN_HD_DELIMITER_Q);
	else if (is_hd_delimiter && !in_quote)
		return (TOKEN_HD_DELIMITER_NQ);
	else if (is_fd)
		return (TOKEN_RD_FD);
	else if (in_quote)
		return (TOKEN_INQUOTE);
	else if (ft_strncmp(input, "$", 1) == 0)
		return (TOKEN_VARIABLE);
	else
		return (TOKEN_STRING);
}

/**
 * @function: lexer_token_type_c
 * @brief: to match the input string to the correct token type
 *
 * @param input: input token that will be a string
 * @param in_quote: flag to indicate if token is in_quotes
 * @param is_hd_delimiter: flag to indicate if token is a delimiter for
 * heredoc
 * @param is_fd: flag to indicate if a token is a file descriptor that follows
 * a redirection
 * @return: the correct token type
 */
t_token_type	lexer_token_type_c(char *input, int in_quote,
		int is_hd_delimiter, int is_fd)
{
	(void)*input;
	if (is_hd_delimiter && in_quote)
		return (TOKEN_HD_DELIMITER_Q);
	else if (is_hd_delimiter && !in_quote)
		return (TOKEN_HD_DELIMITER_NQ);
	else if (is_fd)
		return (TOKEN_RD_FD);
	else if (in_quote)
		return (TOKEN_INQUOTE);
	else
		return (TOKEN_STRING);
}

/**
 * @function: tokenize
 * @brief: takes input string and splits the words into tokens
	 without any classification.
 *
 * @param input: string after first expansion
 *
 * @return: returns a list of strings, char **tokens
 */
char	**tokenize(char *input)
{
	char	**tokens;

	tokens = ft_split_ignore_quotes(input, ' ');
	return (tokens);
}
