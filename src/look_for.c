#include "../include/minishell.h"

bool	look_for_exit(char **s_line)
{
	if (ft_strncmp(s_line[0], "exit", 5) == 0)
	{
		return (true);
	}
	return (false);
}

bool	look_for_export(char **s_line)
{
	if (ft_strncmp(s_line[0], "export", ft_strlen("export")) == 0)
	{
		return (true);
	}
	return (false);
}

bool	look_for_unset(char **s_line)
{
	if (ft_strncmp(s_line[0], "unset", ft_strlen("unset")) == 0)
	{
		return (true);
	}
	return (false);
}

bool	look_for_cd(char **s_line)
{
	if (ft_strncmp(s_line[0], "cd", ft_strlen("cd")) == 0)
	{
		return (true);
	}
	return (false);
}

bool	look_for_echo(char **s_line)
{
	if (ft_strncmp(s_line[0], "echo", ft_strlen("echo")) == 0)
	{
		return (true);
	}
	return (false);
}
