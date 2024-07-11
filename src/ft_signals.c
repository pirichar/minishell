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

// TO-DO Double check why mik add g_mini.code =  INTERRUPT_SIG 
 * 
 * @param sig is required by the sig action struct
 */
void	handle_sigint(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief 
 * 
 */
void	setup_signal_handlers(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
