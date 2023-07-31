/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:23:45 by novsiann          #+#    #+#             */
/*   Updated: 2023/07/31 19:23:30 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


t_token_list	*lexer(char *input)
{
	int				i;
	int				type;
	t_token_list	*list;

	i = 0;
	type = get_type(input[i]);
	while (input[i])
	{

	}
	printf("%d", type);
	return (list);
}