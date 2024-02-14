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
	int				type;
	char			**word;
	int				*content; //0 = |, 1 = > --->(se .next = > ----> 2 = ">>"), 3 = < (--->(se .next = < ----> 4 = "<<")), 5 = " ", 6 = ' ';
	struct s_toks	*prev;
	struct s_toks	*next;
}	t_toks;

typedef struct	s_mini
{
	char	**env; // allocata
	char	*input;
	char	*c_input; //allocata
	// int				n_cmd; // numero del comando
}	t_mini;

// MINI FUNCTIONS
void	put_env(t_mini *mini,char **env);

// LEXER FUNCTIONS
char	*lexer(t_mini *mini, t_toks *toks);
void	clean_input_len(t_mini *mini);
void	splitter(t_mini *mini, t_toks *toks);
void	tokenizer(t_mini *mini, t_toks *toks);

// PARSER FUNCTIONS


// EXECUTOR FUNCTIONS


// BUILTINS FUNCTIONS

// UTILS FUNCTIONS
char	**mini_split(char const *s, char c);
void	ft_print_matrix(char **matrix); // TESTING (DA CANCELLARE)

# endif