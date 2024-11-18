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
 * @function: checking_if_pipes_exist
 * @brief: checks through the nodes if pipe commands exist
 	return to calling function if pipe commands are found
 	as current function only handles single commands
	this function is created for single_command.c
 * 
 * @param t_list *node: structure of the linked list
 	where it points to void content
 * 
 * @return: -1 if pipes are found in the linked list structure
 	    0  if no pipes are found
 */

int	checking_if_pipes_exist(t_list *node)

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
 * @function: handle_redirects
 * @brief: handling redirections if command consists of redirects
 	execute_child_process is in single_command_utils1.c
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

int	handle_redirects(t_redirect_single_command_params *params,
	char ***env, char *input)

{
	while (params->result->redirect[params->i] != NULL)
		params->i++;
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("forking failed");
		return (-1);
	}
	if (params->pid == 0)
		execute_child_process_for_redirections(params, env, input);
	else
		wait(NULL);
	return (0);
}

/**
 * @function: execute_child_process_for_redirections
 * @brief: further summarising into a cleaner structure to read
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
	handle_redirections_file_opening(params, env, input);
	handle_dup_and_closing_fd(params, env, input);
	handle_execve_for_redirections(params, env, input);
}

/**
 * @function: handle_single_commands_no_heredocs
 * @brief: handling forking process if no heredocs is found
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	char ***env : *** is called in calling function
 		only needed ** for freeing in child process
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: -1 if failure, 0 if success
 */

int	handle_single_commands_no_heredocs(t_redirect_single_command_params *params,
	char ***env, char *input)
{	
	if (handle_fork_plus_executing_child(params, env, input) == -1)
		return (-1);
	return (0);
}

/**
 * @function: handle_other_cases
 * @brief: handling other test case scenarios
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	char ***env : *** is needed to modify env variable if needed
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: -1 if forking fails 0 if all commands is executed
 */

int	handle_other_cases(t_redirect_single_command_params *params,
	char ***env, char *input)

{
	params->av = params->result->cmd;
	params->ac = 0;
	while (params->av[params->ac] != NULL)
		params->ac++;
	if (handle_single_commands(params, env, input) == -1)
		return (-1);
	return (0);
}
