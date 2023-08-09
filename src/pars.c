/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:03:19 by ikhristi          #+#    #+#             */
/*   Updated: 2023/08/09 09:44:23 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



void    parse(t_token_list *list)
{
    t_token_list    *s_tmp;
    t_token_list    *f_tmp;
    t_pipe_group    *pipe_grp;
    int             i;

    i = 0;
    f_tmp = list;
    s_tmp = list;
    pipe_grp = NULL;
    while(f_tmp != NULL)
    {
        if(f_tmp->tok[i] == '|')
        {
            if(f_tmp->tok[i + 1] == '|')
            {
                printf("Invalid input\n");
                // ft_clear_tokens(&list); тут проеб, когда идет 2 пайпы, оно выдает ошибку как и нужно, но при следующем вводе любого значения, выдает segfault.
                return ;
            }
            else
            {
                if(!pipe_grp)
                    pipe_grp = create_pipe_group(s_tmp, f_tmp);
                // else
                //     pipe_grp->next = create_pipe_group(s_tmp, f_tmp);
                s_tmp = f_tmp;
            }
            i++;   
        }
        f_tmp = f_tmp->next;
    }
    i = 0;
    // while(pipe_grp->argv[i] != NULL)
    // {
    //     printf("String - [%s]\n", pipe_grp->argv[1]);
    //     i++;
    // }
}
