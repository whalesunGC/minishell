/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:54:25 by apoh              #+#    #+#             */
/*   Updated: 2024/11/20 17:54:54 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_free_all_pipes
 * @brief: to free all heredoc and regular pipes
 * 
 * @param params:
 */
static void	ft_free_all_pipes(t_piping_multiple_command_params *params)
{
	params->j = 0;
	while (params->j < params->total - 1)
	{
		close(params->pipes[params->j][0]);
		close(params->pipes[params->j][1]);
		params->j++;
	}
	if (params->pipes && params->total - 1)
		free_pipes(params->pipes, params->total - 1);
	params->j = 0;
	while (params->j < params->heredocs_count)
	{
		close(params->heredocs_pipes[params->j][0]);
		close(params->heredocs_pipes[params->j][1]);
		params->j++;
	}
	if (params->heredocs_pipes && params->heredocs_count)
		free_heredocs_pipes(params->heredocs_pipes, params->heredocs_count);
}

/**
 * @function: exit_is_the_only_argument
 * @brief: exits the program if the only argument is exit
 * 
 * @param params: **av: to free up the arguments which
 * 	are already split into tokens
 * @param env: to free up the duplicated env
 * 
 * @return: void function
 */
static void	exit_is_the_only_argument(
			t_piping_multiple_command_params *params, char **env)
{
	free_dup_envp(env);
	rl_clear_history();
	ft_dprintf(1, "exit\n");
	ft_lstclear(&params->exec_data_head, ft_free_exec_data);
	if (params->exit_status)
		free(params->exit_status);
	ft_free_all_pipes(params);
	free(params->pid_array);
	exit(EXIT_SUCCESS);
}

/**
 * @function: exit_with_one_other_argument
 * @brief: exits the program if the exit argument
 		is followed by a numeric argument
 * 
 * @param **av: to free up the arguments which
 		are already split into tokens
 	 **env: to free up the duplicated env
 * 
 * @return: void function
 */
static void	exit_with_one_other_argument(
			t_piping_multiple_command_params *params, char **env)
{
	int	exit_status;

	exit_status = 0;
	exit_status = ft_atoi(params->av[1]);
	free_dup_envp(env);
	rl_clear_history();
	ft_dprintf(1, "exit\n");
	exit_status = (exit_status % 256 + 256) % 256;
	ft_lstclear(&params->exec_data_head, ft_free_exec_data);
	if (params->exit_status)
		free(params->exit_status);
	ft_free_all_pipes(params);
	free(params->pid_array);
	exit(exit_status);
}

/**
 * @function: is_argument_numeric
 * @brief: checks if the argument being passed
 		into the program is numeric
 * 
 * @param *arg: literally means av[1],
 		the argument after the word exit.
 * 
 * @return: void function
 */

static int	is_argument_numeric(const char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i = 1;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @function: exit_command_multiple
 * @brief: illustrates what happens when i type
 	the exit command in my program for multiple piping
 * 
 * @param ac: the total number of arguments
 	**av: the strings belonging to each argument.
 	**env: duplicated env. being called so
 		i can free it and exit from here.
 * 
 * @return: void function
 */

void	exit_command_multiple(
			t_piping_multiple_command_params *params, char **env)
{
	if (params->ac > 0 && ft_strncmp(params->av[0], "exit", 4) == 0)
	{
		if (params->ac == 1 && ft_strlen(params->av[0]) == 4)
			exit_is_the_only_argument(params, env);
		else if (params->ac == 1 && ft_strlen(params->av[0]) != 4)
			ft_dprintf(1, "%s: command not found\n", params->av[0]);
		else if (params->ac == 2 && ft_strlen(params->av[0]) == 4)
		{
			if (is_argument_numeric(params->av[1]) == 0)
			{
				ft_dprintf(1, "%s: %s: numberic"
					" argument required\n", params->av[0], params->av[1]);
				exit_is_the_only_argument(params, env);
			}
			exit_with_one_other_argument(params, env);
		}
		else
		{
			ft_dprintf(1, "%s: too many arguments\n", params->av[0]);
			exit_is_the_only_argument(params, env);
		}
	}
}
