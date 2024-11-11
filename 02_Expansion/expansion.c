/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:01:41 by wichee            #+#    #+#             */
/*   Updated: 2024/10/07 18:04:48 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_env_len
 * @brief: Calculates the length of an environment variable name
 * 
 * @param input: The input string starting with the variable name
 * @return: The length of the environment variable name
 */
int	ft_env_len(const char *input)
{
	int	len;

	len = 0;
	if (input[len] == '$')
	{
		len++;
		while (input[len] && (ft_isalnum(input[len]) || input[len] == '_'))
			len++;
	}
	else
		len = 1;
	return (len);
}

/**
 * @function: ft_var_exp
 * @brief: takes an input that starts with a '$',
 	finds the env variable and replaces inplace.
 * 
 * @param input: the address to the pointer of the input string.
 * @param start_index: an int which represents the starting
 	index that points to a '$'
 * 
 * @return: returns a string with the '$VAR' replaced with
 	its corresponding env variable if found, else it returns
	a string with '$VAR' replaced with a NULL 
 */

char	*ft_var_exp(char **input, int start_index, char **env)
{
	int		env_len;
	char	*var;
	char	*env_var;

	env_len = ft_env_len(*input + start_index);
	var = ft_substr(*input + start_index, 0, env_len);
	ft_printf("variable found: %s\n", var);
	env_var = ft_env_search(var, env);
	return (free(var), env_var);
}
/**
 * @function: expansion
 * @brief: takes input string and does variable expansion.
 * 
 * @param input: any string, note that this
 	is malloced and needs to be freed after use.
	@param ignore_quote: flag to check if expansion should
 * ignore quotes.
 * 
 * 
 * @return: returns expanded string or NULL if expansion fails.
 */

char	*expansion_string(char *input, int ignore_quote, char **env)
{
	char	*env_var;
	int		in_single_quote;
	int		i;

	in_single_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			in_single_quote = !in_single_quote;
			i++;
		}
		else if ((input[i] == '$' && ft_is_env(input[i + 1]))
			&& (!in_single_quote || ignore_quote))
		{
			env_var = ft_var_exp(&input, i, env);
			expansion_replace_string(env_var, i, &input);
			if (env_var)
			{
				i += ft_strlen(env_var);
				free(env_var);
			}
		}
		else
			i++;
	}
	return (input);
}

/**
 * @function: expansion
 * @brief: iterates through linked-list and does expansion via
 * variable substitution on raw_string.
 * 
 * @param token_data: linked-list of lexed token_data
 * @return: linked-list of token_data with expansion
 */
t_list	*expansion(t_list *token_data, char **env)
{
	t_list		*head;

	head = token_data;
	if (!token_data)
		return (NULL);
	else
		while (token_data != NULL)
			token_data = ft_expansion_tokens(&token_data, env);
	ft_print_tokens(head);
	return (head);
}
