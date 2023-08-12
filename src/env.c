/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:55:57 by ikhristi          #+#    #+#             */
/*   Updated: 2023/08/11 21:08:12 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_vars_env(int	*counter, char ***env, char **envp, int *i)
{
	*counter = 0;
	*i = 0;
	g_shell_h = malloc(sizeof(t_minishell));
	*env = malloc(sizeof(char *) * 1000);
	if (!env)
		return ;
	while (envp[*counter])
		(*counter)++;
	//Проверить для экспорта
}

int	assign_env(char **envp)
{
	int		count;
	char	**env;
	int		i;

	init_vars_env(&count, &env, envp, &i);
	while (i < count)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (0);
		i++;
	}
	envp[i] = NULL;
	g_shell_h->envp = env;
	g_shell_h->current_env = i;
	g_shell_h->pipes = NULL;
	g_shell_h->error = 0;
	return (1);
}

void	print_env(void)
{
	int	i;

	i = 0;
	while (i < g_shell_h->current_env)
	{
		if (g_shell_h->envp[i] != NULL)
		{
			printf("%s\n", g_shell_h->envp[i]);
		}
		i++;
	}
}

char	*find_in_env(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (i < g_shell_h->current_env)
	{
		if (g_shell_h->envp[i] != NULL)
		{
			ret = ft_strnstr(g_shell_h->envp[i], str, \
				ft_strlen(g_shell_h->envp[i]));
			if (ret != NULL)
			{
				ret += ft_strlen(str) + 1;
				return (ret);
			}
		}
		i++;
	}
	return ("\0");
}
