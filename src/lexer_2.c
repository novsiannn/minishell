/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:29:07 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/08 19:29:45 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_node(t_token_list *tmp, char *buf, t_token_list **list)
{
	char	*str;

	str = get_word(buf, (*list)->i, (*list)->k);
	free(tmp->tok);
	tmp->tok = ft_strdup(str);
	tmp->len = ft_strlen(tmp->tok);
	(*list)->corrective_token = 1 ;
	free(str);
}

void	last_letter(t_token_list *list, char *buf, int sta, int end)
{
	char	*str;

	str = get_word(buf, sta, end + 1);
	list = ft_put_between_token(list, list->next, str);
	free(str);
}

void	list_value_cmp(t_token_list **list)
{
	int				i;
	int				type;
	t_token_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		i = 0;
		type = get_type(temp->tok[i]);
		while (temp->tok[i] != '\0')
		{
			if (get_type(temp->tok[i]) != type)
			{
				list_value_split(&temp, type);
				break ;
			}
			else
				i++;
		}
		temp = temp->next;
	}
}
