/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:30:14 by wichee            #+#    #+#             */
/*   Updated: 2024/05/14 17:55:28 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isupper(int i)
{
	return (i >= 'A' && i <= 'Z');
}

static int	ft_islower(int i)
{
	return (i >= 'a' && i <= 'z');
}

int	ft_isalpha(int i)
{
	return (ft_isupper(i) || ft_islower(i));
}
