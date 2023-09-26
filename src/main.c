/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:11:47 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 19:44:17 by nikitos          ###   ########.fr       */
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

void	count_last(t_pipe_group *pipes)
{
	g_shell_h->last = -1;
	while (pipes)
	{
		pipes = pipes->next;
		g_shell_h->last++;
	}
}

void	ft_lexer(void)
{
	put_type_tok(&(g_shell_h->head));
	split_words(&(g_shell_h->head));
}

void	free_all(char *readed, char **splited)
{
	free_t_token(&(g_shell_h->head));
	free_t_pipe(&(g_shell_h->pipes));
	free(readed);
	free_splited(splited);
}

int	main(int argc, char **argv, char **env)
{
	char			*readed;
	char			**splited;

	init_main(argc, argv, env);
	while (1)
	{
		readed = read_input();
		if (!readed)
			return (0);
		splited = ft_split_minishell(readed);
		if (main_allocate(splited, readed) == 1)
			continue ;
		count_last(g_shell_h->pipes);
		executor(g_shell_h->pipes);
		free_all(readed, splited);
	}
	free_shell_h();
	return (0);
}
