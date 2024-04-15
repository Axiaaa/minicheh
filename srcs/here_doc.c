/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 04:23:47 by geymat            #+#    #+#             */
/*   Updated: 2024/04/15 18:05:56 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_limiter(char *line)
{
	size_t	start;
	size_t	end;
	char	*res;
	char	quote;

	start = 0;
	while (line[start] && line[start] == ' ')
		start++;
	end = start;
	while (line[end] && line[end] != ' ')
		end++;
	res = f_malloc(end - start + 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, line + start, end - start + 1);
	quote = ft_strchr(res, '\'') || ft_strchr(res, '\"');
	rm_useless_quotes(res);
	res[ft_strlen(res) + 1] = quote;
	return (res);
}

static void	clean_the_mess(char *line, char *limiter)
{
	if (line)
		f_free(line);
	else
	{
		write(2, "minishell: warning: here-document delimited"
			"by end-of-file\n", 59);
	}
	f_free(limiter);
}

static void	open_heredocs(char *command, int fd, t_env *env)
{
	char	*limiter;
	char	*line;
	size_t	len;

	limiter = get_limiter(command);
	signal(SIGINT, &sahandler_s_heredoc);
	if (!limiter)
		return ;
	line = readline(">");
	while (line && ft_strcmp(line, limiter))
	{
		if (line && !limiter[ft_strlen(limiter) + 1])
			line = replace_env(line, env);
		if (line)
			len = ft_strlen(line);
		write(fd, line, len);
		write(fd, "\n", 1);
		f_free(line);
		line = readline(">");
	}
	if (line && !limiter[ft_strlen(limiter) + 1])
		line = replace_env(line, env);
	if (line)
		len = ft_strlen(line);
	clean_the_mess(line, limiter);
}

static int	the_parent(char *name)
{
	int			kid;
	struct stat	buff;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait(&kid);
	signal(SIGINT, &sahandler_fake);
	signal(SIGQUIT, &sahandler_fake);
	if (WIFEXITED(kid) && WEXITSTATUS(kid) != 130
		&& WEXITSTATUS(kid) != -1)
		return (0);
	if (!stat(name, &buff))
		unlink(name);
	return (-2);
}

int	get_heredoc(char *line, t_env *env, char *name)
{
	int	pid;
	int	fd;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid)
		return (the_parent(name));
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
	{
		perror("minishell's here_doc");
		return (-1);
	}
	open_heredocs(line, fd, env);
	close(fd);
	f_exit(0);
	return (0);
}
