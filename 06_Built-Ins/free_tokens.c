/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:25:40 by apoh              #+#    #+#             */
/*   Updated: 2024/09/20 17:25:52 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: free_tokens
 * @brief: freeing the individual arguments after i have tokenise it.
 * 
 * @param **av: to access the string for each argument. 
 * 
 * @return: void function
 */

void	free_tokens(char **av)

{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		free(av[i]);
		i++;
	}
	free(av);
}
