/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:34:10 by apoh              #+#    #+#             */
/*   Updated: 2024/10/24 15:34:18 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_output_fd_error
 * @brief: function to handle error in child process if
 	fd cannot be opened in redirections_uilts2.c
 	and redirections_utils4.c
 * 
 * @param **av : string of arguments
         **env : env variable
         input : input from readline
 * 
 * @return: void function
 */

void	handle_output_fd_error(char **av, char **env, char *input)

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
 * @brief: function to handle dup2_error in child process
 	in redirections_utils2.c and redirections_utils4.c
 * 
 * @param t_redirections_params *params : structure created to
 	store variables for redirections.
 	 **av : string of arguments
 	**env : env variable
       *input : input from readline
 * 
 * @return: void function
 */

void	handle_dup2_error(t_redirections_params *params,
	char **av, char **env, char *input)

{
	perror("Error handling output redirection");
	free_tokens(av);
	free(input);
	free_dup_envp(env);
	close(params->output_fd);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

/**
 * @function: handle_no_command
 * @brief: function to handle no commands 
 	in child process if there is no command
 	in front of the redirection operator
 	in redirections_utils2.c and redirections_utils4.c
 * 
 * @param **av : string of arguments
         **env : env variable
        *input : input from readline
 * 
 * @return: void function
 */

void	handle_no_command(char **av, char **env, char *input)

{
	free_tokens(av);
	free(input);
	free_dup_envp(env);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

/**
 * @function: handle_command_error
 * @brief: function to handle execve error in child process
	 in redirections_utils2.c and redirections_utils4.c
 * 
 * @param t_redirections_params *params : structure created to
 	store variables for redirections.
 	 **av : string of arguments
 	**env : env variable
       *input : input from readline
 * 
 * @return: void function
 */

void	handle_command_error(t_redirections_params *params,
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
