/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:32:33 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/15 14:34:25 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_keyword(char *args)
{
    int index;
    int i;

    i = 0;
    index = 0;
    if (!args || args[0] || args[0] == '=')
        return (1);
    if (args[ft_strlen(args) - 1] != '=')
        return (1);
    while (args[i] && args[i] != '=')
    {
        if (ft_isalnum(args[i]))
            index = 1;
        else
            if (ft_isdigit(args[i]) && !index)
                return (1);
        else if (args[i] != '_')
			return (1);
		i++;
    }
    return (0);
}

void	change_env(char *arg, int index)
{
	g_shell_h->envp[index] = ft_strdup(arg);
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
