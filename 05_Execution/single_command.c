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

static int	handle_redirects(t_redirect_single_command_params *params,
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
 * @function: handle_no_redirects
 * @brief: handling commands with no redirects
 	handle_single_commands is in single_commands_utils2.c
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	char ***env : *** is needed to modify env variable if needed
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: -1 if forking fails 0 if all commands is executed
 */

static int	handle_no_redirects(t_redirect_single_command_params *params,
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

/**
 * @function: execution
 * @brief: execution of a single command where it will
 	handle redirectionss and no redirections
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
	t_redirect_single_command_params	params;

	if (checking_if_pipes_exist(node) == -1)
		return ;
	ft_memset(&params, 0, sizeof(t_redirect_single_command_params));
	ft_printf("Entering process of single command execution\n");
	params.traverse = node;
	while (params.traverse)
	{
		params.result = (t_exec_node *)params.traverse->content;
		if (params.result->type == AST_COMMAND)
		{
			if (params.result->redirect != NULL)
			{
				if (handle_redirects(&params, env, input) == -1)
					return ;
			}
			else if (handle_no_redirects(&params, env, input) == -1)
				return ;
		}
		params.traverse = params.traverse->next;
	}
}
