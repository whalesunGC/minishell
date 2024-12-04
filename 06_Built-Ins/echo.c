/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:13:18 by apoh              #+#    #+#             */
/*   Updated: 2024/11/20 14:33:43 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_only_n
 * @brief: checks if echo's argument to string has only n
 *
 * @param string: Input string
 *
 * @return: void function
 */
static int	ft_only_n(char *string)
{
	while (*string)
	{
		if (*string != 'n')
			return (0);
		string++;
	}
	return (1);
}

/**
 * @function: print_with_n_option
 * @brief: prints no newline if -n option is used.
 *
 * @param ac: Total number of arguments
 **av: The arguments inside your commands.
 *
 * @return: void function
 */
static void	print_with_n_option(int ac, char **av, int start)

{
	int	i;

	i = start;
	while (i < ac)
	{
		ft_dprintf(1, "%s", av[i]);
		if (i < (ac - 1))
			ft_dprintf(1, " ");
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

static void	print_without_n_option(int ac, char **av, int start)

{
	int	i;

	i = start;
	while (i < ac)
	{
		ft_dprintf(1, "%s", av[i]);
		if (i < (ac - 1))
			ft_dprintf(1, " ");
		i++;
	}
	ft_dprintf(1, "\n");
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
	int	i;
	int	n_option_count;

	i = 1;
	n_option_count = 0;
	if (ac > 0 && ft_strncmp(av[0], "echo", 4) == 0)
	{
		while (i < ac && ft_strncmp(av[i], "-n", 2)
			== 0 && ft_only_n(av[i] + 2))
		{
			n_option_count++;
			i++;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		if (n_option_count > 0)
			print_with_n_option(ac, av, i);
		else
			print_without_n_option(ac, av, i);
	}
}
