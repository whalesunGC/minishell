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
	data->is_variable = 0;
	data->type = lexer_token_type_a(input, is_first_token);
	if (data->type == 42)
		data->type = lexer_token_type_b(input, in_quote, is_hd_delimiter,
				is_fd);
	if (data->type == TOKEN_VARIABLE)
		data->is_variable = 1;
	return (data);
}

static void	update_state_flags(t_lex_init_state *state, t_lex_data *data)
{
	state->is_first_token = (data->type == TOKEN_PIPE
			|| data->type == TOKEN_PARENTHESIS_L || data->type == TOKEN_AND_SEQ
			|| data->type == TOKEN_OR_SEQ);
	state->is_hd_delimiter = (data->type == TOKEN_HEREDOC);
	state->is_fd = (data->type == TOKEN_REDIRECTION_APPEND
			|| data->type == TOKEN_REDIRECTION_IN
			|| data->type == TOKEN_REDIRECTION_OUT);
	state->i++;
}

static t_list	*create_token_node(t_lex_init_state *state, char **tokens,
		t_list *first_node)
{
	t_lex_data	*data;
	t_list		*new_node;

	data = lexer_token_data(tokens[state->i], state->is_first_token,
			state->is_hd_delimiter, state->is_fd);
	if (!data)
		return (NULL);
	if (state->i == 0)
		first_node = ft_lstnew(data);
	else
	{
		new_node = ft_lstnew(data);
		ft_lstadd_back(&first_node, new_node);
	}
	update_state_flags(state, data);
	return (first_node);
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
	t_lex_init_state	*state;
	t_list				*first_node;

	state = NULL;
	state = ft_lexer_init_state(state);
	first_node = NULL;
	while (tokens[state->i])
	{
		first_node = create_token_node(state, tokens, first_node);
		if (!first_node)
			return (free(state), NULL);
	}
	free(state);
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

	if (!input)
		return (NULL);
	tokens = tokenize(input);
	if (!tokens)
		return (free(input), NULL);
	else
	{
		token_data = lexer_init_data(tokens);
		if (!token_data)
			return (ft_free_split(tokens), free(tokens), NULL);
	}
	return (ft_free_split(tokens), free(tokens), token_data);
}
