/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 05:14:33 by geymat            #+#    #+#             */
/*   Updated: 2024/04/15 17:22:39 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	replace_inside(char **p_s, size_t start, size_t end, char *s2)
{
	size_t	i;
	char	*res;
	char	*s1;

	s1 = *p_s;
	i = -1;
	res = f_malloc(ft_strlen(s1) + ft_strlen(s2) + start - end + 1);
	*p_s = res;
	if (!res)
	{
		f_free(s1);
		return (-1);
	}
	while (++i < start)
		res[i] = s1[i];
	i = -1;
	while (s2[++i])
		res[i + start] = s2[i];
	i = -1;
	while (++i < ft_strlen(s1) - end)
		res[i + start + ft_strlen(s2)] = s1[i + end];
	res[i + start + ft_strlen(s2)] = '\0';
	f_free(s1);
	return (0);
}

static size_t	word_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '?')
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
		++i;
	}
	return (i);
}

char	*get_value(char *str, t_env *env)
{
	if (!env)
		return (NULL);
	while (env && env->key)
	{
		if (!ft_strncmp(str, env->key, word_len(str)))
		{
			if (!env->value)
				return ("");
			return (env->value);
		}
		env = env->next;
	}
	return ("");
}

char	*replace_env(char *str, t_env *env)
{
	int		delimiter;
	size_t	i;

	delimiter = 0;
	i = 0;
	while (str && str[i])
	{
		if (delimiter == 1 && (str[i] == '\"'))
			delimiter = 0;
		else if ((delimiter == 2) && str[i] == '\'')
			delimiter = 0;
		else if ((str[i] == '\"') && !delimiter)
			delimiter = 1;
		else if ((str[i] == '\'') && !delimiter)
			delimiter = 2;
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
			|| str[i + 1] == '?') && delimiter != 2)
		{
			replace_inside(&str, i, i + word_len(str + i + 1) + 1,
				get_value(str + i + 1, env));
			i--;
		}
		i++;
	}
	return (str);
}
