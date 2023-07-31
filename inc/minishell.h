/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:31:56 by nikitos           #+#    #+#             */
/*   Updated: 2023/07/31 16:15:16 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

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
# define MINI_FILE 10



#endif