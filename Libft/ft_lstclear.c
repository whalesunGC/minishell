/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:52:15 by wichee            #+#    #+#             */
/*   Updated: 2024/06/10 19:14:32 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_lst;

	if (*lst == NULL)
		;
	else
	{
		while (*lst != NULL)
		{
			del((*lst)->content);
			temp_lst = *lst;
			*lst = (*lst)->next;
			free(temp_lst);
		}
	}
}
