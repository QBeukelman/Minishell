/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_open.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:04:57 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/13 15:38:53 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	safe_open(char *path, t_redirect_type oflag, int mode)
{
	int		fd;

	if (mode == 0)
		mode = 0644;
	fd = STDIN_FILENO;
	fd = open(path, oflag, mode);
	if (access(path, R_OK) == -1)
	{
		show_error_message(E_DENY, C_RED, path, X_FAILURE);
		exit(g_exit_code);
	}
	else if (fd == -1)
		show_error_message(E_OPENING_FILE, C_RED, path, X_FAILURE);
	return (fd);
}

t_in_files	*open_in_files(t_cmd *cmd, t_in_files *ins, t_redirect_type type, \
	int *stat_loc)
{
	int			i;
	t_redirect	*in;

	i = 0;
	in = cmd->fd_in;
	while (in)
	{
		if (in->type == type && type == IN_APPEND)
		{
			ins->heredocs[i] = setup_heredoc(in, stat_loc);
			i++;
		}
		if (in->type == type && type == IN)
		{
			ins->infiles[i] = safe_open(in->value, get_open_flag(IN), 0);
			i++;
		}
		if (in->next == NULL)
			break ;
		in = in->next;
	}
	return (ins);
}
