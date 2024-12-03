/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:02:41 by apoh              #+#    #+#             */
/*   Updated: 2024/09/24 16:02:47 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: free_unset_variable
 * @brief: upon successful search for the specific var_name
 	free that particular pointer and shift the other variables up.
 * 
 * @param **env : copy of envp to be used for manipulation.
 * 
 * @return: void function
 */

static void	free_unset_variable(char **env, int i)

{
	free(env[i]);
	while (env[i] != NULL)
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
}

/**
 * @function: unset_variable
 * @brief: searching env to see if the variable name can be found.
 		if yes, free that line and move the rest of the variables up.
 		if no, dont do anything.
 * 
 * @param var_to_unset: var_name to be searched in the environment.
 	  **env : copy of envp to be manipulated.
 * 
 * @return: return (1) if successful search
 		return (0) if unsuccessful
 */

static int	unset_variable(char *var_to_unset, char **env)

{
	char	*equal_sign;
	int		i;
	size_t	length;

	i = 0;
	while (env[i] != NULL)
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
			length = equal_sign - env[i];
		else
			length = ft_strlen(env[i]);
		if (ft_strncmp(env[i], var_to_unset, length) == 0
			&& ft_strlen(var_to_unset) == length)
		{
			free_unset_variable(env, i);
			return (1);
		}
		else
			i++;
	}
	return (0);
}

/**
 * @function: unset_command
 * @brief: illustrates what happens when i type
 	the unset command in my program.
 * 
 * @param ac: the total number of arguments in my program.
 	  **av: to access the string for each argument. 
 	  **env : copy of envp to be manipulated
 * 
 * @return: return (env) so that the env can be used in other functions.
 */

char	**unset_command(int ac, char **av, char **env)

{
	int	j;

	j = 1;
	if (ac > 0 && ft_strncmp(av[0], "unset", 5) == 0)
	{
		if (ac >= 1 && ft_strlen(av[0]) == 5)
		{
			if (ac == 1)
				ft_dprintf(2, "%s: Nothing to unset\n", av[j]);
			while (j < ac)
			{
				if (unset_variable(av[j], env) == 0)
					ft_dprintf(2, "%s: unset string error\n", av[j]);
				else
					ft_dprintf(2, "%s: unset string removed\n", av[j]);
				j++;
			}
		}
	}
	return (env);
}
