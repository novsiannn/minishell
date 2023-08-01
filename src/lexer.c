/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:23:45 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/01 14:26:37 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token_list	*list_without_spaces(char *str, int start, int end)
{
	char *new_str;
	t_token_list *list;
	int tmp_start = start;
	int	i;

	i = 0;
	new_str = malloc(sizeof(char *) * (end - tmp_start + 1));
	if (!new_str)
		exit (0);
	while(tmp_start < end)
		new_str[i++] = str[tmp_start++];
	list = create_token(end - start, new_str, 1);
	return (list);
}

void	list_value_split(t_token_list *list)
{
	int i;
	int type;

	while(list != NULL)
	{
		i = 0;
		type = get_type(list->tok[i]);
		while(list->tok[i] != '\0')
		{
			if (get_type(list->tok[i]) != type)
				printf("another\n");
			i++;
		}
		printf("\n NEXT LINKED LIST\n\n");
		list = list->next;
	}
}

void	lexer(char *input)//
{
	int				start;
	int				end;
	// int				type;
	t_token_list	*list;

	start = 0;
	end = 0;
	// type = get_type(input[i]);
	while (input[start])
	{
		while (((input[start] >= 8 && input[start] <= 14) || input[start] == 32) && input[start] != '\0')
			start++;
		end = start;
		while (!(input[start] >= 8 && input[start] <= 14) && input[end] != ' '  && input[end] != '\0')
			end++;
		if (!list)
			list = list_without_spaces(input, start, end);
		else	
			ft_lstadd_back_minishell(&list, list_without_spaces(input, start, end));
		start = end;
	}
	list_value_split(list);
	ft_clear_tokens(&list);
	write(1, "\n", 1);
	// return (list);
}
