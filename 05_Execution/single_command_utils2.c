/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:26:26 by apoh              #+#    #+#             */
/*   Updated: 2024/11/07 20:26:32 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: clean_up_function
 * @brief: freeing up resources when child process exits
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	char ***env : *** is called in calling function
 		only needed ** for freeing in child process
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: void function
 */

void	clean_up_function(t_redirect_single_command_params *params,
			char ***env, char *input)

{
	free(input);
	free_pipes(params->pipes, params->pipe_count);
	free_dup_envp(*env);
	rl_clear_history();
}

/**
 * @function: exiting_conditions_nonzero_pipecount
 * @brief: handling conditions to exit the
 	child process if certain conditions are met
 	if there are no heredocs
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	char ***env : *** is called in calling function
 		only needed ** for freeing in child process
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: void function
 */

void	exiting_conditions_nonzero_pipecount(t_redirect_single_command_params
*params, char ***env, char *input)

{
	while (params->result->redirect[params->loop_counter] != NULL)
		params->loop_counter++;
	if ((ft_strcmp(params->result->cmd[0], "echo") == 0)
		|| (ft_strcmp(params->result->cmd[0], "cd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "pwd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "export") == 0)
		|| (ft_strcmp(params->result->cmd[0], "unset") == 0)
		|| (ft_strcmp(params->result->cmd[0], "env") == 0)
		|| (ft_strcmp(params->result->cmd[0], "exit") == 0)
		|| (ft_strcmp(params->result->redirect[params->loop_counter - 1],
				"a") == 0))
	{
		write(2, "exiting redirects\n", 18);
		clean_up_function(params, env, input);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @function: exiting_conditions_zero_pipecount
 * @brief: handling conditions to exit the
 	child process if certain conditions are met
 	if there are heredocs
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	char ***env : *** is called in calling function
 		only needed ** for freeing in child process
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: void function
 */

void	exiting_conditions_zero_pipecount(t_redirect_single_command_params
*params, char ***env, char *input)

{
	if ((ft_strcmp(params->result->cmd[0], "echo") == 0)
		|| (ft_strcmp(params->result->cmd[0], "cd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "pwd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "export") == 0)
		|| (ft_strcmp(params->result->cmd[0], "unset") == 0)
		|| (ft_strcmp(params->result->cmd[0], "env") == 0)
		|| (ft_strcmp(params->result->cmd[0], "exit") == 0)
		|| (ft_strcmp(params->result->redirect[params->loop_counter],
				"a") == 0))
	{
		write(2, "exiting redirects for no pipe\n", 30);
		clean_up_function(params, env, input);
		exit(EXIT_SUCCESS);
	}
}
