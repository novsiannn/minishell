/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:12:02 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/09 09:12:32 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe_group    *create_pipe_group(t_token_list *start, t_token_list *finish)
{
    t_pipe_group    *pipe_grp;
    int             i;
    int             k;

    i = 0;
    k = 0;
    pipe_grp_mmry(&pipe_grp, start, finish);
    // while(pipe_grp->argv[i] != NULL)
    // {
    //     printf("String - [%s]\n", pipe_grp->argv[i]);
    //     i++;
    // }
    // Сюда позже добавить объявление других переменных с структуры. Спасибо
    pipe_grp->next = NULL;
    return (pipe_grp);
}

void    pipe_grp_mmry(t_pipe_group **pipe_grp, t_token_list *start, t_token_list *finish)
{
    int             len;
    int             i;
    int             k;

    i = 0;
    *pipe_grp = malloc(sizeof(t_pipe_group));
    if (!pipe_grp)
        return ;
    len = ft_lstsize_n(start, finish);
    (*pipe_grp)->argv = ft_calloc(sizeof(char **), (len + 1));
    while (start != finish)
    {
        k = 0;
        len = ft_strlen(start->tok);
        (*pipe_grp)->argv[i] = ft_calloc(sizeof(char *), (len + 1));
        while (k <= len)
        {
            (*pipe_grp)->argv[i][k] = start->tok[k];
            k++;
        }
        i++;
        start = start->next;
    }
}
