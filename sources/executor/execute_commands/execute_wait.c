/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_wait.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/22 21:17:34 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/04/22 21:24:22 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_signal(int signal)
{
	if (signal > 0 && signal < 32)
		ft_putstr_fd("Handle error", STDOUT_FILENO); // TODO handle signals
	return (signal + 128);
}

int	wait_for_last_cmd(int child_count, int last_pid)
{
	int	i;
	int	status;
	int	last_status;
	int	waitpid_ret;

	i = 0;
	while (i < child_count)
	{
		waitpid_ret = waitpid(-1, &status, 0);
		if (waitpid_ret < 0)
			show_error_message(E_WAITPID, C_RED, "", X_WAITPID);
		if (waitpid_ret == last_pid)
			last_status = status;
		if (WIFEXITED(status) || WIFSIGNALED(status))
			i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (handle_signal(WTERMSIG(last_status)));
	return (-1);
}