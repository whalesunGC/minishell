/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:01:18 by wichee            #+#    #+#             */
/*   Updated: 2024/10/05 12:02:06 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		lexer(char *input);
char 	**tokenize(char *input);

//Lexer Utils
void	ft_free_split(char **split);