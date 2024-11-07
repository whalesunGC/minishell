/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:17:49 by apoh              #+#    #+#             */
/*   Updated: 2024/11/02 13:18:00 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: child_process
 * @brief: after a fork is created,
 	need to find the executable and
 	then use execve to execute the command
 * 
 * @param t_piping_single_command_params : structure for
 	single_command parameters
 	char ***env  : *** was declared in the calling function
 		needed only char ** in this function, hence needed de-referencing
 	char *input  : input from initial readline
 		used for freeing if execve fails
 * 
 * @return: void function
 */

static void	child_process(t_piping_single_command_params *params,
	char ***env, char *input)

{
	char		*command_path;

	if (access(params->result->cmd[0], F_OK) == 0)
		command_path = params->result->cmd[0];
	else
		command_path = find_command(&params->result->cmd[0], 0, *env);
	if (execve(command_path, params->result->cmd, *env) == -1)
	{
		perror("execve error");
		if (command_path != params->result->cmd[0])
			free(command_path);
		free(input);
		free_dup_envp(*env);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: checking_if_pipes_exist
 * @brief: checks through the nodes if pipes exist
 	return to calling function if pipes are found
 	as current function only handles single commands
 * 
 * @param t_list *node: structure of the linked list
 	where it points to void content
 * 
 * @return: -1 if pipes are found in the linked list structure
 	    0  if no pipes are found
 */

static int	checking_if_pipes_exist(t_list *node)

{
	t_list		*traverse;
	t_exec_node	*result;

	traverse = node;
	while (traverse)
	{
		result = (t_exec_node *)traverse->content;
		if (result->type == AST_PIPE)
		{
			ft_printf("Pipes detected. Proceeding to function with pipes\n");
			return (-1);
		}
		traverse = traverse->next;
	}
	return (0);
}

/**
 * @function: handle_fork_plus_executing_child
 * @brief: forks the process and executes single command
 * 
 * @param t_piping_single_commands_params *params : structure for
 	single_command parameters
 	char ***env : this parameter is needed in the child process
 * 
 * @return: -1 if forking fails. 0 if the whole execution is successful
 */

static int	handle_fork_plus_executing_child(t_piping_single_command_params
*params, char ***env, char *input)

{
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("forking failed");
		return (-1);
	}
	if (params->pid == 0)
		child_process(params, env, input);
	else
		wait(NULL);
	return (0);
}

/**
 * @function: handle_single_commands
 * @brief: handles single commands with built-in features
 	will perform execve if command is not a built-in feature
 * 
 * @param t_piping_single_command_params *params : structure for
 	single_command parameters
 	char ***env : needed *** to amend env
 	if cd and export command is called
 	char *input : input from original readline in main function
 		needed for freeing purposes
 * 
 * @return: -1 if forking process fails, 0 if all commands are successfully run
 */

static int	handle_single_commands(t_piping_single_command_params *params,
	char ***env, char *input)
{
	if (ft_strcmp(params->av[0], "echo") == 0)
		echo_command(params->ac, params->av);
	else if (ft_strcmp(params->av[0], "cd") == 0)
		cd_command(params->ac, params->av, env);
	else if (ft_strcmp(params->av[0], "pwd") == 0)
		pwd_command(params->ac, params->av);
	else if (ft_strcmp(params->av[0], "export") == 0)
		export_command(params->ac, params->av, env);
	else if (ft_strcmp(params->av[0], "unset") == 0)
		unset_command(params->ac, params->av, *env);
	else if (ft_strcmp(params->av[0], "env") == 0)
		env_command(params->ac, params->av, *env);
	else if (ft_strcmp(params->av[0], "exit") == 0)
		exit_command(params->ac, params->av, *env, input);
	else if (handle_fork_plus_executing_child(params, env, input) == -1)
		return (-1);
	return (0);
}

/**
 * @function: execution
 * @brief: execution of a single command
 * 
 * @param t_list *node : structure of linked list
 	where it points to void content
 	char ***env : *** is needed if env is needed to be updated
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: void function
 */

void	execution(t_list *node, char ***env, char *input)

{
	t_piping_single_command_params	params;

	if (checking_if_pipes_exist(node) == -1)
		return ;
	ft_memset(&params, 0, sizeof(t_piping_single_command_params));
	ft_printf("Entering process of single command execution\n");
	params.traverse = node;
	while (params.traverse)
	{
		params.result = (t_exec_node *)params.traverse->content;
		if (params.result->type == AST_COMMAND)
		{
			params.av = params.result->cmd;
			params.ac = 0;
			while (params.av[params.ac] != NULL)
				params.ac++;
			if (handle_single_commands(&params, env, input) == -1)
				return ;
		}
		params.traverse = params.traverse->next;
	}
}
