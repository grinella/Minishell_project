/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eugenio <eugenio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:04:07 by grinella          #+#    #+#             */
/*   Updated: 2024/01/28 18:43:34 by eugenio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
 
typedef struct s_toks
{
	int				*token; // se "|" = 0, se ">" = 1, se ">>" = 2, se "<" = 3 
	char			*word;
	struct s_list	*prev;
	struct s_list	*next;
}				t_toks;

typedef struct	s_mini
{
	char	*input;
}				t_mini;

//minishell

//lexer
void	lexer(t_mini *mini);
//parser

//executor

# endif