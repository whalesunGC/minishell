/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils8.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:46:41 by apoh              #+#    #+#             */
/*   Updated: 2024/11/27 15:46:42 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: initialise_counters_in_handle_arguments
 * @brief: initialise counters before start of loop
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	initialise_counters_in_handle_arguments(
			t_piping_multiple_command_params *params)
{
	params->i = 0;
	params->heredocs_pipe_number = 0;
}

/**
 * @function: setting_up_counters_and_initialise_node
 * @brief: initialise variables
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	setting_up_counters_and_initialise_node(
			t_piping_multiple_command_params *params)
{
	params->count = 0;
	params->flag = 0;
	params->result = (t_exec_node *)params->traverse->content;
}

/**
 * @function: increment_counters_and_traverse_next_node
 * @brief: handle closing fd if needed and increase counter
 	and move to next node
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	increment_counters_and_traverse_next_node(
			t_piping_multiple_command_params *params)
{
	if (params->input_fd > 0)
		close(params->input_fd);
	if (params->output_fd > 0)
		close(params->output_fd);
	params->i++;
	params->traverse = params->traverse->next;
}

/**
 * @function: handle_arguments
 * @brief: handling the commands after input
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if fork fails. 0 if everything is successful.
 */

int	handle_forking_process_and_executing_child(
			t_piping_multiple_command_params *params, char ***env, int i)
{
	if (*params->exit_status != 0 && *params->exit_status != 1)
		return (-1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	params->pid_array[i] = fork();
	if (params->pid_array[i] < 0)
	{
		perror("fork failed");
		return (-1);
	}
	if (params->pid_array[i] == 0)
		handle_child_process(params, env);
	return (0);
}

/**
 * @function: handle_arguments
 * @brief: handling the commands after input
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if fork fails. 0 if everything is successful.
 */

int	handle_arguments(
			t_piping_multiple_command_params *params, char ***env)
{
	initialise_counters_in_handle_arguments(params);
	while (params->traverse)
	{
		setting_up_counters_and_initialise_node(params);
		if (params->result->type == AST_PIPE)
		{
			params->traverse = params->traverse->next;
			continue ;
		}
		if (params->result->type == AST_COMMAND)
		{
			if (params->result->redirect != NULL)
				handle_heredocs_pipe_number_multiple_commands(params);
			if (params->flag == 1)
			{
				handle_flag_equals_one(params);
				continue ;
			}
		}
		if (handle_forking_process_and_executing_child
			(params, env, params->i) == -1)
			return (-1);
		increment_counters_and_traverse_next_node(params);
	}
	return (0);
}
