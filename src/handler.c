/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:14:30 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/23 19:04:31 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void sig_handler(int sig)
{
    char    cwd[256];
    
    getcwd(cwd, sizeof(cwd));
	ft_strlcat(cwd, " : ", 256);
    if (sig == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        ft_putstr_fd(cwd, STDIN_FILENO);
    }
}

void	sig_handle_child(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	}
	if (sig == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
