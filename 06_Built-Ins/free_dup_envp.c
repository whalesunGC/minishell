/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dup_envp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:41:08 by apoh              #+#    #+#             */
/*   Updated: 2024/09/24 19:41:14 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: free_dup_envp
 * @brief: freeing duplicate env to prevent leaks
 * 
 * @param **env : this is the duplicated env
 * 
 * @return: void function
 */

void	free_dup_envp(char **env)

{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}
