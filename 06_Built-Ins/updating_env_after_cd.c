/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updating_env_after_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:31:56 by apoh              #+#    #+#             */
/*   Updated: 2024/10/10 20:32:16 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * @function: updating_env
 * @brief: takes the copy of environment and changes 
 	OLDPWD and PWD in the env variable after a
 	successful switch of the cd command.
 * 
 * @param env: ***so that i can change the values inside env
 		and can be updated and used throughout
 		the other functions.
 	old_pwd: already generated in the cd function.
 * 
 * @return: *env so that the duplicated env can	be
 		updated throughout the function
 */

char	**updating_env(char ***env, char *old_pwd)

{
	char	pwd[PATH_MAX];
	int		i;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd failed");
		return (*env);
	}
	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "PWD", 3) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("PWD=", pwd);
		}
		else if (ft_strncmp((*env)[i], "OLDPWD", 6) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("OLDPWD=", old_pwd);
		}
		i++;
	}
	return (*env);
}
