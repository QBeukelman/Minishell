/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_finish_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 16:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/20 14:34:19 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(token);
	token = NULL;
}

void	free_tokens(t_token *token)
{
	t_token	*next;

	next = NULL;
	if (token == NULL)
		return ;
	while (token)
	{
		next = token->next;
		free_token(token);
		token = next;
	}
}

void	free_2d_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
	}
}

void	free_strs(char *str1, char *str2, char *str3)
{
	if (str1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2)
	{
		free(str2);
		str2 = NULL;
	}
	if (str3)
	{
		free(str3);
		str3 = NULL;
	}
}
