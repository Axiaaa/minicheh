/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 23:08:43 by geymat            #+#    #+#             */
/*   Updated: 2024/03/13 19:33:46 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getenv(char **envp, char *key)
{
	size_t	i;
	int		accurate;

	i = 0;
	accurate = 1;
	while (*envp)
	{
		i = 0;
		accurate = 1;
		while ((*envp)[i] && (*envp)[i] != '=' && accurate && key[i])
		{
			if (key[i] != (*envp)[i])
				accurate = 0;
			i++;
		}
		if (key[i] || (*envp)[i] != '=')
			accurate = 0;
		if (accurate)
			return (*envp);
		envp++;
	}
	return (NULL);
}

char	*ft_strerror(void)
{
	if (errno == 2)
		return ("no such file or directory");
	if (errno == 13)
		return ("permission denied");
	return (strerror(errno));
}

void	print_error(char *name, char *error, char *file)
{
	char	*temp;
	int		i;

	temp = malloc(1);
	if (!temp)
		return ;
	temp[0] = 0;
	temp = ft_strjoin_free_first(temp, name);
	temp = ft_strjoin_free_first(temp, ": ");
	temp = ft_strjoin_free_first(temp, error);
	temp = ft_strjoin_free_first(temp, ": ");
	temp = ft_strjoin_free_first(temp, file);
	temp = ft_strjoin_free_first(temp, "\n");
	if (!temp)
		return ;
	i = 0;
	while (temp[i])
		i++;
	write(2, temp, i);
	free(temp);
}

void	merge_fd(size_t fd1, size_t fd2, int fd_res[2])
{
	fd_res[0] = fd1;
	fd_res[1] = fd2;
}

int	almost_pipex(char **argv, char **envp, void *env)
{
	int	pid;
	int	res;
	int	infos;
	int	return_value;
	int	base_fd[2];

	base_fd[0] = dup(0);
	if (base_fd[0] == -1)
		return (1);
	base_fd[1] = dup(1);
	if (base_fd[1] == -1)
		return (close(base_fd[0]), 1);
	pid = loops_executions(argv, envp, base_fd, env);
	res = 1;
	infos = -1;
	return_value = 1;
	while (res != -1)
	{
		res = waitpid(0, &infos, 0);
		if (res == pid)
			return_value = (WEXITSTATUS(infos) + 1) * WIFEXITED(infos) - 1;
	}
	return (return_value);
}
