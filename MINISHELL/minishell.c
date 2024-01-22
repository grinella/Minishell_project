/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:56:20 by grinella          #+#    #+#             */
/*   Updated: 2024/01/22 14:27:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

char	*ft_find_word(char *input, int i)
{
	int j;
	
	while(input[i] == ' ')
	{
		i++;
	}
	j = i;
	while(input[j] != ' ' && input[j] != '\0') //ascii
	{
		write(1, &input[j], 1);
		j++;
	}
	write(1, "\n", 1);
	printf("j: %i\n", j);
	i++;
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	int i = 0;

	(void)argv;
	if(argc == 2);
	{
	// if (argc != 1)
	// {
	// 	printf("Error: too many arguments\n");
	// 	return (1);
	// }
	//get_env(envp);
		input = ("ciao come stai\n");
		// input = readline("shell>> ");
		ft_find_word(input, i);
		// if (input && input[0])
		// {
		// 	add_history(input);
		// }
		// if (input && input[0])
		// {
		// 	if (run_lexer(input, mini) && parse_input(mini))
		// 	{
		// 		is_builtin(mini);
		// 	}
		// }
		// free_cmds(&mini, input);
	}
	return (0);
}