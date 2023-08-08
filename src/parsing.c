/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:03:19 by ikhristi          #+#    #+#             */
/*   Updated: 2023/08/08 14:44:27 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    check_quotes(t_token_list *tokens)
{
    int quote;

    quote = -1;
    while (tokens)
    {
        if (quote == -1)
        {
            if (tokens->type == DOUBLE_QUOTES || tokens->type == SINGLE_QUOTES)
            {
                quote = tokens->type;
            }       
        }
        else
        {
            if (quote == tokens->type)
            {
                quote = -1;
            }       
        }
        tokens = tokens->next;
    }
    if (quote != -1)
        printf("Quotes are not closed\n");
}
