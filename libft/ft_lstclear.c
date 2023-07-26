/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:44:06 by novsiann          #+#    #+#             */
/*   Updated: 2023/01/04 16:42:57 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*first_elem;
	t_list	*next_elem;

	if (lst && del)
	{
		next_elem = *lst;
		while (next_elem)
		{
			first_elem = next_elem;
			next_elem = next_elem->next;
			del(first_elem->content);
			free(first_elem);
		}
		*lst = NULL;
	}
}
