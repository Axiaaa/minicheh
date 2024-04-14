/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geymat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:33:38 by geymat            #+#    #+#             */
/*   Updated: 2024/04/14 19:55:58 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirect_before_bi(char *line, int fd[2])
{
	int	res;

	fd[0] = dup(0);
	if (fd[0] == -1)
		return (0);
	fd[1] = dup(1);
	if (fd[1] == -1)
	{
		close(fd[0]);
		return (0);
	}
	res = redirections(line);
	if (res == -1)
		return (0);
	return (1);
}

int	restaure_redirections_bi(int fd[2])
{
	if (dup2(fd[0], 0) == -1 || dup2(fd[1], 1) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		f_exit(3);
		return (0);
	}
	close(fd[0]);
	fd[0] = -1;
	close(fd[1]);
	fd[1] = -1;
	return (1);
}

static size_t	where_command(char *line, size_t i)
{
	short	is_file;
	short	delimiter;

	is_file = 0;
	delimiter = 0;
	while (line[i] && (is_file || line[i] == ' '
			|| delimiter || line[i] == '<' || line[i] == '>'))
	{
		if ((delimiter == 1 && line[i] == '\"')
			|| (delimiter == 2 && line[i] == '\''))
			delimiter = 0;
		else if ((line[i] == '\"' || line[i] == '\'') && !delimiter)
			delimiter = 1 + (line[i] == '\'');
		else if ((line[i] == '<' || line[i] == '>') && !delimiter)
			is_file = 1;
		else if (is_file == 1 && (!ft_isalnum(line[i]) && line[i] != '_'
				&& line[i] != '/' && line[i] != '-' && line[i] != '.'
				&& line[i] != '\'' && line[i] != '\"' && line[i] != -1))
			is_file = 2;
		else if (is_file == 2 && line[i] == ' ')
			is_file = 0;
		i++;
	}
	return (i);
}

int	is_a_built_in(char *line, t_env **env)
{
	size_t	i;

	i = where_command(line, 0);
	if (!ft_strncmp(line + i, "env", 3) && (line[i + 3] == ' ' || !line[i + 3]))
		return (bi_env(line, env) || 1);
	if (!ft_strncmp(line + i, "echo", 4)
		&& (line[i + 4] == ' ' || !line[i + 4]))
		return (bi_echo(line) || 1);
	if (!ft_strncmp(line + i, "pwd", 3) && (line[i + 3] == ' ' || !line[i + 3]))
		return (bi_pwd(line) || 1);
	if (!ft_strncmp(line + i, "cd", 2) && (line[i + 2] == ' ' || !line[i + 2]))
		return (bi_cd(line, env) || 1);
	if (!ft_strncmp(line + i, "unset", 5) && (line[5] == ' ' || !line[i + 5]))
		return (bi_unset(line, env) || 1);
	if (!ft_strncmp(line + i, "export", 6)
		&& (line[i + 6] == ' ' || !line[i + 6]))
		return (bi_export(line, env) || 1);
	if (!ft_strncmp(line + i, "exit", 4)
		&& (line[4 + i] == ' ' || !line[4 + i]))
		return (bi_exit(line) || 1);
	return (0);
}
