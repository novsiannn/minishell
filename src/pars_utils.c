/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:18:14 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/08 23:20:57 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_lstsize_n(t_token_list *start, t_token_list *finish)
{
	int	i;

	i = 0;
	while(start != finish)
	{
		i++;
		start = start->next;
	}
	return (i);
}