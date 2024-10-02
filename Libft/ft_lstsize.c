/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:24:53 by wichee            #+#    #+#             */
/*   Updated: 2024/06/06 15:21:12 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	if (lst == NULL)
		;
	else
	{
		while (lst != NULL)
		{
			lst = lst->next;
			size++;
		}
	}
	return (size);
}
