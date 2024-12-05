/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:01:50 by apoh              #+#    #+#             */
/*   Updated: 2024/09/24 18:01:56 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: env_command
 * @brief: illustrates what happens when i type
 	the env dommand in my program
 * 
 * @param ac: the total number of arguments in my program.
 	  **av: to access the string for each argument. 
 	  ***env : triple *** because i want to update the env variable
 	  	to be used in other functions.
 * 
 * @return: (*env) because i wanted to use the updated environment
 		contents in other functions.
 */

void	env_command(int ac, char **av, char **env, int *e_s)
{
	int	i;

	i = 0;
	if (ac > 0 && ft_strncmp(av[0], "env", 3) == 0)
	{
		if (ac == 1 && ft_strlen(av[0]) == 3)
		{
			while (env[i] != NULL)
			{
				if (ft_strnstr(env[i], "=''", ft_strlen(env[i])) == NULL)
					ft_printf("%s\n", env[i]);
				i++;
			}
		}
		else if (ac >= 1 && ft_strlen(av[0]) != 3)
		{
			*e_s = 1;
			ft_dprintf(1, "%s: too many arguments\n", av[0]);
		}
		else
		{
			*e_s = 1;
			ft_dprintf(1, "%s: '%s': too many arguments\n", av[0], av[1]);
		}
	}
}
