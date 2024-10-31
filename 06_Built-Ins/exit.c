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
 		are already split into tokens
 	 **env: to free up the duplicated env
 	 *input: to free up readline input variable
 * 
 * @return: void function
 */

static void	exit_is_the_only_argument(char **av, char **env, char *input)

{
	free_tokens(av);
	free(input);
	free_dup_envp(env);
	rl_clear_history();
	ft_printf("exit\n");
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
 	 *input: to free up readline input variable
 * 
 * @return: void function
 */

static void	exit_with_one_other_argument(char **av,
		char **env, char *input)

{
	int	exit_status;

	exit_status = 0;
	exit_status = ft_atoi(av[1]);
	free_tokens(av);
	free(input);
	free_dup_envp(env);
	rl_clear_history();
	ft_printf("exit\n");
	exit_status = (exit_status % 256 + 256) % 256;
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
 	*input: input from readline. being called 
 		so i can free it and exit from here.
 * 
 * @return: void function
 */

void	exit_command(int ac, char **av, char **env, char *input)

{
	int	i;

	i = 0;
	if (ac > 0 && ft_strncmp(av[i], "exit", 4) == 0)
	{
		if (ac == 1 && ft_strlen(av[i]) == 4)
			exit_is_the_only_argument(av, env, input);
		else if (ac == 1 && ft_strlen(av[i]) != 4)
			ft_printf("%s: command not found\n", av[i]);
		else if (ac == 2 && ft_strlen(av[i]) == 4)
		{
			if (is_argument_numeric(av[1]) == 0)
			{
				ft_printf("%s: %s: numberic"
					" argument required\n", av[i], av[1]);
				return ;
			}
			exit_with_one_other_argument(av, env, input);
		}
		else
			ft_printf("%s: too many arguments\n", av[i]);
	}
}
