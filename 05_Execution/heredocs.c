/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:53:48 by apoh              #+#    #+#             */
/*   Updated: 2024/11/08 22:53:50 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handling_forking_process
 * @brief: handles the heredoc process once "<<" is found in commands
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	char ***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 	char *input: readline from main function
 	to free if child process exits
 * 
 * @return: -1 if failure, 0 if success
 */

int	handling_forking_process(t_redirect_single_command_params *params,
		char ***env, char *input)

{
	ft_printf("Welcome to heredocs <<\n");
	ft_printf("delimiter for heredocs: %s\n",
		params->result->delimiter[params->delimiter_counter]);
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("fork failed");
		return (-1);
	}
	if (params->pid == 0)
	{
		ft_signal(params, *env, input, CHILD);
		handle_heredoc_child_process(params, env, input);
	}
	else
	{	
		ignore_parent_signals();
		wait(NULL);
	}
	params->delimiter_counter++;
	params->z++;
	if (params->y < params->pipe_count)
	{
		close(params->pipes[params->y][1]);
		params->y++;
	}
	return (0);
}

/**
 * @function: handling_next_redirect
 * @brief: looping through the redirect array to find the next redirect
 	changing the redirect array if "<<" is found to another char
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: void function
 */

void	handling_next_redirect(t_redirect_single_command_params *params)

{	
	ft_printf("Entering here to change current redirect array %s\n",
		params->result->redirect[params->x]);
	free(params->result->redirect[params->x]);
	params->result->redirect[params->x] = ft_strdup("a");
	ft_printf("After changing redirect array %s\n",
		params->result->redirect[params->x]);
	params->x++;
}

/**
 * @function: handling_last_redirect
 * @brief: handling the last_redirect and checking if there is a command
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	char ***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 	char *input: readline from main function
 	to free if child process exits
	
 * 
 * @return: void function
 */

int	handling_last_redirect(t_redirect_single_command_params *params,
		char ***env, char *input)

{
	ft_printf("Entering here to change current redirect array %s\n",
		params->result->redirect[params->x]);
	free(params->result->redirect[params->x]);
	params->result->redirect[params->x] = ft_strdup("a");
	ft_printf("After changing redirect array %s\n",
		params->result->redirect[params->x]);
	if (params->result->cmd[0] != NULL)
	{
		if (handle_child_execution(params, env, input) == -1)
			return (-1);
	}
	return (0);
}

/**
 * @function: waiting_for_child_to_execute
 * @brief: to wait for all child processes to finish
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
  * 
 * @return: void function
 */

void	waiting_for_child_to_execute(t_redirect_single_command_params *params)

{
	params->y = 0;
	while (params->y < params->pipe_count)
	{
		wait(NULL);
		params->y++;
	}
}

/**
 * @function: heredocs
 * @brief: handling the presence of heredocs
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	char ***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 	char *input: readline from main function
 	to free if child process exits
 * 
 * @return: -1 if failure, 0 if success
 */

int	heredocs(t_redirect_single_command_params *params, char ***env, char *input)

{
	while (params->result->redirect[params->x] != NULL)
	{
		if ((ft_strcmp(params->result->redirect[params->x], "<<") == 0))
		{
			if (handling_forking_process(params, env, input) == -1)
				return (-1);
			if (params->result->redirect[params->x + 1] != NULL)
			{
				handling_next_redirect(params);
				continue ;
			}
			else if (params->result->redirect[params->x + 1] == NULL)
			{
				if (handling_last_redirect(params, env, input) == -1)
					return (-1);
			}
			waiting_for_child_to_execute(params);
		}
		params->x++;
	}
	return (0);
}
