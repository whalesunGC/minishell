/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:03:17 by wichee            #+#    #+#             */
/*   Updated: 2024/06/11 08:48:38 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*create_and_add_node(t_list **new_lst, void *(*f)(void *)
, void (*del)(void *), void *content)
{
	t_list	*new_node;
	void	*new_content;

	new_content = f(content);
	if (!new_content)
	{
		ft_lstclear(new_lst, del);
		return (NULL);
	}
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		del(new_content);
		ft_lstclear(new_lst, del);
		return (NULL);
	}
	ft_lstadd_back(new_lst, new_node);
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*new_lst;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		if (!create_and_add_node(&new_lst, f, del, lst->content))
			return (NULL);
		lst = lst->next;
	}
	return (new_lst);
}
