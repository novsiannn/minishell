/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:43:43 by nikitos           #+#    #+#             */
/*   Updated: 2023/08/21 19:13:10 by nikitos          ###   ########.fr       */
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

void	strjoin_free(char **str, char *add)
{
	char	*res;

	res = ft_strjoin(*str, add);
	free(*str);
	*str = res;
}
