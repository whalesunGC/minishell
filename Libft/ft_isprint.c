/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:32:56 by wichee            #+#    #+#             */
/*   Updated: 2024/05/16 20:25:37 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_isprint(int i)
{
	return (i >= 32 && i <= 126);
}
