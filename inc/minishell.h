/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:31:56 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/14 14:46:55 by nikitos          ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>

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

# define SYNTAX_ERROR "minishell: syntax error near unexpected token\n"
# define OPEN_ERROR "minishell: couldn't open such file or directory\n"

typedef struct s_token_list
{
	int					len;
	char				*tok;
	int					type;
	int					corrective_token;
	int					i;
	int					k;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}						t_token_list;

typedef struct s_pipe_group
{
	char				**argv;
	char				*cmd;
	int					fd[2];
	int					input;
	int					output;
	int					pipe_index;
	char				*heredoc;
	struct s_pipe_group	*next;
}						t_pipe_group;

typedef struct s_minishell
{
	char			**envp;
	int				error;
	int				current_env;
	int				last;
	t_pipe_group	*pipes;
	t_token_list	*head;
}			t_minishell;

extern t_minishell *g_shell_h;

char				*read_input(void);
char				*find_in_env(char *str);
char				**ft_split_minishell(char *input);
void				charjoinfree(char **str, char ch);

int					throw_error(char *error);
int					get_type(char symbol);
int					create_red(t_token_list **token_tmp,
					t_pipe_group **tmp);
int					add_word(t_pipe_group **tmp, t_token_list **token_tmp,
					int *first, int *count_words);
int 				add_pipe(t_pipe_group **tmp, t_token_list **token_tmp,
					int *first, int *count_words);										
int					assign_env(char **envp);
int					get_words_minishell(char *str);
int					ft_words_len(char *str);
int					ft_init_list(t_token_list **head, char *input, char **splited);
int					ft_strcmp(char *s1, char *s2);
int					put_skip(t_token_list **tmp);
int					ft_lstsize_n(t_token_list *start, t_token_list *finish);
int					here_doc(t_token_list **token_tmp, t_pipe_group **tmp);
int					open_output(t_pipe_group **tmp, t_token_list **token_tmp, int type);

int					main_allocate(char **splited, char *readed);
void				ft_lexer(void);
void				put_type_tok(t_token_list **head);
void				free_t_token(t_token_list **list);
void				split_words(t_token_list **list);
void				init_vars_env(int	*counter, char ***env, char **envp, int *i);
void				print_env(void);
void				fill_array(char **array, char *str);
void				strjoin_free(char **str, char *add);

t_pipe_group		*redirection(void);
void				ft_clear_tokens(t_token_list **tokens);
void				skip_space(t_token_list **tmp);
void				free_t_pipe(t_pipe_group **token);
void				free_t_token(t_token_list **token);
void				free_splited(char **splited);
// void				free_readed_and_splited(char **splited);
void				free_readed_and_splited(char *readed, char **splited);
void				ft_lstadd_back_minishell(t_token_list **lst, \
t_token_list *new);
void				get_final_type(t_token_list **token);
char				*quotes_allocate(char *str);
char				*here_doc_init(char **file_name, t_token_list **token_tmp,
						t_pipe_group **tmp, int *file);
void				check_quotes(t_token_list *tokens);
void				heredoc_last(t_token_list **token_tmp,
				t_pipe_group **tmp, char **file_name, char **buf);



void				pipe_grp_mmry(t_pipe_group **pipe_grp, t_token_list *start, t_token_list *finish);
void				parse(t_token_list *list);

void				lexer(char *input);

t_pipe_group		*create_pipe_group(t_token_list *start, t_token_list *finish);
t_pipe_group		*init_pipe(int index);
t_pipe_group		*init_pipe(int index);
t_token_list		*new_token_and_type(int *i, char *str);

void	expander(void);
char	*resolve_dollar(char *inp);
int		define_malloc(int *i, int *j, char *inp);
char	*get_var_name(char *inp);
void    signals(void);
void 	sig_handler(int sig);
#endif