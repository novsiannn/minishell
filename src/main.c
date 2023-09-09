/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:11:47 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/09 16:52:10 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	*g_shell_h = NULL;

void	init_main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	assign_env(env);
	signals();
}

void	ft_lexer(void)
{
	put_type_tok(&(g_shell_h->head));
	split_words(&(g_shell_h->head));
	// delete_empty_node(&(g_shell_h->head));
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
		// str = "sas | ad \"asdf\"";
		if (!str)
			return (0);
		main_allocate(str);
	}
	return (0);
}
