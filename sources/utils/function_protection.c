/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_protection.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/29 13:21:05 by qbeukelm      #+#    #+#                 */
/*   Updated: 2024/04/06 15:42:03 by quentinbeuk   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error_messages.h"
#include "../../includes/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		// TODO correct exit code?
		g_exit_code = EXIT_FAILURE;
		exit_with_message(E_MALLOC, C_RED, g_exit_code);
	}
	return (ptr);
}
