/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:34:41 by wichee            #+#    #+#             */
/*   Updated: 2024/12/07 17:36:12 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	is_argument_numeric(const char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i = 1;
	if (arg[i] == '\0')
		return (0);
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @function: exit_too_many_args
 * @brief: return prompt
 * 
 * @param param: to free up the arguments which
 *		are already split into tokens
 *@param env: to free up the duplicated env
 * 
 * @return: void function
 */
void	exit_too_many_args(int *e_s)
{
	ft_dprintf(1, "exit\n");
	*e_s = 1;
}

/**
 * @function: handle_symbol
 * @brief: updates the symbol status
 *
 * @param number: number as string
 *@param is_minus: flag for symbol
 *
 * @return: void function
 */
static int	handle_symbol(char **number, int *is_minus)
{
	if (!(*number))
		return (0);
	if (*(*number) == '-')
		*is_minus = !(*is_minus);
	if (*(*number) == '-' || *(*number) == '+')
		(*number)++;
	return (1);
}

/**
 * @function: ft_chck_ul
 * @brief: checks if input string is larger thab ulong
 *
 * @param param: to free up the arguments which
 *		are already split into tokens
 *@param env: to free up the duplicated env
 *
 * @return: return 1 if outside long_min to long_max
 */
int	ft_chk_ul(char *number)
{
	char	*temp;
	int		len;
	int		is_minus;

	is_minus = 0;
	if (!handle_symbol(&number, &is_minus))
		return (1);
	len = ft_strlen(number);
	if (len == 19)
	{
		temp = malloc(sizeof(char) * 19);
		if (!temp)
			return (1);
		ft_strlcpy(temp, number, 19);
		if (ft_atoll(temp) > 922337203685477580)
			return (free(temp), 1);
		else if (ft_atoi(&number[len - 1]) > 8 && is_minus)
			return (free(temp), 1);
		else if (ft_atoi(&number[len - 1]) > 7 && !is_minus)
			return (free(temp), 1);
	}
	if (len <= 19)
		return (0);
	else
		return (1);
}
