/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:43:43 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 18:08:54 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_shell_h(void)
{
	int	i;

	i = 0;
	free_t_pipe(&(g_shell_h->pipes));
	free_t_token(&(g_shell_h->head));
	while (i < g_shell_h->current_env)
	{
		free(g_shell_h->envp[i]);
		i++;
	}
	free(g_shell_h->envp);
	free(g_shell_h);
	clear_history();
}

void	free_t_token(t_token_list **token)
{
	t_token_list	*tmp;
	t_token_list	*next;

	if (!(*token))
		return ;
	tmp = *token;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->tok)
			free(tmp->tok);
		free(tmp);
		tmp = next;
	}
	*token = NULL;
}

void	free_string_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

int	ft_arr_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (i < 50)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
