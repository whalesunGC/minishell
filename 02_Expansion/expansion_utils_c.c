/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:31:58 by wichee            #+#    #+#             */
/*   Updated: 2024/11/14 17:32:01 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_word_split
 * @brief: handles additional word splitting after the expansion step
 *
 * @param string: input string
 * @param current_token: current token position
 * @return: current token position
 */
t_list	**handle_word_split(char *string, t_list **current_token)
{
	t_list	*node;
	t_list	*node_head;

	node = NULL;
	node_head = NULL;
	string = input_clean(string);
	node = lexer(string);
	if (!node)
		return (free(string), current_token);
	else
	{
		free(((t_lex_data *)((*current_token)->content))->raw_string);
		((t_lex_data *)((*current_token)->content))->raw_string = ft_strdup(
				((t_lex_data *)(node->content))->raw_string);
		node_head = node;
		node = node->next;
		*current_token = ft_lstinsert(node, *current_token);
	}
	return (ft_free_lex_data(node_head->content), free(node_head),
		free(string), current_token);
}

/*/**
 * @function: ft_lstinsert
 * @brief: inserts lst into lst
 *
 * @param node: new list
 * @param current: current list
 * @return: pointer to head of current list
 */
t_list	*ft_lstinsert(t_list *node, t_list *current)
{
	t_list	*current_next;
	t_list	*current_head;

	current_head = current;
	current_next = current->next;
	current->next = node;
	while (current->next)
		current = current->next;
	current->next = current_next;
	return (current_head);
}

/**
 * @function: ft_has_whitespace
 * @brief: checks if string has whitespace
 *
 * @param string: input string
 * @return: 1 or 0
 */
int	ft_has_whitespace(char *string)
{
	if (!string)
		return (0);
	while (*string)
	{
		if (ft_iswhitespace(*string))
			return (1);
		string++;
	}
	return (0);
}

/**
 * @function: ft_remove_quote
 * @brief: removes all quotes from input string, returns new string
 *
 * @param string: input string
 * @return: new string with no quotes
 */
char	*ft_remove_quote(char *string)
{
	int	i;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"')
			string = ft_str_replace(string, i, "");
		else
			i++;
	}
	return (string);
}

/**
 * @function: ft_has_quote
 * @brief: checks if quotes exist in string
 *
 * @param string: input string
 * @return: 1 or 0
 */
int	ft_has_quote(char *string)
{
	if (!string)
		return (0);
	while (*string)
	{
		if (*string == '\'' || *string == '\"')
			return (1);
		string++;
	}
	return (0);
}
