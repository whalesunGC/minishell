/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:16:02 by apoh              #+#    #+#             */
/*   Updated: 2024/10/25 13:16:04 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_input_fd_error
 * @brief: static function to handle errors if
 	fd cannot be opened in the child process
 * 
 * @param **av : string of arguments
 	 **env : env variable
        *input : input from readline
 * 
 * @return: void function
 */

static void	handle_input_fd_error(char **av, char **env, char *input)

{
	perror("Error opening file");
	free_tokens(av);
	free(input);
	free_dup_envp(env);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

/**
 * @function: handle_dup2_error
 * @brief: static function to handle error
 	if dup2 fails in the child process
 * 
 * @param t_redirections_params *params : structure created to
 	store variables for redirections.
 	 **av : string of arguments
 	**env : env variable
       *input : input from readline
 * 
 * @return: void function
 */

static void	handling_dup2_error(t_redirections_params *params,
	char **av, char **env, char *input)

{
	perror("Error handling input redirection");
	free_tokens(av);
	free(input);
	free_dup_envp(env);
	close(params->input_fd);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

/**
 * @function: handle_execve_error
 * @brief: static function to handle error if
 	execve fails in the child process
 * 
 * @param t_redirections_params *params : structure created to
 	store variables for redirections.
 	 **av : string of arguments
 	**env : env variable
       *input : input from readline
 * 
 * @return: void function
 */

static void	handle_execve_error(t_redirections_params *params,
	char **av, char **env, char *input)

{
	perror("Error handling execve");
	if (params->command_path != av[0])
		free(params->command_path);
	free_tokens(av);
	free(input);
	free_dup_envp(env);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

/**
 * @function: child_process
 * @brief: static function to handle what the child process will be doing
 * 
 * @param t_redirections_params *params : structure created to
 	store variables for redirections.
 	 **av : string of arguments
 	**env : env variable
       *input : input from readline
 * 
 * @return: void function
 */

static void	child_process_input(t_redirections_params *params,
	char **av, char **env, char *input)

{
	params->input_fd = open(av[params->i + 1], O_RDONLY);
	if (params->input_fd < 0)
		handle_input_fd_error(av, env, input);
	if (dup2(params->input_fd, STDIN_FILENO) < 0)
		handling_dup2_error(params, av, env, input);
	close(params->input_fd);
	if (access(av[0], F_OK) == 0)
		params->command_path = av[0];
	else
		params->command_path = find_command(av, 0, env);
	params->args[0] = params->command_path;
	params->args[1] = NULL;
	if (execve(params->command_path, params->args, env) == -1)
		handle_execve_error(params, av, env, input);
}

/**
 * @function: input_redirections_operator
 * @brief: function to handle < operator
 * 
 * @param t_redirections_params *params : structure created to
 	store variables for redirections.
 	 **av : string of arguments
 	**env : env variable
       *input : input from readline
 * 
 * @return: -1 if failure, 0 if success
 */

int	input_redirections_operator(t_redirections_params *params,
	char **av, char **env, char *input)

{
	if (av[params->i + 1] != NULL)
	{
		params->pid = fork();
		if (params->pid < 0)
		{
			perror("forked failed");
			return (-1);
		}
		if (params->pid == 0)
			child_process_input(params, av, env, input);
		else
			wait(NULL);
	}
	else
	{
		ft_printf("%s :parsing error1\n", av[params->i]);
		return (-1);
	}
	return (0);
}
