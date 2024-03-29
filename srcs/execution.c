/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:22:00 by geymat            #+#    #+#             */
/*   Updated: 2024/03/29 08:55:49 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

static void	change_string(char *str, char c1, char c2)
{
	size_t	i;
	short	delimiter;

	i = 0;
	delimiter = 0;
	while (str[i])
	{
		if (delimiter == 1 && (str[i] == '\"'))
			delimiter = 0;
		else if ((delimiter == 2) && str[i] == '\'')
			delimiter = 0;
		else if ((str[i] == '\"') && !delimiter)
			delimiter = 1;
		else if ((str[i] == '\'') && !delimiter)
			delimiter = 2;
		else if (delimiter && str[i] == c1)
			str[i] = c2;
		i++;
	}
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

static char	**split_and_parsing(char *line)
{
	char	**argv;

	change_string(line, '|', -2);
	change_string(line, ' ', -1);
	argv = ft_split(line, '|');
	if (!argv)
		return (NULL);
	change_string(line, -2, '|');
	return (argv);
}

void	executions(char **line, t_env **env)
{
	char	**envp;
	char	**argv;

	envp = create_envp(*env);
	if (!envp)
	{
		the_return_value(1);
		return ;
	}
	replace_all_here_docs(line, *env);
	argv = split_and_parsing(*line);
	if (!argv)
	{
		ft_strsfree(envp);
		the_return_value(1);
		return ;
	}
	if (argv[0] && (argv[1] || !(is_a_built_in(*line, env))))
		the_return_value(almost_pipex(argv, envp, (void *) env));
	ft_strsfree(envp);
	ft_strsfree(argv);
}
