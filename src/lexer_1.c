/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:23:45 by novsiann          #+#    #+#             */
/*   Updated: 2023/09/04 20:53:08 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_split_minishell(char *input)
{
	char	**array;
	int		words;

	words = get_words_minishell(input);
	array = malloc(sizeof(char *) * (words + 1));
	array[words] = 0;
	fill_array(array, input);
	return (array);
}

int	check_closed_brackets(char **splited)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (splited[i])
	{
		if (quote)
		{
			if (quote == 1 && (ft_strcmp(splited[i], "\'") == 0))
				quote = 0;
			else if (quote == 2 && (ft_strcmp(splited[i], "\"") == 0))
				quote = 0;
		}
		else if (ft_strcmp(splited[i], "\'") == 0)
			quote = 1;
		else if (ft_strcmp(splited[i], "\"") == 0)
			quote = 2;
		i++;
	}
	if (quote)
		return (1);
	return (0);
}

void	cat_quote(char **splited, int *words, t_token_list **head)
{
	t_token_list	*tmp;
	char			quote;

	tmp = malloc(sizeof(t_token_list));
	tmp->tok = NULL;
	quote = splited[*words][0];
	(*words)--;
	while (*words >= 0 && splited[*words][0] != quote)
	{
		strjoin_free(&(tmp->tok), splited[*words]);
		(*words)--;
	}
	if (tmp->tok != NULL)
		tmp->len = ft_strlen(tmp->tok);
	if (quote == '\"')
		tmp->type = DOUBLE_QUOTES;
	else
		tmp->type = SINGLE_QUOTES;
	if (tmp->tok == NULL)
		strjoin_free(&(tmp->tok), "\0");
	tmp->next = *head;
	*head = tmp;
	(*words)--;
}

void	temp_assign(t_token_list **tmp, t_token_list **head, \
char **splited, int *words)
{
	*tmp = malloc(sizeof(t_token_list));
	(*tmp)->tok = ft_strdup(splited[*words]);
	(*tmp)->len = ft_strlen(splited[*words]);
	(*tmp)->type = -1;
	(*tmp)->next = *head;
	*head = *tmp;
	(*words)--;
}

int	ft_init_list(t_token_list **head, char *input, char **splited)
{
	int				words;
	t_token_list	*temp;

	if (check_closed_brackets(splited) == 1)
	{
		throw_error("brackets not closed\n");
		return (1);
	}
	words = get_words_minishell(input);
	words -= 1;
	while (0 <= words)
	{
		if (splited[words][0] == '\"' || splited[words][0] == '\'')
		{
			cat_quote(splited, &words, head);
			continue ;
		}
		temp_assign(&temp, head, splited, &words);
	}
	return (0);
}

int	put_skip(t_token_list **tmp)
{
	if ((*tmp)->type != -1)
	{
		*tmp = (*tmp)->next;
		return (1);
	}
	return (0);
}

void	put_type_tok(t_token_list **head)
{
	t_token_list	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		if (put_skip(&tmp))
			continue ;
		if (tmp->tok[0] == '|' && !(tmp->tok[1]))
			tmp->type = PIPE;
		else if (tmp->tok[0] == '>' && tmp->tok[1] \
		&& tmp->tok[1] == '>' && !(tmp->tok[2]))
			tmp->type = APPEND;
		else if (tmp->tok[0] == '<' && tmp->tok[1] \
		&& tmp->tok[1] == '<' && !(tmp->tok[2]))
			tmp->type = HEREDOCK;
		else if (tmp->tok[0] == '>' && !(tmp->tok[1]))
			tmp->type = GREATER_THAN;
		else if (tmp->tok[0] == '<' && !(tmp->tok[1]))
			tmp->type = LESS_THAN;
		else if (tmp->tok[0] != ' ')
			tmp->type = WORD;
		else
			tmp->type = SPACE;
		tmp = tmp->next;
	}
}

void	ft_lexer(void)
{
	put_type_tok(&(g_shell_h->head));
	split_words(&(g_shell_h->head));
}

void	main_allocate(char *readed)
{
	// t_token_list	*list;
	char **splited;

	splited = ft_split_minishell(readed);
	if (ft_init_list(&(g_shell_h->head), readed, splited) == 1)
	{
		free_readed_and_splited(readed, splited);
		return ;
	}
	ft_lexer();
	expander();
	while(g_shell_h->head != NULL)
	{
		printf("string - [%s] and type = [%d]\n", g_shell_h->head->tok, g_shell_h->head->type);
		g_shell_h->head = g_shell_h->head->next;
	}
}
