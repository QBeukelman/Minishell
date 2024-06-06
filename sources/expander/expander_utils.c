/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: quentinbeukelman <quentinbeukelman@stud      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 21:54:16 by quentinbeuk   #+#    #+#                 */
/*   Updated: 2024/06/06 20:15:38 by qtrinh        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	expand_exit_code(size_t *i, t_vec *exp_str)
{
	char	*exit_code_string;
	size_t	j;

	j = 0;
	(*i)++;
	exit_code_string = ft_itoa(g_exit_code);
	if (exit_code_string == NULL)
		return (show_error_message(E_MALLOC, C_RED, "exp_exit_code", X_FAILURE));
	while (exit_code_string[j])
	{
		vec_push(exp_str, exit_code_string[j]);
		j++;
	}
	free(exit_code_string);
	return (true);
}

bool	expand_env(char **env, char *arg, size_t *i, t_vec *exp_str)
{
	char	*key;
	char	*env_value;
	size_t	j;

	// (*i)++;
	j = 0;
	if (arg[*i] == '?')
		return (expand_exit_code(i, exp_str));
	if (arg[*i] == '\0' || arg[*i] == S_QUOTE_CHAR || arg[*i] == D_QUOTE_CHAR)
		return (vec_push(exp_str, EXPAND_CHAR));
	key = get_env_key(arg, *i);
	if (key == NULL)
		return (false);
	env_value = get_value_for_key(env, key);
	if (env_value == NULL)
		return (free(key), false);
	free(key);
	while (env_value[j])
	{
		if (vec_push(exp_str, env_value[j]) == false)
			return (show_error_message(E_MALLOC, C_RED, "exp_env", X_FAILURE));
		j++;
	}
	free(env_value);
	return (true);	
}

// void free_env_values(char *key, char *value, t_env_utils *env_utils)
// {
// 	if (key)
// 	{
// 		free (key);
// 		key = NULL;
// 	}
// 	if (value)
// 	{
// 		free (value);
// 		value = NULL;
// 	}
// 	if (env_utils)
// 	{
// 		free (env_utils);
// 		env_utils = NULL;
// 	}
// }

// int	count_expand(char *arg)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == EXPAND_CHAR)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// bool is_arg_key(char *arg, char *key)
// {
// 	if (ft_strncmp(arg, key, (ft_strlen(key) + ft_strlen(arg)))  == 0)
// 		return (true);
// 	return (false);
// }

// char *expand_exit_code(char *arg, char *key, char *val, \
// 	size_t i, t_env_utils *env_utils)
// {
// 	char	*exit_code_string;

// 	key = safe_strjoin("$", key);
// 	arg = ft_str_remove(arg, key); // ! key/arg = NULL
// 	exit_code_string = ft_itoa(g_exit_code);
// 	arg = ft_str_insert(arg, exit_code_string, i);
// 	// free (exit_code_string);
// 	free_env_values(key, val, env_utils);
// 	return (arg);
// }

