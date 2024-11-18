/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:13:31 by apoh              #+#    #+#             */
/*   Updated: 2024/11/11 19:13:33 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: free_pipes
 * @brief: freeing pipes after the usage of the functions
 * 
 * @param **pipes: 2d array of pipes to keep track of
 	which pipe you are working with
 	num_pipes: number of pipes in total
 * 
 * @return: void function
 */

void	free_pipes(int **pipes, int num_pipes)

{
	int	i;

	i = 0;
	if (pipes == NULL)
		return ;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	free_heredocs_pipes(int **heredocs_pipes, int heredocs_count)

{
	int	i;

	i = 0;
	if (heredocs_pipes == NULL)
		return ;
	while (i < heredocs_count)
	{
		free(heredocs_pipes[i]);
		i++;
	}
	free(heredocs_pipes);
}
