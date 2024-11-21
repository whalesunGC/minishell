/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:13:36 by apoh              #+#    #+#             */
/*   Updated: 2024/11/14 19:13:37 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: creating_heredocs_pipes
 * @brief: malloc space for heredocs for them to be stored in pipes
 	if there are heredocs. needed to differentiate this from
 	the normal piping commands
 	also mallocing space to store 2 integers for each pipe
 	so that your read end and write end can be represented easily
 * 
 * @param heredocs_count: the total count for the number of
 	heredocs in the command
 * 
 * @return: heredocs_pipes if allocation is successful, NULL if error
 */

int	**creating_heredocs_pipes(int heredocs_count)
{	
	int	**heredocs_pipes;
	int	i;

	i = 0;
	heredocs_pipes = malloc(sizeof(int *) * heredocs_count);
	if (heredocs_pipes == NULL)
	{
		perror("Failed to allocate memory for heredoc pipes");
		return (NULL);
	}
	while (i < heredocs_count)
	{
		heredocs_pipes[i] = malloc(sizeof(int) * 2);
		if (heredocs_pipes[i] == NULL)
		{
			perror("Failed to allocate memory for heredoc pipe descriptors");
			while (i > 0)
				free(heredocs_pipes[--i]);
			free(heredocs_pipes);
			return (NULL);
		}
		i++;
	}
	return (heredocs_pipes);
}

/**
 * @function: setting_up_heredocs_pipes
 * @brief: setting up heredocs_pipes using the pipe function call
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: 0 if successful, -1 if failure
 */

int	setting_up_heredocs_pipes(t_piping_multiple_command_params *params)
{
	params->heredocs_pipe_number = 0;
	while (params->heredocs_pipe_number < params->heredocs_count)
	{
		if (pipe(params->heredocs_pipes[params->heredocs_pipe_number]) == -1)
		{
			perror("pipe failed for multiple commands with pipes\n");
			return (-1);
		}
		params->heredocs_pipe_number++;
	}
	return (0);
}
