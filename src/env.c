/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:55:57 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/26 10:47:27 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_vars_env(int	*counter, char ***env, char **envp, int *i)
{
	*counter = 0;
	*i = 0;
	g_shell_h = malloc(sizeof(t_minishell));
	while (envp[*counter])
		(*counter)++;
	*env = malloc(sizeof(char *) * 1000);
	if (!(*env))
		return ;
	while (*i < 1000)
	{
		(*env)[*i] = NULL;
		(*i)++;
	}
	*i = 0;
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

int	print_env(void)
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
	return (0);
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

int	find_path_env(char **env, char *key)
{
	int	i;

	i = 0;
	while (i < 1000)
	{
		if (env[i] && ft_strnstr(env[i], key, ft_strlen(key)))
			return (i);
		i++;
	}
	return (-1);
}
