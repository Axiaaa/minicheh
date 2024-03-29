/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 03:11:22 by geymat            #+#    #+#             */
/*   Updated: 2024/03/29 08:29:59 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../libft/libft.h"

static int	check_if_the_first_arg_is_only_spaces(char *line)
{
	int	res;

	res = 0;
	while (*line)
	{
		if (line[0] == -1 || line[0] == '\'' || line[0] == '\"')
		{
			res = 1;
			if (line[1] && line[1] != -1 && line[1] != '\''
				&& line[1] != '\"')
				return (0);
		}
		line++;
	}
	return (res);
}

static int	check_args_exit(char *line)
{
	if (check_if_the_first_arg_is_only_spaces(line))
		return (2);
	replace_chars_in_str(line, -1, ' ');
	rm_useless_quotes(line);
	while (*line)
	{
		if (!ft_isdigit(*line) && *line != ' ' && *line)
		{
			write(2, "minishell: exit: numeric argument required\n", 44);
			return (2);
		}
		if (*line == ' ' && line[1] && line[1] != ' ')
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			return (1);
		}
		line++;
	}
	return (0);
}

int	bi_exit(char *line)
{
	char	*line_cpy;
	int		res;
	int		args_flag;
	int		fd[2];

	line_cpy = line;
	if (!redirect_before_bi(line, fd))
		return (the_return_value(1));
	restaure_redirections_bi(fd);
	while (*line == ' ')
		line++;
	line += 4;
	while (*line == ' ')
		line++;
	if (!(*line))
		return (-(ft_strlcpy(line_cpy, "exit", 5) || 1));
	args_flag = check_args_exit(line);
	res = 1;
	if (args_flag == 1)
		return (the_return_value(1));
	else if (args_flag == 0)
		res = ft_atoi(line);
	ft_strlcpy(line_cpy, "exit", 5);
	return (the_return_value(res % 256));
}
