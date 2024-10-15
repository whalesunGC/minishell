/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:37:37 by apoh              #+#    #+#             */
/*   Updated: 2024/09/24 19:37:42 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: free_string_if_malloc_error_for_env
 * @brief: freeing strings if malloc fails during building
 		of each line while copying from envp
 * 
 * @param **env: array of pointers belonging pertaining to each string.
 	      i: to loop through the string to free the correct string.
 * 
 * @return: void function
 */

static void	free_string_if_malloc_error_for_env(char **env, int i)

{
	if (i == 0)
	{
		free(env[i]);
	}
	while (i > 0)
	{
		free(env[i - 1]);
		i--;
	}
	free(env);
}

/**
 * @function: copy_envp
 * @brief: get a copy of envp since envp cannot be manipulated. (READ ONLY) 
 		i need a copy to manipulate the variables inside envp. 
 * 
 * @param **envp: an array of pointers pertaining to each string
 		inside the enviornment variable.
 * 
 * @return: env
 */

char	**copy_envp(char **envp)

{
	char	**env;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (envp[count] != NULL)
		count++;
	env = (char **)malloc(sizeof(char *) * (count + 1));
	if (env == NULL)
		return (NULL);
	while (i < count)
	{
		env[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		if (env[i] == NULL)
		{
			free_string_if_malloc_error_for_env(env, i);
			return (NULL);
		}
		ft_strlcpy(env[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	env[count] = NULL;
	return (env);
}
