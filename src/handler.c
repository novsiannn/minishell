/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:14:30 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/03 21:50:35 by ikhristi         ###   ########.fr       */
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
