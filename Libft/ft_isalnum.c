/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:13:44 by wichee            #+#    #+#             */
/*   Updated: 2024/05/14 17:54:22 by wichee           ###   ########.fr       */
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

static int	ft_isdigit(int i)
{
	return (i >= '0' && i <= '9');
}

int	ft_isalnum(int i)
{
	return (ft_isupper(i) || ft_islower(i) || ft_isdigit(i));
}
