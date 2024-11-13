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
 * @function: finding_heredocs
 * @brief: finding if there is any heredocs in the command.
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	t_list *node: node to travserse each node
 * 
 * @return: void function
 */

void	finding_heredocs(t_redirect_single_command_params *params, t_list *node)
{	
	params->traverse = node;
	while (params->traverse)
	{
		ft_printf("checking for heredocs\n");
		params->result = (t_exec_node *)params->traverse->content;
		if (params->result->type == AST_COMMAND)
		{
			if (params->result->redirect != NULL)
			{
				while (params->result->redirect[params->count] != NULL)
				{
					if (ft_strcmp(params->result
							->redirect[params->count], "<<") == 0)
						params->pipe_count++;
					params->count++;
				}
			}
		}
		params->traverse = params->traverse->next;
	}
}

/**
 * @function: handling_no_heredocs
 * @brief: here we handle the situation where no heredocs is found
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	char ***env: this is used to free env if child process fails
 	char *input: this is used to free readline data in main
 	t_list *node: node to travserse each node
 * 
 * @return: -1 if there is an error, 0 if success
 */
int	handling_no_heredocs(t_redirect_single_command_params
*params, char ***env, char *input, t_list *node)
{	
	ft_printf("handling no heredocs\n");
	params->traverse = node;
	while (params->traverse)
	{
		params->result = (t_exec_node *)params->traverse->content;
		if (params->result->type == AST_COMMAND)
		{
			if (params->result->redirect != NULL)
			{
				if (handle_redirects(params, env, input) == -1)
					return (-1);
				if (handle_other_cases(params, env, input) == -1)
					return (-1);
			}
			else if (handle_other_cases(params, env, input) == -1)
				return (-1);
		}
		params->traverse = params->traverse->next;
	}
	return (0);
}

/**
 * @function: creating_pipes
 * @brief: creating space for pipes and
 	initialising pipe using pipe function
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: -1 if there is an error, 0 if success
 */

int	creating_pipes(t_redirect_single_command_params *params)
{
	ft_printf("Total heredocs found: %d\n", params->pipe_count);
	params->pipes = creating_new_pipes(params->pipe_count);
	if (params->pipes == NULL)
	{
		perror("pipes failed");
		return (-1);
	}
	params->count = 0;
	while (params->count < params->pipe_count)
	{
		if (pipe(params->pipes[params->count]) == -1)
		{
			perror("pipe failed");
			return (-1);
		}
		params->count++;
	}
	return (0);
}

/**
 * @function: handling_heredocs
 * @brief: handling situations if heredocs are found
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	char ***env : *** is needed if env is needed to be updated
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 	t_list *node: node to travserse each node
 	
 * 
 * @return: -1 if there is an error, 0 if success
 */

int	handling_heredocs(t_redirect_single_command_params
*params, char ***env, char *input, t_list *node)
{	
	params->traverse = node;
	while (params->traverse)
	{
		ft_printf("Entering here for first loop\n");
		params->result = (t_exec_node *)params->traverse->content;
		if (params->result->type == AST_COMMAND)
		{
			if (params->result->redirect != NULL)
			{
				ft_printf("coming here\n");
				if (heredocs(params, env, input) == -1)
					return (-1);
				if (handle_redirects(params, env, input) == -1)
					return (-1);
				if (handle_single_commands_no_heredocs
					(params, env, input) == -1)
					return (-1);
			}
		}
		params->traverse = params->traverse->next;
	}
	return (0);
}

/**
 * @function: execution
 * @brief: execution of a single command where it will
 	handle redirections and no redirections
 * 
 * @param t_list *node : structure of linked list
 	where it points to void content
 	char ***env : *** is needed if env is needed to be updated
 	char *input : initial readline from main function
 		used for freeing purposes if program fails
 * 
 * @return: -1 if error, 0 if success
 */

void	execution(t_list *node, char ***env, char *input)
{
	t_redirect_single_command_params	params;

	if (checking_if_pipes_exist(node) == -1)
		return ;
	ft_memset(&params, 0, sizeof(t_redirect_single_command_params));
	ft_printf("Entering process of single command execution\n");
	finding_heredocs(&params, node);
	params.exec_data_head = node;
	if (params.pipe_count == 0)
		handling_no_heredocs(&params, env, input, node);
	else
	{
		if (creating_pipes(&params) == -1)
			return ;
		if (handling_heredocs(&params, env, input, node) == -1)
			return ;
		free_pipes(params.pipes, params.pipe_count);
	}
}
