/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:41:08 by wichee            #+#    #+#             */
/*   Updated: 2024/06/22 18:57:05 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *str);
char	*ft_strchr_gnl(const char *s, int c);
void	*ft_memmove_gnl(void *dest, const void *src, size_t n);
char	*ft_substr_gnl(const char *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_strdup_gnl(const char *s);

#endif
