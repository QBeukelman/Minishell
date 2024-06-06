/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/16 11:15:41 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/06 20:07:59 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * get key and value van env dubbel array
// * if null -> do nothing
// * combine 

static bool expand_double_q(char **env, char *arg, size_t *i, t_vec *exp_str)
{
	(*i)++;
	while (arg[*i] != D_QUOTE_CHAR)
	{
		if (arg[*i] == EXPAND_CHAR)
		{
			if (expand_env(env, arg, i, exp_str) == false)
				return (false);
		}
		else
		{
			if (vec_push(exp_str, arg[*i]) == false)
				return (show_error_message(E_MALLOC, C_RED, "", X_FAILURE), false);
			(*i)++;
		}
		(*i)++;
	}
	(*i)++;
	return (true);
}

static bool	expand_single_q(char *arg, size_t *i, t_vec *exp_str)
{
	(*i)++;
	while (arg[*i] != S_QUOTE_CHAR)
	{
		if (vec_push(exp_str, arg[*i]) == false)
			return (false);
		(*i)++;
	}
	(*i)++;
	return (true);
}

static bool	expand_type(char **env, char *arg, size_t *i, t_vec *exp_str)
{
	if (arg[*i] == S_QUOTE_CHAR)
	{
		if (expand_single_q(arg, i, exp_str) == false)
			return (false);
	}
	else if (arg[*i] == D_QUOTE_CHAR)
	{
		if (expand_double_q(env, arg, i, exp_str) == false)
			return (false);
	}
	else if (arg[*i] == EXPAND_CHAR)
	{
		if (expand_env(env, arg, i, exp_str) == false)
			return (false);
	}	
	return (true);
}

static char	*expander(char **env, char *arg)
{
	t_vec	expanded_string;
	size_t	i;

	(void)env;
	if (vec_init(&expanded_string, 200) == false)
		return (show_error_message(E_MALLOC, C_RED, "", X_FAILURE), NULL);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPAND_CHAR || arg[i] == S_QUOTE_CHAR
		|| arg[i] == D_QUOTE_CHAR)
		{
			if (expand_type(env, arg, &i, &expanded_string) == false)
				return (arg);
			break ;
		}
		else
		{
			if (vec_push(&expanded_string, arg[i]) == false)
				return (arg);
			i++;
		}
	}
	return (get_str(&expanded_string));
}

char	*will_expand(char **env, char *arg)
{
	int	i;
	char *expanded_str;

	expanded_str = NULL;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == EXPAND_CHAR || arg[i] == S_QUOTE_CHAR
			|| arg[i] == D_QUOTE_CHAR)
		{
			expanded_str = expander(env, arg);
			if (expanded_str)
			{
				free(arg);
				arg = expanded_str;
			}
			break ;
		}
		i++;
	}
	return (arg);
}

// t_env_utils	*init_env_utils(char **env, char *arg, size_t i)
// {
// 	t_env_utils		*env_utils;

// 	env_utils = safe_malloc(sizeof(t_env_utils));
// 	env_utils->key = get_env_key(arg, i);
// 	// ft_sleep(5000);
// 	env_utils->value = get_value_for_key(env, env_utils->key);
// 	return (env_utils);
// }

// static char	*expand_arg(char **env, char *arg, size_t i)
// {
// 	t_env_utils		*env_utils;

// 	if (ft_strlen(arg) == 1)
// 		return (arg);
// 	env_utils = NULL;
// 	env_utils = init_env_utils(env, arg, i);
// 	if (env_utils->key[0] == '?')
// 	{
// 		arg = expand_exit_code(arg, env_utils->key, env_utils->value, i, env_utils);
// 		return (arg);
// 	}
// 	if (env_utils->key[0] != EXPAND_CHAR)
// 		env_utils->key = ft_strjoin("$", env_utils->key);
// 	if (arg && env_utils->value && is_arg_key(arg, env_utils->key))
// 	{
// 		arg = safe_strdup(env_utils->value);
// 		free_env_values(env_utils->key, env_utils->value, env_utils);
// 		return (arg);
// 	}
// 	arg = ft_str_remove(arg, env_utils->key);
// 	if (arg && env_utils->value)
// 		arg = ft_str_insert(arg, env_utils->value, i);
// 	free_env_values(env_utils->key, env_utils->value, env_utils);
// 	return (arg);
// }

// char	*will_expand(char **env, char *arg)
// {
// 	size_t	i;
// 	int		expand_count;
// 	int		expanded_count;

// 	expanded_count = 0;
// 	expand_count = count_expand(arg);
// 	if (expand_count == 0)
// 		return (arg);
// 	i = 0;
// 	while (arg[i])
// 	{
// 		if (expanded_count == expand_count)
// 			break ;
// 		if (arg[i] == EXPAND_CHAR)
// 		{
// 			arg = expand_arg(env, arg, i);
// 			expanded_count++;
// 			i = 0;
// 			continue ;
// 		}
// 		i++;
// 	}
// 	return (arg);
// }
