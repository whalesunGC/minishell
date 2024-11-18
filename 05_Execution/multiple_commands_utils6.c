/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils6.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:18:28 by apoh              #+#    #+#             */
/*   Updated: 2024/11/18 18:18:30 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_input_output_heredocs_multiple_commands
 * @brief: to dup2 input, output, heredoc redirections appropriately
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env : *** used in calling function needed to use ** to free data
	*input : this is readline input from main function
 * 
 * @return: void function
 */

void	handle_input_output_heredocs_multiple_commands(
		t_piping_multiple_command_params *params, char ***env, char *input)

{
	write(2, "entering this loop\n", 19);
	params->b = 0;
	while (params->result->redirect[params->b] != NULL)
		params->b++;
	setting_up_input_redirections_multiple_commands(params, env, input);
	setting_up_output_redirections_multiple_commands(params, env, input);
	setting_up_heredocs_multiple_commands(params, env, input);
}

/**
 * @function: setup_pipe_redirection_and_closing
 * @brief: to handle the main general logic for the whole piping process
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env : *** used in calling function needed to use ** to free data
	*input : this is readline input from main function
 * 
 * @return: void function
 */

void	setup_pipe_redirection_and_closing(t_piping_multiple_command_params
*params, char ***env, char *input)

{
	if (params->i < params->total - 1)
	{
		write(2, "entering 1st command onwards\n", 29);
		if (params->result->redirect != NULL)
		{
			handle_input_output_heredocs_multiple_commands(params, env, input);
			setting_up_pipes_to_redirect_output(params, env, input);
		}
		else
			setting_up_pipes_to_redirect_output(params, env, input);
	}
	if (params->i > 0)
	{	
		write(2, "entering 2nd command onwards\n", 29);
		if (params->result->redirect != NULL)
			handle_input_output_heredocs_multiple_commands(params, env, input);
		else
			read_from_pipe_without_redirections(params, env, input);
	}
	params->j = 0;
	while (params->j < params->total - 1)
	{
		close(params->pipes[params->j][0]);
		close(params->pipes[params->j][1]);
		params->j++;
	}
}

/**
 * @function: handle_child_process
 * @brief: handling the process a child process does after forking
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 	char **env : env which was copied from env
 	this is required for execve to be executed
 * 
 * @return: void function
 */

void	handle_child_process(t_piping_multiple_command_params
*params, char ***env, char *input)

{
	setup_pipe_redirection_and_closing(params, env, input);
	if (params->input_fd < 0)
	{
		clean_up_function_multiple_commands(params, env, input);
		exit(EXIT_FAILURE);
	}
	if (access(params->result->cmd[0], F_OK) == 0)
		params->command_path = params->result->cmd[0];
	else
		params->command_path = find_command(&params->result->cmd[0], 0, *env);
	if (execve(params->command_path, params->result->cmd, *env) == -1)
	{
		perror("execve process failed");
		clean_up_function_multiple_commands(params, env, input);
		exit(EXIT_FAILURE);
	}
}
