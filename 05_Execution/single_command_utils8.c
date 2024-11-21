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
 * @function: closing_current_pipes_heredocs_single_command
 * @brief: handle the closure of current pipe in parnet process
 	after heredocs has been performed
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: void function
 */

void	closing_current_pipes_heredocs_single_command(
			t_redirect_single_command_params *params)
{
	ft_dprintf(2, "Debugging closing current pipe\n");
	if (params->a < params->pipe_count)
	{
		close(params->pipes[params->a][0]);
		close(params->pipes[params->a][1]);
		params->a++;
	}
}

/**
 * @function: handle_null_heredocs
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
	ft_dprintf(2, "Debugging ERROR, please use delimiter\n");
	freeing_heredoc_pipes(params);
	clean_up_function(params, env);
	exit(EXIT_FAILURE);
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

void	handle_heredocs_input(t_redirect_single_command_params *params)
{
	ft_dprintf(2, "Debugging handling heredocs input\n");
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
			handle_heredocs_input(params);
	}
}