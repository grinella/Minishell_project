/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:04:07 by grinella          #+#    #+#             */
/*   Updated: 2024/01/31 16:06:20 by Gabriele         ###   ########.fr       */
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
	// int				n_cmd; // numero del comando
	char			*word;
	struct s_toks	*prev;
	struct s_toks	*next;
}	t_toks;

typedef struct	s_mini
{
	char	**env; // allocata
	char	*input;
}	t_mini;

// LEXER FUNCTIONS
char	*lexer(t_mini *mini);
char	*clean_input(char *input, int i);

// PARSER FUNCTIONS


// EXECUTOR FUNCTIONS


// BUILTINS FUNCTIONS


# endif