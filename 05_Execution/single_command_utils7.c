/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_utils7.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:27:11 by apoh              #+#    #+#             */
/*   Updated: 2024/11/21 12:27:12 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_parent_for_handling_forking_process
 * @brief: handle parent process for the function handling forking process
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: void function
 */

void	handle_parent_for_handling_forking_process(
			t_redirect_single_command_params *params)
{
	int	status;

	ignore_parent_signals();
	waitpid(params->pid, &status, 0);
	if (WIFEXITED(status))
	{
		ft_dprintf(1, "Child %d exited normally, with exit code %d\n", params->pid, WEXITSTATUS(status));
		*params->exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		ft_dprintf(1, "Child %d exited with signals, with exit code %d\n", params->pid, WTERMSIG(status));
		*params->exit_status = WTERMSIG(status) + 128;
	}
	ft_dprintf(1, "Current exit status %d\n", *params->exit_status);
	ft_signal(NULL, NULL, NULL, PARENT);
}

/**
 * @function: handling_forking_process
 * @brief: handles the heredoc process once "<<" is found in commands
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success
 */

int	handling_forking_process(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Welcome to heredocs <<\n");
	ft_dprintf(2, "delimiter for heredocs: %s\n",
		params->result->delimiter[params->delimiter_counter]);
	if (*params->exit_status != 0)
		return (-1);
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("fork failed");
		return (-1);
	}
	if (params->pid == 0)
	{
		ft_signal(params, NULL, *env, CHILD);
		handle_heredoc_child_process(params, env);
	}
	else
		handle_parent_for_handling_forking_process(params);
	params->delimiter_counter++;
	params->z++;
	closing_current_pipe_after_writing_data(params);
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
	ft_dprintf(2, "Entering here to change current redirect array %s\n",
		params->result->redirect[params->x]);
	free(params->result->redirect[params->x]);
	params->result->redirect[params->x] = ft_strdup("a");
	ft_dprintf(2, "After changing redirect array %s\n",
		params->result->redirect[params->x]);
	params->x++;
}

/**
 * @function: handling_last_redirect
 * @brief: handling the last_redirect and checking if there is a command
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

int	handling_last_redirect(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Entering here to change current redirect array %s\n",
		params->result->redirect[params->x]);
	free(params->result->redirect[params->x]);
	params->result->redirect[params->x] = ft_strdup("a");
	ft_dprintf(2, "After changing redirect array %s\n",
		params->result->redirect[params->x]);
	if (params->result->cmd[0] != NULL)
	{
		if (handle_child_execution(params, env) == -1)
			return (-1);
	}
	return (0);
}
