/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 00:21:40 by geymat            #+#    #+#             */
/*   Updated: 2024/04/15 23:37:27 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	bi_exp_print(t_env **env)
{
	t_env	*lst;

	lst = *env;
	while (lst)
	{
		if ((lst->key)[0] == '?')
		{
			lst = lst->next;
			continue ;
		}
		if (lst->value)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
		else
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
	return (the_return_value(0));
}

static int	any_forbidden_chars_export(char *temp)
{
	size_t	i;

	i = 0;
	while (temp[i] != '=' && temp[i] && temp[i] != ' ')
	{
		if (!ft_isalnum(temp[i]) && temp[i] != '_' && temp[i] != ' '
			&& temp[i] != '\"' && temp[i] != '\'')
		{
			return (the_return_value(1));
		}
		i++;
	}
	return (0);
}

int	free_ret_1(char *str)
{
	if (str)
		f_free(str);
	return (1);
}

static int	export_multiple(char *line, t_env **env)
{
	char	*temp;
	int		trigger;

	trigger = 0;
	while (*line)
	{
		temp = ft_space_strtok(line);
		if (temp && (any_forbidden_chars_export(temp) || startwithnbr(temp)))
			trigger = 1;
		else
			do_export(temp, env);
		while (*line && *line != ' ')
			line++;
		while (*line == ' ')
			line++;
		f_free(temp);
	}
	if (trigger == 1)
		write(2, "minishell: export: the identifier is not valid\n", 48);
	return (trigger);
}

int	bi_export(char *line, t_env **env)
{
	int	res;
	int	fd[2];

	if (!redirect_before_bi(line, fd))
		return (the_return_value(1));
	restaure_redirections_bi(fd);
	while (*line && (*line == ' ' || *line == '\'' || *line == '\"'))
		line++;
	line += 6;
	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (bi_exp_print(env));
	res = export_multiple(line, env);
	return (the_return_value(res));
}
