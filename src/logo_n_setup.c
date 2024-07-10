#include "../include/minishell.h"

/**
 * @brief Fun function to print our logo
			Thanks to jvigneau <jvigneau@student.42quebec>
			Second MVP is the escape character \
 * 
 * @param env to use execve and clear 
 */
void	print_logo(char **env)
{
	char	*lol[15];
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		lol[0] = "/usr/bin/clear";
		lol[1] = NULL;
		execve(lol[0], lol, env);
	}
	wait(NULL);
	printf(RED"\n __________________________\
________________________________________\n");
	printf("|    ____                  __   \
          __  ____ ___________     |\n");
	printf("|   / __ \\__  ______  ____/ /__\
  _____   /  |/  (_) __/ __/ (_)___ |\n");
	printf("|  / / / / / / / __ \\/ __  / _ \
\\/ ___/  / /|_/ / / /_/ /_/ / / __ \\|\n");
	printf("| / /_/ / /_/ / / / / /_/ /  __/\
 /     / /  / / / __/ __/ / / / / /|\n");
	printf("|/_____/\\____/_/ /_/\\__,_/\\__\
_/_/   __/_/  /_/_/_/ /_/ /_/_/_/ /_/ |\n");
	printf(BLU"|        / /_  __  __   _____\
____ _/ /_  ________                  |\n");
	printf("|       / __ \\/ / / /  / ___/ _\
_ `/ __ \\/ ___/ _ \\                 |\n");
	printf("|      / /_/ / /_/ /  (__  ) /_/\
 / /_/ / /  /  __/                 |\n");
	printf("|     /_.___/\\__, /  /____/\\__\
,_/_.___/_/   \\___/                  |\n");
	printf("|          /____/               \
                                   |\n");
	printf("|_______________________________\
___________________________________|\n\n\n"RESET);
}

/**
 * @brief Get the current terminal attributes
			Clear the ECHOCTL flag to stop echoing Ctrl characters
			Apply the modified settings
 */
void	configure_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * @brief First function called by main
 			Configure the terminal settings to suppress ^C
			Allocate the main execution struct called T_EXEC
			Setup variables and validate if the user uses args
			Print logo , get the env and setup signal handling
 * 
 * @param argc passed by the main function
 * @param env passed by the main function
 * @return 1 if an error occured or 0 if everything went fine
 */
int	setup_minishell(int argc, char **env)
{
	if (argc > 1)
	{
		fprintf(stderr, "Why U put params?!?!\n");
		return (1);
	}
	configure_terminal();
	g_ex = ft_calloc(1, sizeof(t_exec));
	if (g_ex == NULL)
		exit(1);
	g_ex->status = 0;
	g_ex->foreground_job_active = 0;
	g_ex->line = NULL;
	g_ex->prompt = NULL;
	print_logo(env);
	g_ex->new_env = copy_env(env);
	setup_signal_handlers();
	return (0);
}
