/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_utils8.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:27:15 by apoh              #+#    #+#             */
/*   Updated: 2024/11/21 12:27:16 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_parent_for_handling_forking_process
 * @brief: handle parent process for the function handling forking process below
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
		*params->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		*params->exit_status = WTERMSIG(status) + 128;
		if (WTERMSIG(status) + 128 == 130)
			handle_readline_cleanup();
		else if (WTERMSIG(status) + 128 == 131)
		{
			handle_readline_cleanup();
			ft_printf("\n");
		}
	}
	ft_signal(NULL, NULL, NULL, PARENT);
}

/**
 * @function: handle_delimiter_input_single_commands
 * @brief: checking if expanstion is necessary if heredocs is met
 	and cleaning input after that
 	0 means not necessary. 1 means necessary
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: void function
 */

void	handle_delimiter_input_single_commands(
			t_redirect_single_command_params *params)
{
	params->ignore_quote = 0;
	if (ft_has_quote(params->result->delimiter[params->delimiter_counter]) == 1)
		params->ignore_quote = 0;
	else
		params->ignore_quote = 1;
	params->result->delimiter[params->delimiter_counter]
		= ft_remove_quote(params->result->delimiter[params->delimiter_counter]);
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
	if (*params->exit_status != 0)
		return (-1);
	handle_delimiter_input_single_commands(params);
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
	free(params->result->redirect[params->x]);
	params->result->redirect[params->x] = ft_strdup("a");
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
	free(params->result->redirect[params->x]);
	params->result->redirect[params->x] = ft_strdup("a");
	if (params->result->cmd[0] != NULL)
	{
		if (handle_child_execution(params, env) == -1)
			return (-1);
	}
	return (0);
}
