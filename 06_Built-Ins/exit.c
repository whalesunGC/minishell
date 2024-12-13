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
 * @function: exit_is_the_only_argument
 * @brief: exits the program if the only argument is exit
 * 
 * @param **av: to free up the arguments which
 		are already split exit(EXIT_SUCCESS);
 */

static void	exit_is_the_only_argument(t_redirect_single_command_params *params,
		char **env)
{
	int	e_s;

	(void)env;
	e_s = *params->exit_status;
	rl_clear_history();
	ft_dprintf(1, "exit\n");
	ft_free(&params->msd);
	exit(e_s);
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
	rl_clear_history();
	ft_dprintf(1, "exit\n");
	exit_status = (exit_status % 256 + 256) % 256;
	ft_free(&params->msd);
	(void)env;
	exit(exit_status);
}

/**
 * @function: handle_error_numeric
 * @brief: updates the symbol status
 *
 * @param params: struct containing param data for execution
 * @param env: env
 * @param e_s: exit_status
 * @return: void function
 */
static void	handle_error_numeric(t_redirect_single_command_params *params,
		char **env, int *e_s)
{
	ft_dprintf(2, "%s: %s: numeric"
		" argument required\n", params->av[0], params->av[1]);
	*e_s = 2;
	exit_is_the_only_argument(params, env);
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
			if (!is_argument_numeric(params->av[1]))
				handle_error_numeric(params, env, e_s);
			else if (is_argument_numeric(params->av[1])
				&& ft_chk_ul(params->av[1]))
				handle_error_numeric(params, env, e_s);
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
