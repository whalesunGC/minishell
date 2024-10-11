/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:52:08 by apoh              #+#    #+#             */
/*   Updated: 2024/09/20 18:52:09 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	handle_cd_error(const char *dir)

{
	perror(dir);
}

static void	handle_ac_is_1(void)

{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
	{
		ft_printf("HOME environment variable is not set\n");
		return ;
	}
	if (chdir(home) != 0)
		handle_cd_error(home);
}

static void	handle_ac_is_2(char **av)

{
	if (ft_strncmp(av[1], ".", 1) == 0 && ft_strlen(av[1]) == 1)
		return ;
	else if (ft_strncmp(av[1], "..", 2) == 0 && ft_strlen(av[1]) == 2)
	{
		if (chdir("..") != 0)
			handle_cd_error(av[1]);
	}
	else if (chdir(av[1]) != 0)
	{
		handle_cd_error(av[1]);
	}
}

/*ft_printf("Cd: %s: %s\n", strerror(errno), av[1]);*/

void	cd_command(int ac, char **av)

{
	if (ac > 0 && ft_strncmp(av[0], "cd", 2) == 0)
	{
		if (ac == 1 && ft_strlen(av[0]) == 2)
			handle_ac_is_1();
		else if (ac >= 1 && ft_strlen(av[0]) > 2)
			ft_printf("%s: command not found\n", av[0]);
		else if (ac == 2)
			handle_ac_is_2(av);
		else
			ft_printf("Too many arguments!\n");
	}
	else
		return ;
}
