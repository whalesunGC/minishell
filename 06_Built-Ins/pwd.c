/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:30:40 by apoh              #+#    #+#             */
/*   Updated: 2024/09/23 12:30:46 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: pwd_command
 * @brief: shows the current working directory that you are in.
 * 
 * @param ac: the total number of arguments in my program.
 	  **av: to access the string for each argument. 
 * 
 * @return: void function
 */

void	pwd_command(int ac, char **av)

{
	char	pwd[PATH_MAX];

	if (ac > 0 && ft_strncmp(av[0], "pwd", 3) == 0)
	{
		if (ac == 1 && ft_strlen(av[0]) == 3)
		{
			if (getcwd(pwd, sizeof(pwd)) != NULL)
				ft_printf("%s\n", pwd);
			else
				perror("pwd error");
		}
		else if (ac == 1 && ft_strlen(av[0]) != 3)
			ft_printf("%s: command not found\n", av[0]);
		else
			ft_printf("%s : too many arguments\n", av[0]);
	}
}
