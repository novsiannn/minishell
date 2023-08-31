/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:11:47 by nikitos           #+#    #+#             */
/*   Updated: 2023/08/31 20:38:38 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	*g_shell_h = NULL;

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
		main_allocate(str);
	}
	return (0);
}
