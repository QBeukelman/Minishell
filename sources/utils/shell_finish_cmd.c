/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_finish_cmd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/01 16:00:19 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/06/01 16:13:49 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_cmd_fd(t_redirect *head)
{
	t_redirect	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		printf("freeing redirect fd at: %p\n", temp); // TODO delete later
		free(temp);
	}
}

static void	free_args_format(t_cmd *cmd, int i)
{
	i = 0;
	while (i <= cmd->arg_count)
	{
		if (cmd->cmd_and_args[i])
		{
			free(cmd->cmd_and_args[i]);
			cmd->cmd_and_args[i] = NULL;
		}
		i++;
	}
	free(cmd->cmd_and_args);
	cmd->cmd_and_args = NULL;
}

//!			cat tasks.md > grep "a"
//!			'EOF' / "..."
static void	free_args_format_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (i < cmd->arg_count)
		{
			if (cmd->args[i])
			{
				free(cmd->args[i]);
				cmd->args[i] = NULL;
			}
			i++;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->cmd_and_args)
		free_args_format(cmd, i);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_args_format_cmd(cmd);
	if (cmd->fd_in)
		free_cmd_fd(cmd->fd_in);
	if (cmd->fd_out)
		free_cmd_fd(cmd->fd_out);
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	free(cmd);
}
