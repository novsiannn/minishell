/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:11:47 by nikitos           #+#    #+#             */
/*   Updated: 2023/07/31 17:18:55 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main()
{
	char *str;
	t_token_list	*tokens;

	while(1)
	{
		str = read_input();
		if (!str)
			return (0);
		tokens = lexer(str);
	}
	return (1);
}