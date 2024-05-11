#include "../include/minishell.h"

// This function handles the Ctrl-C (SIGINT) event
// Move to a new line
// TO-DO DEBUG - HEre i should probably try to just generate a new line and call readline instead of cheating
void	handle_sigint(int sig)
{
	(void)sig;
    char *prompt;
    ex->interrupted = 1;
    write (1, "\n", 1);
    //prompt_and_read_input();
	prompt = set_prompt(ex->new_env);
	write(1, prompt, ft_strlen(prompt));
	free(prompt);
}

// This function handles the Ctrl-\  event
// Move to a new line
void handle_sigquit(int sig)
 {
    (void)sig;
	if (ex->foreground_job_active)
		write(1, "\nQuit signal (SIGQUIT) received by job.\n", 40);
}

/**
 * @brief Set the up signal handlers object 
            Sigaction
            (signaltype, struct sig action (handle, mask, flags), pointer to another sigaction structure)
            The mask is the signals we want to block
            the flag helps to control with more details

            A signalset is a bunch of bits hidden behind macros
            Sigemptyset will initialise a signalset and will clear everything
 * 
 */
void setup_signal_handlers()
{
    // Setup for SIGINT
	sigemptyset(&ex->sa_int.sa_mask);
	ex->sa_int.sa_handler = handle_sigint;
	ex->sa_int.sa_flags = SA_RESTART; // Auto-restart functions if interrupted
	sigaction(SIGINT, &ex->sa_int, NULL);

   // SIGQUIT handler setup
    sigemptyset(&ex->sa_quit.sa_mask);
    ex->sa_quit.sa_handler = handle_sigquit; 
    ex->sa_quit.sa_flags = 0;  // No flags
    sigaction(SIGQUIT, &ex->sa_quit, NULL);
}

void update_sigquit_handling()
 {
    if (ex->foreground_job_active)
	{
        // Set to custom handler when a job is active
        signal(SIGQUIT, handle_sigquit);
    } else {
        // Ignore SIGQUIT when no job is active
        signal(SIGQUIT, SIG_IGN);
    }
}
