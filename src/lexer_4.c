/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:16:37 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/26 18:17:55 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	put_skip(t_token_list **tmp)
{
	if ((*tmp)->type && (*tmp)->type != -1)
	{
		*tmp = (*tmp)->next;
		return (1);
	}
	return (0);
}

void	delete_empty_node(t_token_list **list)
{
	t_token_list	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->tok);
		tmp = tmp->next;
	}
}

int	main_allocate(char **splited, char *readed)
{
	if (ft_init_list(&(g_shell_h->head), readed, splited) == 1)
	{
		free_readed_and_splited(readed, splited);
		return (1);
	}
	ft_lexer();
	expander();
	g_shell_h->pipes = redirection();
	if (g_shell_h->pipes == NULL)
	{
		free_readed_and_splited(readed, splited);
		return (1);
	}
	return (0);
}
