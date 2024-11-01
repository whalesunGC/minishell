/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:47:54 by apoh              #+#    #+#             */
/*   Updated: 2024/10/29 11:48:00 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_execve_failure
 * @brief: function to handle execve error gracefully
 * 
 * @param **av : string of arguments
         **env : env variable
         input : input from readline
 * 
 * @return: void function
 */

static void	handle_execve_failure(char **av, char **env, char *input)

{
	perror("execve failed");
	free_tokens(av);
	free(input);
	free_dup_envp(env);
	exit(EXIT_FAILURE);
}

/**
 * @function: first_child_process
 * @brief: function to handle first child process and
 	redirecting its output into the pipe
 * 
 * @param t_piping_params *params : structure to
 	handle piping commands
 	 **av : string of arguments
         **env : env variable
         input : input from readline
 * 
 * @return: void function
 */

static void	first_child_process(t_piping_params *params,
	char **av, char **env, char *input)

{
	params->pid1 = fork();
	if (params->pid1 < 0)
	{
		perror("creating child process failed\n");
		return ;
	}
	if (params->pid1 == 0)
	{
		close(params->fd[0]);
		if (dup2(params->fd[1], STDOUT_FILENO) == -1)
			ft_printf("ERROR for dup2 for child\n");
		close(params->fd[1]);
		if (access(av[0], F_OK) == 0)
			params->command_path = av[0];
		else
			params->command_path = find_command(av, 0, env);
		params->args[0] = params->command_path;
		params->args[1] = NULL;
		if (execve(params->command_path, params->args, env) == -1)
			handle_execve_failure(av, env, input);
	}
}

/**
 * @function: second_child_process
 * @brief: function to handle the 2nd child process
 	this includes reading data from the pipe and executing
 	the command based on the output in the pipe
 * 
 * @param t_piping_params *params : structure to
 	handle piping commands
 	  **av : string of arguments
         **env : env variable
         input : input from readline
 * 
 * @return: void function
 */

static void	second_child_process(t_piping_params *params,
	char **av, char **env, char *input)

{
	params->pid2 = fork();
	if (params->pid2 < 0)
	{
		perror("creating child process failed\n");
		return ;
	}
	if (params->pid2 == 0)
	{
		close(params->fd[1]);
		if (dup2(params->fd[0], STDIN_FILENO) == -1)
			ft_printf("ERROR for dup2 for parent\n");
		close(params->fd[0]);
		if (access(av[2], F_OK) == 0)
			params->command_path = av[2];
		else
			params->command_path = find_command(av, 2, env);
		params->args1[0] = params->command_path;
		params->args1[1] = av[3];
		params->args1[2] = NULL;
		if (execve(params->command_path, params->args1, env) == -1)
			handle_execve_failure(av, env, input);
	}
}

/**
 * @function: handle_no_pipe
 * @brief: function to handle no piping commands
 * 
 * @param t_piping_params *params : structure to
 	handle piping commands
 	  **av : string of arguments
         **env : env variable
         input : input from readline
 * 
 * @return: void function
 */

static void	handle_no_pipe(t_piping_params *params,
	char **av, char **env, char *input)

{
	params->pid1 = fork();
	if (params->pid1 < 0)
	{
		perror("creating child process failed\n");
		return ;
	}
	if (params->pid1 == 0)
	{
		if (access(av[0], F_OK) == 0)
			params->command_path = av[0];
		else
			params->command_path = find_command(av, 0, env);
		params->args[0] = params->command_path;
		params->args[1] = NULL;
		if (execve(params->command_path, params->args, env) == -1)
			handle_execve_failure(av, env, input);
	}
	wait(NULL);
}

/**
 * @function: piping_commands
 * @brief: function will handle non-pipe commands and pipe commands
 * 
 * @param **av : string of arguments
         **env : env variable
         input : input from readline
 * 
 * @return: void function
 */

void	piping_commands(char **av, char **env, char *input)

{
	t_piping_params	params;

	ft_memset(&params, 0, sizeof(t_piping_params));
	while (av[params.i] != NULL)
	{
		if (ft_strcmp(av[params.i], "|") == 0)
			params.command_count++;
		params.i++;
	}
	if (params.command_count > 0)
	{
		if (pipe(params.fd) == -1)
		{
			perror("pipe failed\n");
			return ;
		}
		first_child_process(&params, av, env, input);
		waitpid(params.pid1, NULL, 0);
		second_child_process(&params, av, env, input);
		close(params.fd[1]);
		waitpid(params.pid2, NULL, 0);
		close(params.fd[0]);
	}
	else
		handle_no_pipe(&params, av, env, input);
}
