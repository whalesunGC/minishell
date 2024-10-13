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
 * @return: the correct token type
 */
t_token_type	lexer_token_type(const char *input)
{
	if (*input == '\'' || *input == '"')
	{
		return (TOKEN_COMMAND);
	}
	else if (ft_strncmp(input, "|", 1) == 0)
	{
		return (TOKEN_PIPE);
	}
	else if (ft_strncmp(input, "<", 1) == 0 || ft_strncmp(input, ">", 1) == 0)
	{
		return (TOKEN_REDIRECTION);
	}
	else if (ft_strncmp(input, "<<", 2 == 0 || ft_strncmp(input, ">>", 2) == 0))
	{
		return (TOKEN_HEREDOC);
	}
	return (0);
}

/**
 * @function: lexer_token_data
 * @brief: to create lex_data from a raw input string.
 * 
 * @param input: input token that will be a string
 * @return: a struct with raw_string data and token_type.
 */
t_lex_data	*lexer_token_data(char *input)
{
	t_lex_data	*data;

	data = malloc(sizeof(t_lex_data));
	if (!data)
		return (NULL);
	data->raw_string = ft_strdup(input);
	data->type = lexer_token_type(input);
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

	i = 0;
	while (tokens[i])
	{
		data = lexer_token_data(tokens[i]);
		if (i == 0)
			first_node = ft_lstnew(data);
		else
		{
			new_node = ft_lstnew(data);
			ft_lstadd_back(&first_node, new_node);
		}
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
	int		i;
	t_list	*token_data;
	t_list	*buffer;

	ft_printf("%s\n", input);
	tokens = tokenize(input);
	i = 0;
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
