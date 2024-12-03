/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:51:58 by apoh              #+#    #+#             */
/*   Updated: 2024/11/12 18:51:59 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_exit_conditions_other_cases
 * @brief: handling conditions to exit child process, similarly redirections
 	will not be executed here as they are done in heredocs
 	or handle redirects functions
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handling_exit_conditions_other_cases(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->result->cmd[0] == NULL)
	{
		ft_dprintf(2, "No commands found, so we just exit\n");
		freeing_heredoc_pipes(params);
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
	params->loop_counter = 0;
	while (params->result->redirect[params->loop_counter] != NULL)
		params->loop_counter++;
	if ((ft_strcmp(params->result->redirect[params->loop_counter - 1],
				"a") == 0)
		|| (ft_strcmp(params->result->redirect[params->loop_counter - 1],
				"<") == 0)
		|| (ft_strcmp(params->result->redirect[params->loop_counter - 1],
				">") == 0)
		|| (ft_strcmp(params->result->redirect[params->loop_counter - 1],
				">>") == 0))
	{
		freeing_heredoc_pipes(params);
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @function: child_process_other_cases
 * @brief: after a fork is created, having checks for
 	heredocs and deciding what to execute
 * 
 * @param t_redirect_single_command_params : structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	child_process_other_cases(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->pipe_count == 0)
		handling_executing_execve_other_cases(params, env);
	else
		handling_exit_conditions_other_cases(params, env);
}

/**
 * @function: handle_fork_plus_executing_child
 * @brief: forks the process and creates a child process to handle it
 * 
 * @param t_redirect_single_commands_params *params : structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if forking fails. 0 if the whole execution is successful
 */

int	handle_fork_plus_executing_child(
			t_redirect_single_command_params *params, char ***env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("forking failed");
		return (-1);
	}
	if (params->pid == 0)
		child_process_other_cases(params, env);
	else
		handle_parent_for_handling_forking_process(params);
	return (0);
}

/**
 * @function: handle_built_in_closing_and_restore_original_fd
 * @brief: closing fds and restore original fd back to STDOUT
 * 
 * @param t_redirect_single_commands_params *params : structure for
 	single_command parameters
 * 
 * @return: -1 if dup2 of original fd fails. 0 
 */

int	handle_built_in_closing_and_restore_original_fd(
			t_redirect_single_command_params *params)
{
	if (params->input_fd > 0)
		close(params->input_fd);
	if (params->output_fd > 0)
	{
		if (dup2(params->original_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed");
			return (-1);
		}
		close(params->output_fd);
	}
	close(params->original_fd);
	return (0);
}

/**
 * @function: handle_single_commands_built_in
 * @brief: handles situations when there are redirections in built-ins
 * 
 * @param t_redirect_single_commands_params *params : structure for
 	single_command parameters
 * 
 * @return: -1 if dup2 of original fd fails. 0 
 */

int	handle_single_commands_built_in(
			t_redirect_single_command_params *params, char ***env)
{
	if ((ft_strcmp(params->av[0], "echo") == 0)
		|| (ft_strcmp(params->av[0], "cd") == 0)
		|| (ft_strcmp(params->av[0], "pwd") == 0)
		|| (ft_strcmp(params->av[0], "export") == 0)
		|| (ft_strcmp(params->av[0], "unset") == 0)
		|| (ft_strcmp(params->av[0], "env") == 0)
		|| (ft_strcmp(params->av[0], "exit") == 0))
	{
		if (handle_single_commands_built_in_with_redirects(params) == -1)
			return (-1);
		execute_bulit_in_commands_with_redirects(params, env);
		if (handle_built_in_closing_and_restore_original_fd(params) == -1)
			return (-1);
	}
	else if (handle_fork_plus_executing_child(params, env) == -1)
		return (-1);
	return (0);
}
