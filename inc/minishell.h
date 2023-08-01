/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:31:56 by nikitos           #+#    #+#             */
/*   Updated: 2023/08/01 14:25:54 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

# define WORD 0
# define PIPE 1 // |
# define SPACE 2 // ' '
# define GREATER_THAN 3 // >
# define LESS_THAN 4 // <
# define DOUBLE_QUOTES 5 // "
# define SINGLE_QUOTES 6 // '
# define HEREDOCK 7 // <<
# define APPEND 8 // >>
# define EXPANSION 9

typedef struct s_token_list
{
	int					len;
	char				*tok;
	int					type;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}						t_token_list;

char				*read_input();

int					get_type(char symbol);

void				lexer(char *input);//
void				ft_clear_tokens(t_token_list **tokens);
void				ft_lstadd_back_minishell(t_token_list **lst, t_token_list *new);

t_token_list		*list_without_space(char *str, int start, int end);
t_token_list		*create_token(int length, char *start, int type);
t_token_list		*ft_lstlast_minishell(t_token_list *lst);
#endif