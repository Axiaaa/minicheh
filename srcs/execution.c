/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:22:00 by geymat            #+#    #+#             */
/*   Updated: 2024/04/15 18:00:53 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

static char	**split_and_parsing(char *line)
{
	char	**argv;
	size_t	i;

	i = 0;
	change_string(line, '|', -2);
	change_string(line, ' ', -1);
	argv = ft_split(line, '|');
	if (!argv)
		return (NULL);
	change_string(line, -2, '|');
	while (argv[i])
		change_string(argv[i++], -2, '|');
	return (argv);
}

int	check_pipe(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	change_string(line, '|', -2);
	if ((line[0] == ' ' && line[1] == '|') || line[0] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (1);
	}
	if (ft_strstr(line, "||") || ft_strstr(line, "| |"))
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (1);
	}
	if ((len && line[len - 1] == '|') || \
		(len > 1 && line[len - 1] == ' ' && line[len - 2] == '|'))
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (1);
	}
	change_string(line, -2, '|');
	return (0);
}

void	executions(char **line, t_env **env)
{
	char	**envp;
	char	**argv;

	if (check_pipe(*line))
		return ;
	envp = create_envp(*env);
	if (!envp)
	{
		the_return_value(1);
		return ;
	}
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
