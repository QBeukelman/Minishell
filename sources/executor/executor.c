/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 19:16:50 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/02/22 20:10:40 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		execute(t_shell *shell)
{
	int	exit_code;	

	exit_code = 0;
	
	printf("\n\n========execute========\n");

	if (shell->cmd_table->cmd_count == 1)
		exit_code = single_command(shell);
	else
		exit_code = execute_commands(shell);
	
	return (0);
}
