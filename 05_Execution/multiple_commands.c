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
 * @function: setup_pipe_redirection_and_closing
 * @brief: setting up of redirections depending
 	on which command you are in the pipe process
	1st command - redirect stdout to write to pipe
 	middle commands- redirect stdin to read from pipe
 	middle commands - redirect stdout to write to next pipe
 	last command - redirect stdin to read from pipe
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

static void	setup_pipe_redirection_and_closing(t_piping_multiple_command_params
*params)

{
	if (params->i > 0)
	{	
		if (dup2(params->pipes[params->i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 to stdin failed");
			exit(EXIT_FAILURE);
		}
	}
	if (params->i < params->total - 1)
	{
		if (dup2(params->pipes[params->i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2 to stdout failed");
			exit(EXIT_FAILURE);
		}
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

static void	handle_child_process(t_piping_multiple_command_params
*params, char **env)

{
	setup_pipe_redirection_and_closing(params);
	if (access(params->result->cmd[0], F_OK) == 0)
		params->command_path = params->result->cmd[0];
	else
		params->command_path = find_command(&params->result->cmd[0], 0, env);
	if (execve(params->command_path, params->result->cmd, env) == -1)
	{
		perror("execve process failed");
		exit(EXIT_FAILURE);
	}
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

static void	handle_pipe_and_waiting_for_child(t_piping_multiple_command_params
*params)

{
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

/**
 * @function: handle_arguments
 * @brief: handling the commands after input
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: -1 if fork fails. 0 if everything is successful.
 */

static int	handle_arguments(t_piping_multiple_command_params *params,
	char **env)

{
	while (params->traverse)
	{
		params->result = (t_exec_node *)params->traverse->content;
		if (params->result->type == AST_PIPE)
		{
			params->traverse = params->traverse->next;
			continue ;
		}
		params->pid = fork();
		if (params->pid < 0)
		{
			perror("fork failed");
			return (-1);
		}
		if (params->pid == 0)
		{
			if (params->result->type == AST_COMMAND)
				handle_child_process(params, env);
		}
		params->traverse = params->traverse->next;
		params->i++;
	}
	return (0);
}

/**
 * @function: execution_with_pipes
 * @brief: handling arguments with pipe commands
 * 
 * @param t_list *node : structure of linked list
 	where it points to void content
 	char **env : duplicated env from envp in the main function
 * 
 * @return: void function
 */

void	execution_with_pipes(t_list *node, char **env)

{
	t_piping_multiple_command_params	params;

	if (check_for_pipes(node) == -1)
		return ;
	ft_memset(&params, 0, sizeof(t_piping_multiple_command_params));
	params.total = check_total_commands(node);
	params.pipes = creating_new_pipes(params.total - 1);
	if (params.pipes == NULL)
		return ;
	if (setting_up_pipes(&params) == -1)
		return ;
	params.i = 0;
	params.traverse = node;
	if (handle_arguments(&params, env) == -1)
		return ;
	handle_pipe_and_waiting_for_child(&params);
}
