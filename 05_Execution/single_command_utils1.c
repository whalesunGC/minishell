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
 * @function: checking_if_pipes_exist
 * @brief: checks through the nodes if pipe commands exist
 	return to calling function if pipe commands are found
 	as current function only handles single commands
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
 * @function: finding_heredocs
 * @brief: finding if there is any heredocs in the command.
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	t_list *node: structure of the linked list
 	where it points to void content
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
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 	t_list *node: structure of the linked list
 	where it points to void content
 * 
 * @return: -1 if there is an error, 0 if success
 */
int	handling_no_heredocs(t_redirect_single_command_params
*params, char ***env, t_list *node)
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
				write(2, "handling redirects first\n", 25);
				if (handle_redirects(params, env) == -1)
					return (-1);
				write(2, "handling other cases\n", 21);
				if (handle_other_cases(params, env) == -1)
					return (-1);
			}
			else if (handle_other_cases(params, env) == -1)
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
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 	t_list *node: structure of the linked list
 	where it points to void content
 * 
 * @return: -1 if there is an error, 0 if success
 */

int	handling_heredocs(t_redirect_single_command_params
*params, char ***env, t_list *node)
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
				if (heredocs(params, env) == -1)
					return (-1);
				if (handle_redirects(params, env) == -1)
					return (-1);
				if (handle_single_commands_no_heredocs
					(params, env) == -1)
					return (-1);
			}
		}
		params->traverse = params->traverse->next;
	}
	return (0);
}
