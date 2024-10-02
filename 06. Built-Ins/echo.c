/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:13:18 by apoh              #+#    #+#             */
/*   Updated: 2024/10/02 15:07:30 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell"

static void	print_without_n(int ac, char **av)

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

static void	print_with_n(int ac, char **av)

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
	ft_printf("%%");
	ft_printf("\n");
}

void	echo_command(int ac, char **av)

{
	if (ac > 0 && ft_strncmp(av[0], "echo", 4) == 0)
	{
		if (ac == 1)
			ft_printf("\n");
		else if (ac > 1 && (ft_strncmp(av[1], "-n", 2) == 0))
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			print_without_n(ac, av);
		}
		else if (ac == 2 && ft_strncmp(av[1], "$?", 2) == 0)
		{
			ft_printf("%d\n", g_exit_status);
			g_exit_status = 0;
		}
		else if (ac > 1 && (ft_strncmp(av[1], "-n", 2) != 0))
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			print_with_n(ac, av);
		}
	}
	else
		return ;
}
