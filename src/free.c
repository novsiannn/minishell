/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:43:43 by nikitos           #+#    #+#             */
/*   Updated: 2023/08/29 21:32:14 by nikitos          ###   ########.fr       */
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

char	*ft_strjoin_reverse(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;

	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *) malloc(s1_len + s2_len + 1);
	if (!res)
		return (NULL);
	ft_memmove(res, s2, s1_len);
	ft_memmove(res + s2_len, s1, s1_len + 1);
	return (res);
}

void	strjoin_free(char **str, char *add)
{
	char	*res;

	res = ft_strjoin_reverse(*str, add);
	free(*str);
	*str = res;
}
