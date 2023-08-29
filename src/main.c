/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:11:47 by nikitos           #+#    #+#             */
/*   Updated: 2023/08/29 21:23:12 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	assign_env(env);
	//signals
}

int	main(int argc, char **argv, char **env)
{
	// t_token_list	*list;
	// t_token_list	*tmp;
	char			*str;

	init_main(argc, argv, env);
	while (1)
	{
		str = read_input();
		// str = "sdaskdkasdsakd\"asd\"";
		if (!str)
			return (0);
		lexer(str);
	}
	return (0);
}
