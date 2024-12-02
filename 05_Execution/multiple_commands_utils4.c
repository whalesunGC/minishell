/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:14:09 by apoh              #+#    #+#             */
/*   Updated: 2024/11/14 20:14:11 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_counters_and_redirects_array
 * @brief: handles the counters for the data structure and
 	also increment heredocs pipe number if there are further pipes
 	after the current node
 	amending the redirect array for heredocs to indicate this heredoc has been done
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

void	handle_counters_and_redirects_array(
			t_piping_multiple_command_params *params)
{
	ft_dprintf(2, "Debugging Changing current redirect array"
		"for multiple commands %s\n", params->result->redirect[params->x]);
	free(params->result->redirect[params->x]);
	params->result->redirect[params->x] = ft_strdup("a");
	ft_dprintf(2, "Debugging After changing current redirect"
		"array for multiple commands %s\n", params->result->redirect[params->x]);
	params->delimiter_counter++;
	params->heredocs_pipe_number++;
}

/**
 * @function: handle_delimiter_input_multiple_commands
 * @brief: checking if expanstion is necessary if heredocs is met
 	and cleaning input after that
 	0 means not necessary. 1 means necessary
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

void	handle_delimiter_input_multiple_commands(
			t_piping_multiple_command_params *params)
{
	params->ignore_quote = 0;
	if (ft_has_quote(params->result->delimiter[params->delimiter_counter]) == 1)
		params->ignore_quote = 0;
	else
		params->ignore_quote = 1;
	params->result->delimiter[params->delimiter_counter]
		= ft_remove_quote(params->result->delimiter[params->delimiter_counter]);
	ft_dprintf(2, "current delimiter now after clean up %s\n",
		params->result->delimiter[params->delimiter_counter]);
	ft_dprintf(2, "value of params ignore_quote [%d]\n", params->ignore_quote);
}

/**
 * @function: handle_redirect_array_for_heredocs
 * @brief: forking process is done here to handle heredocs one by one
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_redirect_array_for_heredocs(
			t_piping_multiple_command_params *params, char ***env)
{
	params->x = 0;
	params->delimiter_counter = 0;
	while (params->result->redirect[params->x] != NULL)
	{
		if (ft_strcmp(params->result->redirect[params->x], "<<") == 0)
		{
			ft_dprintf(2, "Debugging Delimiter for multiple pipes heredocs: %s\n",
				params->result->delimiter[params->delimiter_counter]);
			handle_delimiter_input_multiple_commands(params);
			if (*params->exit_status != 0)
				return (handle_counters_and_redirects_array(params));
			params->pid = fork();
			if (params->pid < 0)
			{
				perror("fork failed for multiple pipes heredocs");
				return ;
			}
			if (params->pid == 0)
			{
				ft_signal(NULL, params, *env, CHILD);
				handle_heredocs_readline_multiple_commands(params, env);
			}
			else
				handle_parent_for_handling_forking_process_multi(params);
			handle_counters_and_redirects_array(params);
		}
		params->x++;
	}
}

/**
 * @function: handle_heredocs_multiple_commands
 * @brief: traverses the node to the correct area to execute my commands
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	t_list *node : linked list structure where it points to void content
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_heredocs_multiple_commands(
			t_piping_multiple_command_params *params, t_list *node, char ***env)
{
	params->heredocs_pipe_number = 0;
	params->traverse = node;
	while (params->traverse)
	{
		params->result = (t_exec_node *)params->traverse->content;
		if (params->result->type == AST_PIPE)
		{
			params->traverse = params->traverse->next;
			continue ;
		}
		if (params->result->type == AST_COMMAND)
		{
			if (params->result->redirect != NULL)
			{
				ft_dprintf(2, "Debugging handle redirect array for heredocs\n");
				handle_redirect_array_for_heredocs(params, env);
			}
		}
		params->traverse = params->traverse->next;
	}
}
