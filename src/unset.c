/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:07:16 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/15 18:13:09 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	b_unset(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = find_path_env(g_shell_h->envp, args[i]);
		if (j != -1 && g_shell_h->envp[j])
		{
			free((g_shell_h->envp[j]));
			g_shell_h->envp[j] = NULL;
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
