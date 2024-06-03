/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_heredoc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/25 11:15:17 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/01 14:14:14 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	is_eof(char *line, char *eof)
{
	size_t	eof_len;

	eof_len = ft_strlen(eof);
	if (ft_strlen(line) != eof_len)
		return (false);
	if (ft_strncmp(line, eof, eof_len) == 0)
		return (true);
	return (false);
}

static int	perform_heredoc(int fd, t_redirect *heredoc)
{
	char	*line;

	while (1)
	{
		line = readline(C_YELLOW "> " RESET_COLOR);
		if (line == NULL)
		{
			free(line);
			exit_with_message(E_EOF_DESCRIPTOR, C_RED, g_exit_code);
		}
		if (is_eof(line, heredoc->value) == true)
		{
			if (line)
				free(line);
			return (1);
		}
		line = ft_strjoin(line, "\n");
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	setup_heredoc(t_redirect *heredoc, int *stat_loc)
{
	int		fd[2];
	pid_t	pid;
	int		stat_loc_local;

	stat_loc_local = 0;
	if (pipe(fd) < 0)
		exit_with_message(E_PIPE_FAIL, C_RED, X_FAILURE);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		exit_with_message(E_FORK, C_RED, X_FAILURE);
	if (pid == 0)
	{
		handle_signals(HEREDOC);
		if (perform_heredoc(fd[WRITE], heredoc))
			exit(0);
	}
	else if (pid > 0)
	{
		if (close_fds(fd[WRITE], -1, -1) == false)
			exit_with_message(E_CLOSE, C_RED, X_FAILURE);
		waitpid(pid, &stat_loc_local, 0);
		*stat_loc = stat_loc_local;
	}
	return (fd[READ]);
}
