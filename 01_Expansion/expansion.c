/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:01:41 by wichee            #+#    #+#             */
/*   Updated: 2024/10/07 12:03:19 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_env_replace
 * @brief: takes a string "$VAR" and returns the corresponding string from the env list
 * 
 * @param var: string that starts with '$' + word
 * 
 * @return: a new string that is a copy of the corresponding string from the env list if it exists. Else it returns a whitespace (' ')
 */
char	*ft_env_replace(char *var)
{
	char	*env_var;
	char	*env_var;

	env_var = getenv(++var);
	if (env_var != NULL)
	{
		ft_printf("env_var found: %s\n",env_var);
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
 * @brief: takes an input that starts with a '$', finds the env variable and replaces inplace.
 * 
 * @param input: the address to the pointer of the input string.
 * 
 * @return: returns a string with the '$VAR' replaced with its corresponding env variable if found, else it returns a string with '$VAR' replaced with a whitespace(' ') 
 */
char	*ft_var_exp(char **input)
{
	int		env_len;
	char	*var;
	char	*env_var;

	env_len = ft_strchr(*input, ' ') - *input;
	var = ft_substr(*input, 0, env_len);
	ft_printf("variable found: %s\n",var);
	env_var = ft_env_replace(var);
	return (env_var);
}
/**
 * @function: expansion
 * @brief: takes input string from readline and does variable expansion and command substition.
 * 
 * @param input: output of readline(), note that this is malloced and needs to be freed after use.
 * 
 * @return: returns expanded string or NULL if expansion fails.
 */
char	*expansion(char *input)
{
	char	*exp_input;

	ft_printf("%s\n",input);
	exp_input = input;
	while (*input)
	{
		if (*input == '$')
		{	
			exp_input = ft_var_exp(&input);
		}
		input++;
	}
	return (exp_input);
}
