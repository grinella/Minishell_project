#ifndef MINISHELL_H
# define MINISHELL_H

extern int	g_exit_status;

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
	int				type; //0 = cmd; 1 = | ; 2 = > ; 3 = >> ; 4 = < ; 5 = << .
	char			**word;
	struct s_toks	*prev;
	struct s_toks	*next;
	// int 			id; // 
}	t_toks; // serve un current??

typedef struct s_mini
{
	char	**env; // allocata
	char	*input;
	char	*c_input; //allocata
	char 	*str_exit_status; //allocata
	int		std_out;
	int		std_in;
}	t_mini;

// MINI FUNCTIONS
void	put_env(t_mini *mini, char **env);

// LEXER FUNCTIONS
char	*lexer(t_mini *mini, t_toks *toks);
void	clean_input_len(t_mini *mini);
void	splitter(t_mini *mini, t_toks *toks);
void	space_len(int *i, int *j, int *flag, char* input);
void	quotes_len(int *i, int *j, t_mini *mini);//char* input)
void	find_dollar_env_len(int *i, int *j, t_mini *mini);
void	alloc_spaces(int *i, int *j, t_mini *mini);
void	alloc_double_quotes(int *i, int *j, t_mini *mini);
void	alloc_single_quotes(int *i, int *j, t_mini *mini);
void	alloc_dollar_env(int *i, int *j, t_mini *mini);

// PARSER FUNCTIONS
void	append_node(char **tokens, t_toks **toks, int type, int *i);

// EXECUTOR FUNCTIONS
void	executor(t_mini *mini, t_toks *toks);
void	execute_commands(t_mini *mini, char **cmd);
void	redir_out(char	**word);
void	append_out(char	**word);

// BUILTINS FUNCTIONS
void	is_builtin(t_toks *toks);//(t_mini *mini, t_toks *toks);
void	my_exit(t_toks *toks);

// SIGNALS FUNCTIONS
void	ft_ctrlc(int sign);
void	ft_ctrld(t_mini *mini);

// UTILS FUNCTIONS
char	**mini_split(t_mini *mini, char c);
void	ft_print_node(t_toks *toks); // TESTING (DA CANCELLARE)
void	ft_print_matrix(char **matrix); // TESTING (DA CANCELLARE)

// FREE FUNCTIONS
void	free_matrix(char **matrix);

#endif