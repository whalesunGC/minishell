/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:10:02 by apoh              #+#    #+#             */
/*   Updated: 2024/10/24 16:10:07 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: child_process
 * @brief: handles the actions inside the child process
 	earlier functions are declared in redirections_utils1.c
 * 
 * @param t_redirections_params *params : structure created to
 	store variables for redirections.
 	 **av : string of arguments
 	**env : env variable
       *input : input from readline
 * 
 * @return: void function
 */

static void	child_process_append(t_redirections_params *params,
	char **av, char **env, char *input)

{
	params->output_fd = open(av[params->i + 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (params->output_fd < 0)
		handle_output_fd_error(av, env, input);
	if (dup2(params->output_fd, STDOUT_FILENO) < 0)
		handle_dup2_error(params, av, env, input);
	close(params->output_fd);
	if (ft_strcmp(av[0], ">>") == 0)
		handle_no_command(av, env, input);
	else
	{
		if (access(av[0], F_OK) == 0)
			params->command_path = av[0];
		else
			params->command_path = find_command(av, 0, env);
		params->args[0] = params->command_path;
		params->args[1] = NULL;
		if (execve(params->command_path, params->args, env) == -1)
			handle_command_error(params, av, env, input);
	}
}

/**
 * @function: append_output_redirections_operator
 * @brief: handles >> operator if it is encountered
 * 
 * @param t_redirections_params *params : structure created to
 	store variables for redirections.
 	 **av : string of arguments
 	**env : env variable
       *input : input from readline
 * 
 * @return: -1 if failure, 0 if success
 */

int	append_output_redirections_operator(t_redirections_params *params,
	char **av, char **env, char *input)

{
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("fork failed");
		return (-1);
	}
	if (params->pid == 0)
		child_process_append(params, av, env, input);
	else
		wait(NULL);
	return (0);
}
