/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:38:59 by grinella          #+#    #+#             */
/*   Updated: 2024/03/29 13:59:05 by grinella         ###   ########.fr       */
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

extern int	g_exit_status;

typedef struct s_toks
{
	int				type; //0 = cmd; 1 = | ; 2 = > ; 3 = >> ; 4 = < ; 5 = << .
	char			**word;
	int				cmd_pos;
	struct s_toks	*prev;
	struct s_toks	*next;
}	t_toks; // serve un current??

typedef struct s_mini
{
	char	**env; // allocata
	char	*input;
	char	*c_input; //allocata
	char	*str_exit_status; //allocata, stringa exit status in routine
	int		tmp_out;
	int		tmp_in;
	int		cmd_count;
	int		here_doc_flag;
}	t_mini;

// MINI FUNCTIONS
void	put_env(t_mini *mini, char **env);
int		ft_count_matrix(char **matrix);

// LEXER FUNCTIONS
char	*lexer(t_mini *mini, t_toks *toks);
void	clean_input_len(t_mini *mini);
void	splitter(t_mini *mini, t_toks *toks);
void	space_len(int *i, int *j, int *flag, char *input);
void	quotes_len(int *i, int *j, t_mini *mini);// char* input)
void	find_dollar_env_len(int *i, int *j, t_mini *mini, int len);
void	alloc_spaces(int *i, int *j, t_mini *mini);
void	alloc_double_quotes(int *i, int *j, t_mini *mini);
void	alloc_single_quotes(int *i, int *j, t_mini *mini);
void	alloc_dollar_env(int *i, int *j, int len, t_mini *mini);

void	mini_fill_str(char **str, t_mini *mini, char c);
int		m_len_q(char const *s, int i, char c);
int		mini_len_word(char const *s, int i, char c);
int		is_pipe_redir(char const *s, int i);
int		mini_count_words(t_mini *mini, char c, int i, int count);

// PARSER FUNCTIONS
void	append_node(char **tokens, t_toks **toks, int type, int *i);
t_toks	*find_last_node(t_toks *head);
void	fill_node(char **tokens, t_toks *node, int *i);
void	fill_complex_node(char **tokens, t_toks **toks, t_toks *node, int *i);

// EXECUTOR FUNCTIONS
void	executor(t_mini *mini, t_toks *toks);
void	execute_commands(t_mini *mini, char **cmd);
void	redir_out(char	**word, int type, t_mini *mini);
void	redir_in(char **word, t_mini *mini);
void	here_doc(char **word, t_mini *mini);
void	reset_redir(int fdin, int fdout);
void	create_pipes(t_mini *mini);

// BUILTINS FUNCTIONS
int		is_builtin(t_mini *mini, t_toks *toks);
void	my_env(t_mini *mini, t_toks *toks);
void	my_exit(t_toks *toks);
void	my_echo(t_toks *toks, int n);
void	my_cd(t_mini *mini, t_toks *toks);
void	my_pwd(t_mini *mini);
void	my_export(t_mini *mini, t_toks *toks, int i);
void	my_unset(t_mini *mini, t_toks *toks);

// BUILTINS UTILS FUNCTIONS
char	*get_env(char *search, t_mini *mini);
char	**ft_realloc(char **mtr_old, char *str, int size);
int		ft_search_char(char *str, char c);
char	*ft_substrchr(const char *s, char c, int pre_or_post);
void	ft_print_env_export(t_mini *mini);
int		ft_check_export(char *str);

// SIGNALS FUNCTIONS
void	ft_ctrlc(int sign);
void	ft_ctrld(t_mini *mini);

// UTILS FUNCTIONS
char	**mini_split(t_mini *mini, char c);
void	ft_print_node(t_toks *toks); // TESTING (DA CANCELLARE)
void	ft_print_matrix(char **matrix); // TESTING (DA CANCELLARE)

// FREE FUNCTIONS
void	free_matrix(char **matrix);
void	free_node(t_toks *toks);
void	mini_free(char **str, int i);
void	free_all(t_mini *mini);

// void	exit_free(t_mini *mini, char **mtr);

#endif