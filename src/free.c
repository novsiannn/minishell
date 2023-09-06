/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:43:43 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/06 18:48:44 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_t_token(t_token_list **token)
{
	t_token_list	*tmp;
	t_token_list	*next;

	if (!(*token))
		return ;
	tmp = *token;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->tok)
			free(tmp->tok);
		free(tmp);
		tmp = next;
	}
	*token = NULL;
}

int	ft_arr_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	free_argv(char **argv)
{
	int	i;
	int	len;

	i = 0;
	len = ft_arr_len(argv);
	while (i < len)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_t_pipe(t_pipe_group **token)
{
	t_pipe_group	*tmp;
	t_pipe_group	*next;

	if (!(*token))
		return ;
	tmp = *token;
	while (tmp)
	{
		next = tmp->next;
		free_argv(tmp->argv);
		if (tmp->heredoc)
			unlink(tmp->heredoc);
		free(tmp->heredoc);
		free(tmp);
		tmp = next;
	}
	*token = NULL;
}

char	*ft_strjoin_allocate(int len1, int len2, char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!dst)
		return (NULL);
	while (i < len2)
		dst[j++] = s2[i++];
	i = 0;
	while (i < len1)
		dst[j++] = s1[i++];
	dst[j] = '\0';
	return (dst);
}

char	*ft_strjoin_minishell(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = ft_strjoin_allocate(len1, len2, s1, s2);
	return (dst);
}

void	strjoin_free(char **str, char *add)
{
	char	*res;

	res = ft_strjoin_minishell(*str, add);
	free(*str);
	*str = res;
}
