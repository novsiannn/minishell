/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:33:57 by novsiann          #+#    #+#             */
/*   Updated: 2023/04/10 20:10:57 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_full_line(char *s, char *save, int i)
{
	while (save[i] && save[i] != '\n')
	{
		s[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_get_line(char *save)
{
	char	*s;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		s = (char *)malloc(sizeof(char) * (i + 2));
	else
		s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	i = 0;
	s = ft_full_line(s, save, i);
	return (s);
}

char	*ft_save(char *old_str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (old_str[i] && old_str[i] != '\n')
		i++;
	if (!old_str[i])
	{
		free(old_str);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen_getnextline(old_str) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (old_str[i])
		s[j++] = old_str[i++];
	s[j] = '\0';
	free (old_str);
	return (s);
}

//Founding our line
char	*ft_read_and_save(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr_getnextline(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save = ft_strjoin_check(save, buff);
	}
	free(buff);
	return (save);
}
// The main functuion

char	*get_next_line(int fd)
{
	static char	*save[65000];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 64999)
		return (0);
	if (read(fd, 0, 0) < 0)
	{
		if (save[fd])
			free(save[fd]);
		save[fd] = NULL;
		return (NULL);
	}
	save[fd] = ft_read_and_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	save[fd] = ft_save(save[fd]);
	return (line);
}
