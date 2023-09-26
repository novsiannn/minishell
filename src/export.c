/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:32:33 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 14:05:58 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_var_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_variable(char **envp, char *var, int var_size)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, var_size))
			if (envp[i] && envp[i][var_size] == '=')
				return (i);
		i++;
	}
	return (-1);
}

void	change_env(char *arg, int index)
{
	if (index > 0)
	{
		free(g_shell_h->envp[index]);
		g_shell_h->envp[index] = ft_strdup(arg);
	}
	else
		set_new(arg);
}

int	find_index_of_char(char *arg, char c)
{
	int	i;

	i = 0;
	while (arg[i] != c)
		i++;
	return (i);
}

void	print_export(void)
{
	int		i;

	i = 0;
	while (g_shell_h->envp[i])
	{
		if (!g_shell_h->envp[i])
			continue ;
		ft_putstr_fd("declare -x ", 2);
		ft_putstr_fd(g_shell_h->envp[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}
