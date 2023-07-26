/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:35:11 by novsiann          #+#    #+#             */
/*   Updated: 2023/04/12 21:22:51 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_getnextline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_getnextline(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_getnextline(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_check(char *s1, char *s2)
{
	char	*res;

	if (!s1)
	{
		res = ft_strjoin_getnextline("", s2);
	}
	else
	{
		res = ft_strjoin_getnextline(s1, s2);
		free(s1);
	}
	return (res);
}

char	*ft_strjoin_getnextline(char *s1, char *s2)
{
	char	*dst;
	int		length1;
	int		length2;
	int		i;
	int		j;

	length1 = ft_strlen_getnextline(s1);
	length2 = ft_strlen_getnextline(s2);
	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * (length1 + length2 + 1));
	if (!dst)
		return (NULL);
	while (s1[i] != 0)
		dst[j++] = s1[i++];
	i = 0;
	while (s2[i] != 0)
		dst[j++] = s2[i++];
	dst[j] = '\0';
	return (dst);
}
