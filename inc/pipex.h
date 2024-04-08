/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:40:12 by geymat            #+#    #+#             */
/*   Updated: 2024/04/08 13:56:13 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdlib.h>
# include "struct.h"
# include "collector.h"

char	*ft_strjoin_free_first(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
char	*ft_strdup_until_space(const char *src);
char	*ft_strdup(const char *src);
char	*ft_getenv(char **envp, char *key);
char	*ft_strjoinwithslash(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s1);
int		close_3_free(int fd1, int fd2, int fd3, void *allocation);
int		ft_strcmp_nl(const char *first, const char *second);
int		is_a_built_in_pipe(char *line, t_env **env, int fd[3]);
int		redirections(char *line);
int		loops_executions(char **argv, char **envp, int init_fd[2], t_env **env);
int		open_file(char *file, char *name, int flags);
void	merge_fd(size_t fd1, size_t fd2, int fd_res[2]);
void	free_the_split(char **argv);
void	print_error(char *name, char *error, char *file);
void	ultimate_exit(int fd_old[2], int fd_new[2], int pid);
void	replace_chars_in_str(char *str, char c1, char c2);
void	replace_chars_in_argv(char **argv, char c1, char c2);
void	rm_useless_quotes(char *str);
void	rm_useless_quotes_argv(char **str);

#endif
