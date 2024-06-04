#include "../include/minishell.h"
#include <readline/history.h>
/**
 * @brief General note about signals: 
You can't have data of your own passed to the signal handler as parameters.
Instead you'll have to store your parameters in global variables.
(And be really, really careful if you ever need
to change those data after installing the the signal handler).

Signals are a really old and really low-level design.
Basically you're just given the kernel a single address to some machine
code and asking it to go to this specific address if such and such happens.
We're back in the "portable assembler" mindset here,
where the kernels provide a no-frills baseline service,
and whatever the user process can reasonably
be expected to to for itself, it must do itself.

       The sigaction() system call is used to change the action taken by
       a process on receipt of a specific signal.  (See signal(7) for an
       overview of signals.)

       signum specifies the signal and can be any valid signal except
       SIGKILL and SIGSTOP.

       If act is non-NULL, the new action for signal signum is installed
       from act.  If oldact is non-NULL, the previous action is saved in
       oldact.

       The sigaction structure is defined as something like:

           struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
 *
 */

/**
 * @brief This function handles the Ctrl-C (SIGINT) event
            Move to a new line
            This function is binded by setup_signal_handlers
            It will update ex->interrupted to 1 and print a new prompt
            ex->interrupted is verified in in process_command(main)
            and wont process the command if set to 1

// TO-DO DEBUG - Here i should probably try to just generate a new line
and call readline instead of cheating

// TO-DO Double check why mik add g_mini.code =  INTERRUPT_SIG 
 * 
 * @param sig is required by the sig action struct
 */
static void	handle_sigint(int sig)
{
	//char	*prompt;

	(void) sig;
	ex->interrupted = 1;
	write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
/*
static void	handle_sigint(int sig)
{
	char	*prompt;

	(void) sig;
	ex->interrupted = 1;
	write(1, "\n", 1);
	prompt = set_prompt(ex->new_env);
	write(1, prompt, ft_strlen(prompt));
	free(prompt);
	//rl_on_new_line();
}*/

/**
 * @brief This function handles the Ctrl-\  (sigquit) event
            it will only be called if a foreground_job is active
            This function is binded by setup_signal_handlers
 * 
 * @param sig is required by the sig action struct
 */
static	void	handle_sigquit(int sig)
{
	(void) sig;
	if (ex->foreground_job_active)
		write(1, "\nQuit signal (SIGQUIT) received by job.\n", 40);
}

/**
 * @brief Set the up signal handlers object 
            Sigaction
            (signaltype, struct sig action 
			(handle, mask, flags), pointer to another sigaction structure)
            The mask is the signals we want to block
            the flag helps to control with more details
            A signalset is a bunch of bits hidden behind macros
            Sigemptyset will initialise a signalset and will clear everything

			First we setup the sigint (mask, handler, flags)
			We setup the SA_RESTART flag for the flags so
			it auto-restart the functions if interrupted
			we finally call sigation on that SIGINT with ex->sa_int struct

			Then we setup the sigquit handler without a flag
			This function is called in setup_minishell in main
 * 
 */
void	setup_signal_handlers(void)
{
	sigemptyset(&ex->sa_int.sa_mask);
	ex->sa_int.sa_handler = handle_sigint;
	ex->sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &ex->sa_int, NULL);
	sigemptyset(&ex->sa_quit.sa_mask);
	ex->sa_quit.sa_handler = handle_sigquit;
	ex->sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &ex->sa_quit, NULL);
}

/**
 * @brief Will update the sigquit signal depending
			on the bool ex->foreground_job_active
 			Set to custom handler when a job is active
			Ignore SIGQUIT when nob job is active

			This function is called by prompt_and_read_input
			CALLED ALOT
 * 
 */
void	update_sigquit_handling(void)
{
	if (ex->foreground_job_active)
		signal(SIGQUIT, handle_sigquit);
	else
		signal(SIGQUIT, SIG_IGN);
}
