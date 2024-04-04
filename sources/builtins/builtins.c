/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/01 14:47:56 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/04/03 22:15:00 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_single_builtin(char *cmd_value)
{
	if (cmd_value == NULL)
		return (false);
	if (ft_strncmp(cmd_value, "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd_value, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd_value, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd_value, "unset", 6) == 0)
		return (true);
	return (false);
}

// * change later with jump table
int exec_single_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->value, "exit", 5) == 0)
		g_exit_code = exit_shell(cmd, shell);
	else if (ft_strncmp(cmd->value, "cd", 3) == 0)
		g_exit_code = cd(cmd, shell);
	else if (ft_strncmp(cmd->value, "export", 7) == 0)
		g_exit_code = export(cmd, shell);
	else if (ft_strncmp(cmd->value, "unset", 6) == 0)
		g_exit_code = unset(cmd, shell);
	return (g_exit_code);
}

bool	is_builtin(char *cmd_value)
{
	int	i;

	i = 0;
	while (i < S_NUM_BUILTIN)
	{
		if (ft_strncmp(cmd_value, builtin_table[i].name, ft_strlen(builtin_table[i].name)) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	if (is_single_builtin(cmd->value))
		exit(0);
	while (i < S_NUM_BUILTIN)
	{

		if (ft_strncmp(cmd->value, builtin_table[i].name, ft_strlen(cmd->value)) == 0)
		{
			g_exit_code = builtin_table[i].function(cmd, shell);
			return (g_exit_code);
		}
		i++;
	}
	return (1);
}
