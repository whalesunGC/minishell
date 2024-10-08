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
 * @function: ft_env_replace
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
char	*ft_env_replace(char *var)
{
	char	*env_var;

	env_var = getenv(++var);
	if (env_var != NULL)
	{
		ft_printf("env_var found: %s\n", env_var);
		env_var = ft_strdup(env_var);
	}
	else
	{
		ft_printf("env_var not found: %s\n", env_var);
	}
	return (env_var);
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

	env_len = ft_strchr(*input + start_index, ' ') - *input;
	var = ft_substr(*input + start_index, 0, env_len);
	ft_printf("variable found: %s\n", var);
	env_var = ft_env_replace(var);
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
	int		i;

	ft_printf("input from readline: %s\n", input);
	exp_input = ft_strdup(input);
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			env_var = ft_var_exp(&input, i);
			if (env_var)
				exp_input = ft_str_replace(exp_input, i, env_var);
			else
				exp_input = ft_str_replace(exp_input, i, "$");
		}
		i++;
	}
	return (exp_input);
}
