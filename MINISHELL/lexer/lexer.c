qualcosa analize_readline(input)
{
	while
	{
		ignore_spaces(input[i]); // deve ignorare spazi o tab prima del primo carattere
	}
	while(!ft_strncmp(input, "|", 1));
	{
		// se il primo carattere che becca é una pipe deve printare:
		printf("minishell: syntax error near unexpected token `|'");
		// penso andrá messo in una funzione a parte, deve vedere se ci stanno "|"
		// per poi prendere tutto quello che ha dovuto scorrere e inserirlo in una variabile w_lex come parole
		// per poi verificare se é un comando valido
	}
}

void    lexer(t_mini *input) //o t_mini o t_lexer
{
	int i;

	i = 0;
	if (!input) // se input é vuoto
	{
		printf("\n");
	}
	if (input) // se input ha qualcosa al suo interno
	{
		analize_readline();
	}
}