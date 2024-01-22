# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    file.txt                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grinella <grinella@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 19:56:20 by grinella          #+#    #+#              #
#    Updated: 2024/01/22 10:00:16 by grinella          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

void	ft_ctrlc(int sign)
{
	if (sign == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_ctrld(char *line, t_mini *mini)
{
	ft_free_array(mini->env);
	if (line)
		free(line);
	exit(g_exit_status);
}

void	sig_ignore(void)
{
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}