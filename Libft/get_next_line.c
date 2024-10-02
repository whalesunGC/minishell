/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:38:52 by wichee            #+#    #+#             */
/*   Updated: 2024/08/14 16:50:33 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	count;

	count = 0;
	while (*str++ != '\0')
		count++;
	return (count);
}

static char	*read_from_buffer(int fd, char **buffer, ssize_t *r_result)
{
	if (*r_result == -1)
		return (NULL);
	*buffer = malloc(BUFFER_SIZE + 1);
	if (!*buffer)
		return (NULL);
	*r_result = read(fd, *buffer, BUFFER_SIZE);
	if (*r_result == 0 || *r_result == -1)
		return (free(*buffer), NULL);
	(*buffer)[*r_result] = '\0';
	return (*buffer);
}

static char	*create_line(char **stash, ssize_t *r_result)
{
	char	*line;
	char	*temp;

	temp = *stash;
	if (*r_result != 0)
	{
		line = ft_substr_gnl(*stash, 0,
				(ft_strchr_gnl(*stash, '\n') - temp) + 1);
		if (!line)
			return (NULL);
		*stash = ft_strdup_gnl(ft_strchr_gnl(*stash, '\n') + 1);
	}
	else
	{
		if (**stash == '\0')
			line = NULL;
		else
		{
			line = ft_strdup_gnl(*stash);
			if (!line)
				return (NULL);
		}
		*stash = NULL;
	}
	return (free(temp), line);
}

static char	*join_str(int fd, char **stash, ssize_t *r_result)
{
	char	*buffer;
	char	*temp;

	temp = *stash;
	buffer = read_from_buffer(fd, &buffer, r_result);
	if (!buffer && *r_result != 0)
		return (free(temp), NULL);
	else if (!buffer && *r_result == 0)
		return (*stash);
	*stash = ft_strjoin_gnl(*stash, buffer);
	if (*stash == NULL)
		return (free(temp), free(buffer), NULL);
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	ssize_t		*r_result;

	r_result = (ssize_t[]){1};
	if (BUFFER_SIZE > 2147479552 || BUFFER_SIZE <= 0 || fd == -1)
		return (NULL);
	while (1)
	{
		if (stash == NULL)
		{
			stash = read_from_buffer(fd, &stash, r_result);
			if (!stash)
				return (NULL);
		}
		else if (ft_strchr_gnl(stash, '\n') || *r_result == 0)
			return (create_line(&stash, r_result));
		else
			stash = join_str(fd, &stash, r_result);
	}
}
