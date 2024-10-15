/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:22 by wichee            #+#    #+#             */
/*   Updated: 2024/10/15 15:03:39 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

//input.c
char	*input_clean(char *input);
char	*ft_input_swap_whitespace(char *input);
char	*ft_input_remove_extra_whitespace(char *input);
char	*ft_input_add_whitespace(char *input);
//input_utils.c
int		ft_iswhitespace(int i);
int		ft_isspecial(int i);

#endif