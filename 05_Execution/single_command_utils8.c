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
 * @function: closing_current_pipe_after_writing_data
 * @brief: closes the current heredocs pipe after writing data to it
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: void function
 */

void	closing_current_pipe_after_writing_data(
			t_redirect_single_command_params *params)
{
	if (params->y < params->pipe_count)
	{
		close(params->pipes[params->y][1]);
		params->y++;
	}
}

/**
 * @function: handle_null_heredocs_input
 * @brief: handling null input if ctrl + D is pressed in readline
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_null_heredocs_input(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "warning: here-document at delimited by end-of-file\n");
	freeing_heredoc_pipes(params);
	clean_up_function(params, env);
	exit(EXIT_SUCCESS);
}

/**
 * @function: handle_heredocs_delimiter
 * @brief: handling the instance where the input is the delimiter in readline
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_heredocs_delimiter(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Debugging Delimiter spotted\n");
	freeing_heredoc_pipes(params);
	clean_up_function(params, env);
	free(params->input1);
	exit(EXIT_SUCCESS);
}

/**
 * @function: handle_heredocs_input
 * @brief: handling the data by writing it to a pipe
 	if there is input in readline
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: void function
 */

void	handle_heredocs_input(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Debugging handling heredocs input\n");
	if (params->ignore_quote == 1)
		params->input1 = expansion_string(params->input1,
				params->ignore_quote, *env, params->exit_status);
	write(params->pipes[params->z][1], params->input1,
		ft_strlen(params->input1));
	write(params->pipes[params->z][1], "\n", 1);
	free(params->input1);
}

/**
 * @function: handle_heredoc_child_process
 * @brief: using the child process to perform readline for heredocs
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_heredoc_child_process(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Writing into pipe number [%d]\n", params->z);
	while (1)
	{
		ft_dprintf(2, "Debugging readline heredocs\n");
		params->input1 = readline("heredocs> ");
		if (params->input1 == NULL)
			handle_null_heredocs_input(params, env);
		else if (ft_strcmp(params->input1,
				params->result->delimiter[params->delimiter_counter]) == 0)
			handle_heredocs_delimiter(params, env);
		else if (params->input1 != NULL)
			handle_heredocs_input(params, env);
	}
}
