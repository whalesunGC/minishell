/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:38:34 by apoh              #+#    #+#             */
/*   Updated: 2024/11/07 19:38:36 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_redirections_file_opening
 * @brief: handling opening of files when redirections are called
 	and handling errors if files are not valid
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 * 
 * @return: void function
 */

void	handle_redirections_file_opening(
			t_redirect_single_command_params *params)

{
	while (params->k < params->i)
	{
		if (ft_strcmp(params->result->redirect[params->k], "<") == 0)
			params->input_fd = open(params->result->rd_arg[params->k],
					O_RDONLY);
		else if (ft_strcmp(params->result->redirect[params->k], ">") == 0)
			params->output_fd = open(params->result->rd_arg[params->k],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(params->result->redirect[params->k], ">>") == 0)
			params->output_fd = open(params->result->rd_arg[params->k],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (params->input_fd < 0 || params->output_fd < 0)
		{
			ft_printf("%s: ", params->result->rd_arg[params->k]);
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		params->k++;
	}
}

/**
 * @function: handle_dup_and_closing_fd
 * @brief: handling dup function calls for both input and output
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 * 
 * @return: void function
 */

void	handle_dup_and_closing_fd(t_redirect_single_command_params *params)

{
	if (params->input_fd > 0)
	{
		if (dup2(params->input_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 failed for child for input_fd");
			exit(EXIT_FAILURE);
		}
		close(params->input_fd);
	}
	if (params->output_fd > 0)
	{
		if (dup2(params->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Dup2 failed for child for input_fd");
			exit(EXIT_FAILURE);
		}
		close(params->output_fd);
	}
}

/**
 * @function: handle_execve_for_redirections
 * @brief: handling execve when there is redirections
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	char ***env : *** is called in calling function
 		only needed ** for freeing in child process
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: -1 if forking fails, 0 if all commands is executed
 */

void	handle_execve_for_redirections(t_redirect_single_command_params *params,
	char ***env, char *input)

{
	if (params->result->cmd[0] == NULL)
	{
		ft_printf("No commands found, so we just exit\n");
		free(input);
		free_dup_envp(*env);
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (access(params->result->cmd[0], F_OK) == 0)
			params->command_path = params->result->cmd[0];
		else
			params->command_path = find_command
				(&params->result->cmd[0], 0, *env);
		if (execve(params->command_path, params->result->cmd, *env) == -1)
		{
			if (params->command_path != params->result->cmd[0])
				free(params->command_path);
			free(input);
			free_dup_envp(*env);
			rl_clear_history();
			exit(EXIT_FAILURE);
		}
	}					
}

/**
 * @function: execute_child_process_for_redirections
 * @brief: further summarising the above processes
 	into a cleaner structure to read
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

void	execute_child_process_for_redirections(t_redirect_single_command_params
*params, char ***env, char *input)

{
	handle_redirections_file_opening(params);
	handle_dup_and_closing_fd(params);
	handle_execve_for_redirections(params, env, input);
}
