/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gabriele <Gabriele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 20:04:07 by grinella          #+#    #+#             */
/*   Updated: 2024/01/29 18:10:21 by Gabriele         ###   ########.fr       */
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
 
 typedef struct s_list
{
	int				*token; // se "|" = 0, se ">" = 1, se ">>" = 2, se "<" = 3 
	int				n_cmd; // numero del comando
	char			*word;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct	s_mini
{
	char	*input;
}				t_mini;

# endif