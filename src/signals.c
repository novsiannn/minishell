/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:06:50 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/23 19:04:09 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    signals(void)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sig_handler);
}

void    child_sig(void)
{
    signal(SIGQUIT, sig_handle_child);
	signal(SIGINT, sig_handle_child);
}