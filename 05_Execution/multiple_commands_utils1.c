/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:29:31 by apoh              #+#    #+#             */
/*   Updated: 2024/11/06 20:29:34 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: check_total_commands
 * @brief: check for total commands so that
 	we can know how many pipes is required
 * 
 * @param t_list *node : structure of linked list
 	 where it points to void content
 * 
 * @return: command_count to calling function
 */

int	check_total_commands(t_list *node)

{
	t_list		*traverse;
	t_exec_node	*result;
	int			command_count;

	command_count = 0;
	traverse = node;
	while (traverse)
	{
		result = (t_exec_node *)traverse->content;
		if (result->type == AST_PIPE)
			command_count++;
		traverse = traverse->next;
	}
	command_count++;
	ft_printf("Total number of commands: %d\n", command_count);
	return (command_count);
}

/**
 * @function: check_for_pipes
 * @brief: checks if there are pipes in the command
 	proceeds if there are pipes in the command
 	return to main function if no pipes found
 * 
 * @param t_list *node : structure of linked list
 	 where it points to void content
 * 
 * @return: return 0 if pipes found, -1 if no pipes found
 */

int	check_for_pipes(t_list *node)

{
	t_list		*traverse;
	t_exec_node	*result;

	traverse = node;
	while (traverse)
	{
		result = (t_exec_node *)traverse->content;
		if (result->type == AST_PIPE)
		{
			ft_printf("Pipes detected. Returning\n");
			return (0);
		}
		traverse = traverse->next;
	}
	return (-1);
}

/**
 * @function: creating_new_pipes
 * @brief: creating a 2d array of pipes structure where
 	the first number is the pipe number and the 2nd number
 	represents the fd which is the read and write end
 * 
 * @param num_pipes : number of pipes required for the command
 * 
 * @return: pipes
 */

int	**creating_new_pipes(int num_pipes)

{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * num_pipes);
	if (pipes == NULL)
	{
		perror("Failed to allocate memory for pipes");
		return (NULL);
	}
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			perror("Failed to allocate memory for pipe descriptors");
			while (i > 0)
				free(pipes[--i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

/**
 * @function: setting_up_pipes
 * @brief: sets up each pipe malloced using the pipe function call.
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: -1 if pipes failed. 0 if successful
 */

int	setting_up_pipes(t_piping_multiple_command_params *params)

{
	params->i = 0;
	while (params->i < params->total - 1)
	{
		if (pipe(params->pipes[params->i]) == -1)
		{
			perror("pipe failed\n");
			return (-1);
		}
		params->i++;
	}
	return (0);
}
