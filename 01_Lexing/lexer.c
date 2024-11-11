/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:58:49 by wichee            #+#    #+#             */
/*   Updated: 2024/10/23 18:09:17 by wichee           ###   ########.fr       */
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
 * @function: lexer_token_data
 * @brief: to create lex_data from a raw input string.
 *
 * @param input: input token that will be a string
 * @param is_first_token: flag to indicate if the token is the first token
 * @return: a struct with raw_string data and token_type.
 */
t_lex_data	*lexer_token_data(char *input, int is_first_token,
		int is_hd_delimiter, int is_fd)
{
	t_lex_data	*data;
	int			in_quote;

	in_quote = 0;
	if (!input)
		return (NULL);
	if (*input == '\'' || *input == '\"')
		in_quote = !in_quote;
	data = malloc(sizeof(t_lex_data));
	if (!data)
		return (NULL);
	data->raw_string = ft_strdup(input);
	data->is_first_token = is_first_token;
	data->in_quote = in_quote;
	data->is_hd_delimiter = is_hd_delimiter;
	data->is_fd = is_fd;
	data->type = lexer_token_type_a(input, is_first_token);
	if (data->type == 42)
		data->type = lexer_token_type_b(input, in_quote, is_hd_delimiter,
				is_fd);
	return (data);
}

/**
 * @function: lexer_init_data
 * @brief: inits a linked-list of structs that contain 1)the raw token string,
 * 2)the token_type 3)inquote flag 4)first_token flag 5)is_delimiter 6)is_fd
 *
 * @param tokens: an array of strings, each string is a token that needs to
 * be lexed.
 *
 * @return: returns a pointer to the first node of the linked-list
 */
t_list	*lexer_init_data(char **tokens)
{
	int			i;
	t_lex_data	*data;
	t_list		*new_node;
	t_list		*first_node;
	int			is_first_token;
	int			is_hd_delimiter;
	int			is_fd;

	i = 0;
	new_node = NULL;
	first_node = NULL;
	is_first_token = 1;
	is_hd_delimiter = 0;
	is_fd = 0;
	while (tokens[i])
	{
		data = lexer_token_data(tokens[i], is_first_token, is_hd_delimiter,
				is_fd);
		if (!data)
			return (NULL);
		if (i == 0)
			first_node = ft_lstnew(data);
		else
		{
			new_node = ft_lstnew(data);
			ft_lstadd_back(&first_node, new_node);
		}
		is_first_token = (data->type == TOKEN_PIPE)
			|| (data->type == TOKEN_PARENTHESIS_L || data->type == TOKEN_AND_SEQ
				|| data->type == TOKEN_OR_SEQ);
		is_hd_delimiter = (data->type == TOKEN_HEREDOC);
		is_fd = (data->type == TOKEN_REDIRECTION_APPEND
				|| data->type == TOKEN_REDIRECTION_IN
				|| data->type == TOKEN_REDIRECTION_OUT);
		i++;
	}
	return (first_node);
}

/**
 * @function: lexer
 * @brief: this is the entry point to the lexer module.
 *
 * @param input: string after cleaning.
 *
 * @return: returns a linked-list "data" which is a stream of tokens
 * if created or NULLL if not.
 */
t_list	*lexer(char *input)
{
	char	**tokens;
	t_list	*token_data;

	ft_printf("%s\n", input);
	tokens = tokenize(input);
	if (!tokens)
		return (free(input), NULL);
	else
	{
		token_data = lexer_init_data(tokens);
		if (!token_data)
		ft_print_tokens(token_data);
	}
	return (ft_free_split(tokens), free(tokens), token_data);
}
