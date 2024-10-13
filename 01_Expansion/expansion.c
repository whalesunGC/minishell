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
 * @function: expansion_replace_string
 * @brief: string replacement function for the expansion step.
 * 
 * @param env_var: replacement string
 * @param index: index where "$" is found
 * @param exp_input: pointer to final input string
 * 
 * @return: void function, no return value
 */
void	expansion_replace_string(char *env_var, int index, char **exp_input)
{
	if (env_var)
		*exp_input = ft_str_replace(*exp_input, index, env_var);
	else
		*exp_input = ft_str_replace(*exp_input, index, "");
}

/**
 * @function: ft_env_search
 * @brief: takes a string "$VAR" and returns 
 	the corresponding string from the env list
 * 
 * @param var: string that starts with '$' + word,
 	this is malloced from a previous funciton.
 * 
 * @return: a new string that is a copy of the
 	corresponding string from the env list if it exists.
	Else it returns a whitespace (' ')
 */
char	*ft_env_search(char *var)
{
	char	*env_var;

	env_var = getenv(++var);
	if (env_var != NULL)
	{
		ft_printf("env_var found: %s\n", env_var);
	}
	else
	{
		ft_printf("env_var not found: %s\n", env_var);
	}
	return (env_var);
}

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
		len++;
	while (input[len] && (ft_isalnum(input[len]) || input[len] == '_'))
		len++;
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
	a string with '$VAR' replaced with a whitespace(' ') 
 */

char	*ft_var_exp(char **input, int start_index)
{
	int		env_len;
	char	*var;
	char	*env_var;

	env_len = ft_env_len(*input + start_index);
	var = ft_substr(*input + start_index, 0, env_len);
	ft_printf("variable found: %s\n", var);
	env_var = ft_env_search(var);
	return (free(var), env_var);
}
/**
 * @function: expansion
 * @brief: takes input string from readline and 
 	does variable expansion and command substition.
 * 
 * @param input: output of readline(), note that this
 	is malloced and needs to be freed after use.
 * 
 * @return: returns expanded string or NULL if expansion fails.
 */

char	*expansion(char *input)
{
	char	*env_var;
	char	*exp_input;
	int		in_single_quote;
	int		i;

	exp_input = ft_strdup(input);
	in_single_quote = 0;
	i = 0;
	while (exp_input[i])
	{
		if (exp_input[i] == '\'')
		{
			in_single_quote = !in_single_quote;
			i++;
		}
		else if (exp_input[i] == '$' && !in_single_quote)
		{
			env_var = ft_var_exp(&exp_input, i);
			expansion_replace_string(env_var, i, &exp_input);
			i += ft_strlen(env_var);
		}
		else
			i++;
	}
	return (free(input), exp_input);
}
