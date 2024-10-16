/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:58:49 by wichee            #+#    #+#             */
/*   Updated: 2024/10/05 12:00:58 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: lexer_token_type
 * @brief: to match the input string to the correct token type
 * 
 * @param input: input token that will be a string
 * @param is_first_token: flag to indicate if the token is the first token
 * @return: the correct token type
 */
t_token_type	lexer_token_type(const char *input, int is_first_token)
{
	// Check for operators first
	if (ft_strncmp(input, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(input, ">", 1) == 0)
		return (TOKEN_REDIRECTION_STDOUT);
	else if (ft_strncmp(input, "<", 1) == 0)
		return (TOKEN_REDIRECTION_STDIN);
	else if (ft_strncmp(input, ">>", 2) == 0)
		return (TOKEN_REDIRECTION_APPEND);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(input, "(", 1) == 0)
		return (TOKEN_PARENTHESIS_L);
	else if (ft_strncmp(input, ")", 1) == 0)
		return (TOKEN_PARENTHESIS_R);
	else if (ft_strncmp(input, "&&", 2) == 0)
		return (TOKEN_AND);	
	else if (ft_strncmp(input, "||", 2) == 0)
		return (TOKEN_OR);
	else if (ft_strncmp(input, "*", 1) == 0)
		return (TOKEN_WILDCARD);
	else if (is_first_token)
		return (TOKEN_COMMAND);
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
t_lex_data	*lexer_token_data(char *input, int is_first_token)
{
	t_lex_data	*data;

	data = malloc(sizeof(t_lex_data));
	if (!data)
		return (NULL);
	data->raw_string = ft_strdup(input);
	data->type = lexer_token_type(input, is_first_token);
	return (data);
}

/**
 * @function: lexer_init_data
 * @brief: inits a linked-list of structs that contain 1)the raw token string,
 * the token_type and 
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

	i = 0;
	new_node = NULL;
	first_node = NULL;
	is_first_token = 1;  // Start with true for the first token
	while (tokens[i])
	{
		data = lexer_token_data(tokens[i], is_first_token);
		if (i == 0)
			first_node = ft_lstnew(data);
		else
		{
			new_node = ft_lstnew(data);
			ft_lstadd_back(&first_node, new_node);
		}
		is_first_token = (data->type == TOKEN_PIPE);
		i++;
	}
	return (first_node);
}

/**
 * @function: lexer
 * @brief: this is the entry point to the lexer module.
 * 
 * @param input: string after expansion (variable expansion, 
 * command substition and globbing).
 *
 * @return: returns a linked-list "data" which is a stream of tokens
 * if created or NULLL if not.
 */
t_list	*lexer(char *input)
{
	char	**tokens;
	t_list	*token_data;
	t_list	*buffer;

	ft_printf("%s\n", input);
	tokens = tokenize(input);
	if (!tokens)
		return (free(input), NULL);
	else
	{
		token_data = lexer_init_data(tokens);
		buffer = token_data;
		while (buffer)
		{
			ft_printf("Token is %s, Token Type is %d\n",
				((t_lex_data *)(buffer->content))->raw_string,
				((t_lex_data *)(buffer->content))->type);
			buffer = buffer->next;
		}
	}
	return (ft_free_split(tokens), free(tokens), token_data);
}
