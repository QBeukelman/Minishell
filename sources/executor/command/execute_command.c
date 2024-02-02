/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbeukelm <qbeukelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:28:14 by qbeukelm          #+#    #+#             */
/*   Updated: 2024/02/02 19:23:06 by qbeukelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Get path

// Handle environment

// Make a process for command

#include "../../../includes/minishell.h"

void print_2d_char(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

char	**format_cmd(t_ast_node *ast_c)
{
	int			i;
	char		**cmd_and_args;
	
	i = 0;
	cmd_and_args = malloc(sizeof(char *) * ast_c->num_children + 1); //TODO protect
	if (ast_c->type == COMMAND)
		cmd_and_args[0] = ast_c->value;
	while (i < ast_c->num_children)
	{
		cmd_and_args[i + 1] = ft_strdup(ast_c->children[i]->value); //TODO protect
		i++;
	}
	cmd_and_args[i + 1] = 0;
	return (cmd_and_args);
}

bool	manage_execution(char *cmd_path, t_ast_node *ast_c, t_shell *shell)
{
	int		result;
	char	**cmd_and_args;
	
	cmd_and_args = format_cmd(ast_c);
	result = execve(cmd_path, cmd_and_args, shell->envp);
}

char	*get_path_for_cmd(char **env_paths, char *command)
{
	char	*temp_path;
	char	*command_path;
	int	i;

	i = 0;
	while (env_paths[i])
	{
		temp_path = ft_strjoin(env_paths[i], "/");
		command_path = ft_strjoin(temp_path, command);
		if (access(command_path, 0) == 0)
			return (command_path);
		i++;
	}
	return (NULL);
}

static char	**get_paths(void)
{
	char	*env_path;
	char	**env_paths;
	
	env_path = getenv("PATH");
	if (!env_path)
	{
		//TODO error message ->example cmd not found
	}
	env_paths = ft_split(env_path, ':');
	if (!env_paths)
	{
		//TODO protect
	}
	return (env_paths);
}

void	execute_command(t_shell *shell, t_ast_node *current)
{
	char 	**env_paths;
	char	*cmd_path;
	
	printf("\n\n========execute========\n");

	env_paths = get_paths();
	cmd_path = get_path_for_cmd(env_paths, current->value);
	manage_execution(cmd_path, shell->ast, shell);
}
