/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:12:00 by apoh              #+#    #+#             */
/*   Updated: 2024/11/12 22:12:02 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	handle_null_heredocs_input(t_redirect_single_command_params
*params, char ***env)

{
	write(0, "ERROR, please use delimiter\n", 28);
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

void	handle_heredocs_delimiter(t_redirect_single_command_params
*params, char ***env)

{
	params->z = 0;
	write(0, "Delimiter spotted\n", 18);
	while (params->z < params->pipe_count)
	{
		close(params->pipes[params->z][0]);
		close(params->pipes[params->z][1]);
		params->z++;
	}
	free(params->input1);
	clean_up_function(params, env);
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

void	handle_heredoc_child_process(t_redirect_single_command_params
*params, char ***env)

{
	ft_printf("Writing into pipe number [%d]\n", params->z);
	while (1)
	{
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
