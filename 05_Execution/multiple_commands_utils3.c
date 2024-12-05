/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:00:53 by apoh              #+#    #+#             */
/*   Updated: 2024/11/14 20:00:55 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: clean_up_function_multiple_commands
 * @brief: freeing up memory allocated in case of error in child process
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	clean_up_function_multiple_commands(
			t_piping_multiple_command_params *params, char ***env)
{
	(void)env;
	free_pipes(params->pipes, params->total - 1);
	free_heredocs_pipes(params->heredocs_pipes, params->heredocs_count);
	if (params->signal_data)
		free(params->signal_data);
	if (params->pid_array)
		free(params->pid_array);
	ft_free(&params->msd);
	rl_clear_history();
}

/**
 * @function: handling_multiple_commands_null_heredocs_input
 * @brief: handles null input of heredocs when ctrl + d is pressed
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_multiple_commands_null_heredocs_input(
		t_piping_multiple_command_params *params, char ***env)
{
	ft_dprintf(2, "warning: here-document at delimited by end-of-file\n");
	params->heredocs_pipe_number = 0;
	while (params->heredocs_pipe_number < params->heredocs_count)
	{
		close(params->heredocs_pipes[params->heredocs_pipe_number][0]);
		close(params->heredocs_pipes[params->heredocs_pipe_number][1]);
		params->heredocs_pipe_number++;
	}
	params->z = 0;
	while (params->z < params->total - 1)
	{
		close(params->pipes[params->z][0]);
		close(params->pipes[params->z][1]);
		params->z++;
	}
	clean_up_function_multiple_commands(params, env);
	exit(EXIT_SUCCESS);
}

/**
 * @function: handle_multiple_commands_heredocs_delimiter
 * @brief: handles input when it is equal to the delimiter inside heredocs
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_multiple_commands_heredocs_delimiter(
		t_piping_multiple_command_params *params, char ***env)
{
	params->heredocs_pipe_number = 0;
	while (params->heredocs_pipe_number < params->heredocs_count)
	{
		close(params->heredocs_pipes[params->heredocs_pipe_number][0]);
		close(params->heredocs_pipes[params->heredocs_pipe_number][1]);
		params->heredocs_pipe_number++;
	}
	params->z = 0;
	while (params->z < params->total - 1)
	{
		close(params->pipes[params->z][0]);
		close(params->pipes[params->z][1]);
		params->z++;
	}
	free(params->input1);
	clean_up_function_multiple_commands(params, env);
	exit(EXIT_SUCCESS);
}

/**
 * @function: handle_multiple_commands_heredocs_input
 * @brief: writing data to the correct heredocs_pipe when there is input
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

void	handle_multiple_commands_heredocs_input(
			t_piping_multiple_command_params *params, char ***env)
{
	if (params->ignore_quote == 1)
		params->input1 = expansion_string(params->input1,
				params->ignore_quote, *env, params->exit_status);
	write(params->heredocs_pipes[params->heredocs_pipe_number][1],
		params->input1, ft_strlen(params->input1));
	write(params->heredocs_pipes[params->heredocs_pipe_number][1], "\n", 1);
	free(params->input1);
}

/**
 * @function: handle_heredocs_readline_multiple_commands
 * @brief: handles heredocs using readline
 	helper functions are all on top
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_heredocs_readline_multiple_commands(
		t_piping_multiple_command_params *params, char ***env)
{
	while (1)
	{
		params->input1 = readline("heredocs> ");
		if (params->input1 == NULL)
			handle_multiple_commands_null_heredocs_input(params, env);
		else if (ft_strcmp(params->input1, params->result->delimiter
				[params->delimiter_counter]) == 0)
			handle_multiple_commands_heredocs_delimiter(params, env);
		else if (params->input1 != NULL)
			handle_multiple_commands_heredocs_input(params, env);
	}
}
