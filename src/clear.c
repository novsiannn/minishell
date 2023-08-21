/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:01:02 by nikitos           #+#    #+#             */
/*   Updated: 2023/08/18 20:51:24 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_clear_tokens(t_token_list **tokens)
{
	t_token_list	*current;
	t_token_list	*tmp;

	if (!tokens || !(*tokens))
		return ;
	current = *tokens;
	while (current)
	{
		tmp = current->next;
		current->len = 0;
		current->i = 0;
		current->k = 0;
		free(current->tok);
		current->tok = NULL;
		current->type = 0;
		current->next = NULL;
		current->prev = NULL;
		free(current);
		current = tmp;
	}
	*tokens = NULL;
}

void	free_splited(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

void	free_readed_and_splited(char *readed, char **splited)
{
	free_splited(splited);
	free(readed);
}

int	throw_error(char *error)
{
	ft_putstr_fd(error, 2);
	free_t_pipe(&(g_shell_h->pipes));
	free_t_token(&(g_shell_h->head));
	return (1);
}
