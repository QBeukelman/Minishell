/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_post_process.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 10:13:21 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/06 16:48:03 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*process_args(char **env, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->arg_count)
	{
		cmd->args[i] = will_expand(env, cmd->args[i]);
		// if (contains_quote(cmd->args[i]) == S_QUOTE_CHAR)
		// 	cmd->args[i] = strip_quote_for_type(cmd->args[i]);
		// else if (contains_quote(cmd->args[i]) == D_QUOTE_CHAR)
		// {
		// 	cmd->args[i] = will_expand(env, cmd->args[i]);
		// 	cmd->args[i] = strip_quote_for_type(cmd->args[i]);
		// }
		// else
		// 	cmd->args[i] = will_expand(env, cmd->args[i]);
		i++;
	}
	return (cmd);
}

//!					'EOF' / "..."
static t_cmd	*process_cmd(char **env, t_cmd *cmd)
{
	
	if (cmd->value == NULL)
		return (cmd);
	cmd->value = will_expand(env, cmd->value);
	// if (contains_quote(cmd->value) == S_QUOTE_CHAR 
	// 	|| contains_quote(cmd->value) == D_QUOTE_CHAR)
	// {
	// 	expanded_value = will_expand(env, cmd->value);
	// 	stripped_value = strip_quote_for_type((cmd->value));
	// 	if (stripped_value != NULL)
	// 	{
	// 		cmd->value = stripped_value;
	// 	}
	// 	printf("after strip: %p\n", cmd->value);
	// }
	// else if ()
	// {
	// 	cmd->value = will_expand(env, cmd->value);
	// 	cmd->value = strip_quote_for_type(cmd->value);
	// }
	return (cmd);
}

int		parser_post_process(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_table->cmd_count)
	{
		shell->cmd_table->cmds[i] = process_cmd(shell->envp, shell->cmd_table->cmds[i]);
		shell->cmd_table->cmds[i] = process_args(shell->envp, shell->cmd_table->cmds[i]);
		i++;
	}
	return (0);
}

// c""a""''t README.md