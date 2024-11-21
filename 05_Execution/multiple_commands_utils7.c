/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils7.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:34 by apoh              #+#    #+#             */
/*   Updated: 2024/11/18 18:51:36 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_file_opening_errors
 * @brief: print error message if file opening fails
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

void	handle_file_opening_errors(t_piping_multiple_command_params *params)
{
	ft_dprintf(2, "Debugging file opening failure\n");
	if (params->input_fd < 0 || params->output_fd < 0)
	{
		ft_dprintf(2, "debugging if file opening failure\n");
		ft_printf("%s: ", params->result->rd_arg[params->rd_arg_counter]);
		perror("Error opening file");
	}
	if (params->input_fd < 0 && params->traverse->next == NULL)
	{
		ft_dprintf(2, "setting flag to 1 to indicate failure for last command");
		params->flag = 1;
	}
}

/**
 * @function: handle_file_opening_multiple_commands
 * @brief: to handle file opening for input redirections
 	to handle creation and appending for output redirections
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_file_opening_multiple_commands(
			t_piping_multiple_command_params *params)
{
	ft_dprintf(2, "Debugging file opening\n");
	params->b = 0;
	while (params->result->redirect[params->b] != NULL)
		params->b++;
	params->a = 0;
	params->rd_arg_counter = 0;
	while (params->a < params->b)
	{
		ft_dprintf(2, "Looping through each redirection commands\n");
		if (ft_strcmp(params->result->redirect[params->a], "a") == 0)
		{
			params->a++;
			continue ;
		}
		else if (ft_strcmp(params->result->redirect[params->a], "<") == 0)
			params->input_fd = open(params->result->rd_arg
				[params->rd_arg_counter], O_RDONLY);
		else if (ft_strcmp(params->result->redirect[params->a], ">") == 0)
			params->output_fd = open(params->result->rd_arg
				[params->rd_arg_counter], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(params->result->redirect[params->a], ">>") == 0)
			params->output_fd = open(params->result->rd_arg
				[params->rd_arg_counter], O_WRONLY | O_CREAT | O_APPEND, 0644);
		handle_file_opening_errors(params);
		params->rd_arg_counter++;
		params->a++;
	}
}

/**
 * @function: handle_heredocs_pipe_number_multiple_commands
 * @brief: to check which pipe number should i be using
 	to extract my data when running the command
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_heredocs_pipe_number_multiple_commands(
		t_piping_multiple_command_params *params)
{
	if (params->result->redirect != NULL)
	{
		ft_dprintf(2, "Debugging heredocs\n");
		handle_file_opening_multiple_commands(params);
		params->b = 0;
		while (params->result->redirect[params->b] != NULL)
		{
			ft_dprintf(2, "Debugging counting heredocs count total\n");
			if (ft_strcmp(params->result->redirect[params->b], "a") == 0)
				params->heredocs_pipe_number++;
			params->b++;
		}
		if (params->heredocs_pipe_number > 0)
		{
			params->heredocs_pipe_index = params->heredocs_pipe_number - 1;
			ft_dprintf(2, "reading pipe number [%d]\n",
				params->heredocs_pipe_index);
		}
	}
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
	params->i = 0;
	params->heredocs_pipe_number = 0;
	while (params->traverse)
	{
		ft_dprintf(2, "Debugging traversing through the node handle_arguments\n");
		params->result = (t_exec_node *)params->traverse->content;
		if (params->result->type == AST_PIPE)
		{
			params->traverse = params->traverse->next;
			continue ;
		}
		if (params->result->type == AST_COMMAND)
			handle_heredocs_pipe_number_multiple_commands(params);
		params->pid = fork();
		if (params->pid < 0)
		{
			perror("fork failed");
			return (-1);
		}
		if (params->pid == 0)
		{
			ft_dprintf(2, "Debugging child process\n");
			handle_child_process(params, env);
		}
		params->traverse = params->traverse->next;
		params->i++;
	}
	return (0);
}

/**
 * @function: handle_pipe_and_waiting_for_child
 * @brief: cleanup after all processes are forked already
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_pipe_and_waiting_for_child(
			t_piping_multiple_command_params *params)
{
	ft_dprintf(2, "Debugging closing pipes and waiting for child process to finish\n");
	params->j = 0;
	while (params->j < params->total - 1)
	{
		close(params->pipes[params->j][0]);
		close(params->pipes[params->j][1]);
		params->j++;
	}
	params->j = 0;
	while (params->j < params->total)
	{
		wait(NULL);
		params->j++;
	}
}
