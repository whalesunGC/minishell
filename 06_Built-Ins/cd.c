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

#include "../includes/minishell.h"

/**
 * @function: handle_cd_error
 * @brief: prints error message using perror
 * 
 * @param dir: prints the invalid directory if change is unsuccessful.
 * 
 * @return: void function
 */

static void	handle_cd_error(const char *dir)

{
	perror(dir);
}

/**
 * @function: change_to_home_directory
 * @brief: process of getting your "HOME" directory from getenv
 		and then changes it. If not successful, print
 		error message using handle_cd_error function.
 * 
 * @param NIL
 * 
 * @return: void function
 */

static void	change_to_home_directory(void)

{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
	{
		ft_dprintf(2, "HOME environment variable is not set\n");
		return ;
	}
	if (chdir(home) != 0)
		handle_cd_error(home);
}

/**
 * @function: changing_directories
 * @brief: looking at the arguments after the cd argument is read.
 		example : . - do nothing
 			: .. - change one step up from current directory.
 			: ~ - change to home directory.
 	if change is unsuccessful, handle_cd_error
 	function to print out error message
 * 
 * @param **av: the arguments inside your command.
 * 
 * @return: void function
 */

static void	changing_directories(char **av)

{
	if (ft_strncmp(av[1], ".", 1) == 0 && ft_strlen(av[1]) == 1)
		return ;
	else if (ft_strncmp(av[1], "..", 2) == 0 && ft_strlen(av[1]) == 2)
	{
		if (chdir("..") != 0)
			handle_cd_error(av[1]);
	}
	else if (ft_strncmp(av[1], "~", 1) == 0 && ft_strlen(av[1]) == 1)
		change_to_home_directory();
	else if (chdir(av[1]) != 0)
		handle_cd_error(av[1]);
}

/**
 * @function: cd_command
 * @brief: illustrates what happens when i type
 	the cd command in my program.
 * 
 * @param ac: the total number of arguments in my program.
 	  **av: to access the string for each argument. 
 	  ***env : triple *** because i want to update the env variable
 	  	to be used in other functions.
 * 
 * @return: (*env) because i wanted to use the updated environment
 		contents in other functions.
 */

char	**cd_command(int ac, char **av, char ***env)

{
	char	old_pwd[PATH_MAX];

	if (ac > 0 && ft_strncmp(av[0], "cd", 2) == 0)
	{
		if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		{
			perror("getcwd failed");
			return (*env);
		}
		if (ac == 1 && ft_strlen(av[0]) == 2)
		{
			change_to_home_directory();
			updating_env(env, old_pwd);
		}
		else if (ac >= 1 && ft_strlen(av[0]) > 2)
			ft_dprintf(2, "%s: command not found\n", av[0]);
		else if (ac == 2)
		{
			changing_directories(av);
			updating_env(env, old_pwd);
		}
		else
			ft_dprintf(2, "Too many arguments!\n");
	}
	return (*env);
}
