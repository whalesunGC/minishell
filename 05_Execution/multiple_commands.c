/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:29:42 by apoh              #+#    #+#             */
/*   Updated: 2024/11/06 22:07:37 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: initialise_params
 * @brief: sets up the initialising of parameters before we start the function
 	t_list *node : structure of linked list
 	where it points to void content
 	**exit_status : to update and initialise the value to 0;
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

static void	initialise_params(
			t_piping_multiple_command_params *params,
				t_list *node, int **exit_status)
{
	ft_memset(params, 0, sizeof(t_piping_multiple_command_params));
	params->exec_data_head = node;
	params->exit_status = *exit_status;
	*exit_status = 0;
}

/**
 * @function: handling_heredocs_total
 * @brief: performs error handling if heredocs exceeds the max
 	will perform heredocs if it is valid
 	t_list *node : structure of linked list
 	where it points to void content
 	***env: needed *** here in the event of
 	environment needing to be changed
 	** will be used for freeing purposes
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: -1 if failure, 0 if success
 */

static int	handling_heredocs_total(
			t_piping_multiple_command_params *params, t_list *node, char ***env)
{
	if (params->heredocs_count > 16)
	{
		ft_dprintf(2, "Maximum here-dcoument count exceeded\n");
		closing_main_pipes(params);
		free_pipes(params->pipes, params->total - 1);
		free(params->pid_array);
		return (-1);
	}
	if (params->heredocs_count > 0)
	{
		params->heredocs_pipes = creating_heredocs_pipes
			(params->heredocs_count);
		if (params->heredocs_pipes == NULL || setting_up_heredocs_pipes
			(params) == -1)
			return (-1);
		handle_heredocs_multiple_commands(params, node, env);
	}
	return (0);
}

/**
 * @function: clean_up_function_execution_with_pipes
 * @brief: perform clean up after functions are completed.
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

static void	clean_up_function_execution_with_pipes(
			t_piping_multiple_command_params *params)
{
	handle_pipe_and_waiting_for_child(params);
	free_pipes(params->pipes, params->total - 1);
	free_heredocs_pipes(params->heredocs_pipes, params->heredocs_count);
	free(params->pid_array);
}

/**
 * @function: execution_with_pipes
 * @brief: handling arguments with pipe commands
 * 
 * @param t_list *node : structure of linked list
 	where it points to void content
 	***env: needed *** here in the event of
 	environment needing to be changed
 	** will be used for freeing purposes
 * 
 * @return: void function
 */

void	execution_with_pipes(t_list *node, char ***env, int *exit_status)
{
	t_piping_multiple_command_params	params;

	if (check_for_pipes(node) == -1)
		return ;
	initialise_params(&params, node, &exit_status);
	params.total = check_total_commands(node);
	if (params.total > 43)
	{
		ft_dprintf(2, "Too many pipes created\n");
		return ;
	}
	params.pid_array = (pid_t *)malloc(sizeof(pid_t) * params.total);
	if (!params.pid_array)
		return ;
	ft_memset(params.pid_array, 0, sizeof(pid_t) * params.total);
	params.pipes = creating_new_pipes(params.total - 1);
	if (params.pipes == NULL || setting_up_pipes(&params) == -1)
		return ;
	searching_for_heredocs(&params, node);
	if (handling_heredocs_total(&params, node, env) == -1)
		return ;
	params.traverse = node;
	if (handle_arguments(&params, env) == -1)
		;
	clean_up_function_execution_with_pipes(&params);
}
