/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:13:18 by apoh              #+#    #+#             */
/*   Updated: 2024/09/18 16:13:21 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: print_with_n_option
 * @brief: prints no newline if -n option is used.
 * 
 * @param ac: Total number of arguments
 	**av: The arguments inside your commands.
 * 
 * @return: void function
 */

static void	print_with_n_option(int ac, char **av)

{
	int	i;

	i = 2;
	while (i < ac)
	{
		ft_printf("%s", av[i]);
		if (i < (ac - 1))
			ft_printf(" ");
		i++;
	}
}

/**
 * @function: print_without_n_option
 * @brief: prints a newline if -n option is not used.
 * 
 * @param ac: Total number of arguments
 	**av: The arguments inside your commands.
 * 
 * @return: void function
 */

static void	print_without_n_option(int ac, char **av)

{
	int	i;

	i = 1;
	while (i < ac)
	{
		ft_printf("%s", av[i]);
		if (i < (ac - 1))
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
}

/**
 * @function: echo_command
 * @brief: illustrates what happens if echo command is used.
 * 
 * @param ac: Total number of arguments
 	**av: The arguments inside your commands.
 * 
 * @return: void function
 */

void	echo_command(int ac, char **av)

{
	if (ac > 0 && ft_strncmp(av[0], "echo", 4) == 0)
	{
		if (ac == 1)
			ft_printf("\n");
		else if (ac > 1 && ft_strncmp(av[1], "-n", 2) == 0
			&& ft_strlen(av[1]) == 2)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			print_with_n_option(ac, av);
		}
		else if (ac == 2 && ft_strncmp(av[1], "$?", 2) == 0
			&& ft_strlen(av[1]) == 2)
		{
			ft_printf("%d\n", g_exit_status);
			g_exit_status = 0;
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			print_without_n_option(ac, av);
		}
	}
}
