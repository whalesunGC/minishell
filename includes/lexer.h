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

//ft_split_ignore_quotes.c
char	**ft_split_ignore_quotes(const char *s, char c);
char	*ft_strchr_ignore_quotes(const char *s, int c);