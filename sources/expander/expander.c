/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/20 15:41:40 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft/lib_vector/vector.h"

//TODO echo $USER$PATH (1 string)
//TODO echo echo '$USER'$HOME (sees quote as 1 str)
static char	*expand_arg(char **env, char *arg, size_t i)
{
	t_vec	vec_val;
	char	*key;
	char	*val;

	key = NULL;
	val = NULL;
	if (ft_vec_init(&vec_val, ft_strlen(arg)) == false)
		return (NULL);
	if (ft_strlen(arg) == 1)
		return (ft_vec_push(&vec_val, arg[0]), ft_vec_to_str(&vec_val));
	arg = skip_multiple_expand_chars(arg, i + 1);

	key = get_env_key(arg, i);
	val = get_value_for_key(env, key);
	if (key[0] == '?')
		return (expand_exit_code(arg, i, &vec_val));
	if (val == NULL)
	{
		ft_vec_push_str(&vec_val, NULL);
		return (free_strs(key, val, arg), ft_vec_to_str(&vec_val));
	}
	else
		ft_vec_push_str(&vec_val, val);
	return (free_strs(key, val, arg), ft_vec_to_str(&vec_val));
}

char	*will_expand(char **env, char *arg)
{
	size_t	i;
	int		expand_count;
	int		expanded_count;

	expanded_count = 0;
	expand_count = count_expand(arg);
	if (expand_count == 0)
		return (arg);
	i = 0;
	while (arg[i])
	{
		if (expanded_count == expand_count)
			break ;
		if (arg[i] == EXPAND_CHAR)
		{
			arg = expand_arg(env, arg, i);
			expanded_count++;
			i = 0;
			continue ;
		}
		i++;
	}
	return (arg);
}
