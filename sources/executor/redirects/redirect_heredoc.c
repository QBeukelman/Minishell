/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_heredoc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/25 11:15:17 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/02/25 18:35:09 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool is_eof(char *line, char *eof)
{
	int		eof_len;

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
		line = readline(CYELLOW "> " RESET_COLOR);
		if (is_eof(line, heredoc->value) == true)
		{
			if (line)
				free(line);
			exit(0);
		}
		line = ft_strjoin(line, "\n");
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

static int	setup_heredoc(t_redirect *heredoc)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);

	pid = fork();
	if (pid == -1)
	{ 
		// TODO clean_exit
	}

	if (pid == 0)
		perform_heredoc(fd[WRITE], heredoc);
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(fd[WRITE]);
	}
	return (fd[READ]);
}

int		*collect_heredocs(t_cmd *cmd)
{
	int			exit_code;
	t_redirect	*heredoc;
	int			*open_fds;
	int			i;

	i = 0;
	heredoc = cmd->heredoc;
	open_fds = malloc(sizeof(int) * count_redirects_for_type(cmd, OUT_APPEND));
	if (open_fds == NULL)
	{
		// TODO clean_exit()
	}
	while (heredoc)
	{
		open_fds[i] = STDIN_FILENO;
		open_fds[i] = setup_heredoc(heredoc);
		i++;
		heredoc = heredoc->next;
	}
	return (open_fds);
}
