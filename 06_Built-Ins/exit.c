/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:39:14 by apoh              #+#    #+#             */
/*   Updated: 2024/09/24 21:39:20 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: exit_too_many_args
 * @brief: return prompt
 * 
 * @param param: to free up the arguments which
 *		are already split into tokens
 *@param env: to free up the duplicated env
 * 
 * @return: void function
 */

static void	exit_too_many_args(int *e_s)
{
	ft_dprintf(1, "exit\n");
	*e_s = 1;
}

/**
 * @function: exit_is_the_only_argument
 * @brief: exits the program if the only argument is exit
 * 
 * @param **av: to free up the arguments which
 		are already split exit(EXIT_SUCCESS);
 */

static void	exit_is_the_only_argument(t_redirect_single_command_params *params,
		char **env)

{
	free_dup_envp(env);
	rl_clear_history();
	ft_dprintf(1, "exit\n");
	ft_lstclear(&params->exec_data_head, ft_free_exec_data);
	if (params->exit_status)
		free(params->exit_status);
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
		t_redirect_single_command_params *params,
		char **env)

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
	if (arg[i] == '\0')
		return (0);
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @function: exit_command
 * @brief: illustrates what happens when i type
 	the exit command in my program
 * 
 * @param ac: the total number of arguments
 	**av: the strings belonging to each argument.
 	**env: duplicated env. being called so
 		i can free it and exit from here.
 * 
 * @return: void function
 */

void	exit_command(t_redirect_single_command_params *params,
		char **env, int *e_s)
{
	if (params->ac > 0 && ft_strncmp(params->av[0], "exit", 4) == 0)
	{
		if (params->ac == 1 && ft_strlen(params->av[0]) == 4)
			exit_is_the_only_argument(params, env);
		else if (params->ac == 1 && ft_strlen(params->av[0]) != 4)
			ft_dprintf(2, "%s: command not found\n", params->av[0]);
		else if (params->ac >= 2 && ft_strlen(params->av[0]) == 4)
		{
			if (is_argument_numeric(params->av[1]) == 0)
			{
				ft_dprintf(1, "%s: %s: numberic"
					" argument required\n", params->av[0], params->av[1]);
				exit_is_the_only_argument(params, env);
			}
			else if (params-> ac == 2)
				exit_with_one_other_argument(params, env);
			else
			{
				ft_dprintf(2, "%s: too many arguments\n", params->av[0]);
				exit_too_many_args(e_s);
				return ;
			}
		}
	}
}
