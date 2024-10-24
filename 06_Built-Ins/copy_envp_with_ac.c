/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp_with_ac.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:40:25 by apoh              #+#    #+#             */
/*   Updated: 2024/10/01 14:40:31 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: free_string_if_malloc_error_for_new_env
 * @brief: freeing strings if malloc fails during building
 		of each line while copying from env
 * 
 * @param **new_env: array of pointers belonging pertaining to each string.
 	      i: to loop through the string to free the correct string.
 * 
 * @return: void function
 */

static void	free_string_if_malloc_error_for_new_env(char **new_env, int i)

{
	if (i == 0)
	{
		free(new_env[i]);
	}
	while (i > 0)
	{
		free(new_env[i - 1]);
		i--;
	}
	free(new_env);
}

/**
 * @function: initialise_null
 * @brief: to set a null terminator on each
 	of the newly appended space after creation
 * 
 * @param **new_env: array of pointers belonging pertaining to each string.
 	      count: initial number of lines of old env
 	total count: total number of lines of newly created env
 * 
 * @return: void function
 */

static void	initialise_null(char **new_env, int count, int total_count)

{
	int	i;

	i = count;
	while (i < total_count)
	{
		new_env[i] = NULL;
		i++;
	}
}

/**
 * @function: copy_env_with_ac
 * @brief: get an updated new_env if i'm appending new data to the env
 * 
 * @param **env: an array of pointers pertaining
 		to each string inside env
 	valid_count: the extra space i need to malloc for each valid argument.
 * 
 * @return: new_env
 */

char	**copy_envp_with_ac(char **env, int valid_count)

{
	char	**new_env;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (env[count] != NULL)
		count++;
	new_env = (char **)malloc(sizeof(char *) * (count + valid_count + 1));
	if (new_env == NULL)
		return (NULL);
	while (i < count)
	{
		new_env[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (new_env[i] == NULL)
		{
			free_string_if_malloc_error_for_new_env(new_env, i);
			return (NULL);
		}
		ft_strlcpy(new_env[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	initialise_null(new_env, count, count + valid_count + 1);
	free_dup_envp(env);
	return (new_env);
}
