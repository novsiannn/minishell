/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:03:19 by ikhristi          #+#    #+#             */
/*   Updated: 2023/08/08 23:51:02 by novsiann         ###   ########.fr       */
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

void    pipe_grp_mmry(t_pipe_group **pipe_grp, t_token_list *start, t_token_list *finish)
{
    int             len;

    *pipe_grp = malloc(sizeof(t_pipe_group));
    if (!pipe_grp)
        return ;
    len = ft_lstsize_n(start, finish);
    *pipe_grp = malloc(sizeof(char *) * (len + 1));
    while(start != finish)
    {
        len = ft_strlen(start->tok);
        printf("%d\n", len);
        start = start->next;
    }
    printf("%d\n",len);
}

void    create_pipe_group(t_token_list *start, t_token_list *finish)
{
    t_pipe_group    *pipe_grp;
    int             i;
    // int             k;

    i = 0;
    
    pipe_grp_mmry(&pipe_grp, start, finish);
    // while(start != finish)
    // {
    //     k = 0;
    //     pipe_grp->argv[i] = malloc((len) * sizeof(char));
    //     while(start->tok[k] != '\0')
    //     {
    //         pipe_grp->argv[i][k] = start->tok[i];
    //         k++;
    //     }
    //     i++;
    //     start = start->next;  
    // }
    while (start != finish)
	{
		// printf("start is - [%s]\n", start->tok);
		start = start->next;
	}
    // pipe_grp->next = NULL;
}

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
                return ;
            }
            else
            {
                if(!pipe_grp)
                    create_pipe_group(s_tmp, f_tmp);
                s_tmp = f_tmp;
            }
            i++;   
        }
        f_tmp = f_tmp->next;
    }
    // while (list != NULL)
	// {
	// 	printf("[%s] - [%d] \n", list->tok, list->type);
	// 	list = list->next;
	// }
}