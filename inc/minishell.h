/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:04:33 by geymat            #+#    #+#             */
/*   Updated: 2024/03/28 17:00:58 by geymat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "struct.h"
# include "collector.h"

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

t_env	*ft_envlstnew(char *key, char *value);
t_env	*ft_envlstnew(char *key, char *value);
t_env	*ft_envlstnew_frees(char **key_value);
size_t	path_len(char *str);
char	*get_value(char *str, t_env *env);
char	*get_a_new_line(t_env *env);
char	*get_pwd(void);
char	*ft_space_strtok(char *str);
char	*replace_env(char *str, t_env *env);
char	**create_envp(t_env *env);
char	**sep_in_two(char *str);
void	executions(char **line, t_env **env);
void	rm_useless_quotes(char *str);
void	rm_useless_quotes_argv(char **str);
void	sahandler_fake(int sig);
void	sahandler_true(int sig);
void	sahandler_s_heredoc(int sig);
void	loops_minishell(t_env **envp);
void	ft_envclear(t_env *env);
void	set_shlvl(t_env *env);
void	ft_envlstadd_until_sorted(t_env **lst, t_env *new_lst);
void	replace_chars_in_str(char *str, char c1, char c2);
int		restaure_redirections_bi(int fd[2]);
int		replace_all_here_docs(char **line, t_env *env);
int		ft_strsfree(char **strs);
int		the_return_value(size_t value);
int		replace_inside(char **p_s, size_t start, size_t end, char *s2);
int		bi_export(char *line, t_env **env);
int		bi_env(char *line, t_env **env);
int		bi_echo(char *line);
int		bi_pwd(char *line);
int		bi_cd(char *line, t_env **env);
int		bi_exit(char *line);
int		bi_unset(char *line, t_env **env);
int		almost_pipex(char **argv, char **envp, void *env);
int		redirections(char *line);
int		is_a_built_in(char *line, t_env **env);
int		ft_envlst_remove_if(t_env **start, char *line);
int		get_heredoc(char *line, t_env *env, char *name);
int		redirect_before_bi(char *line, int fd[2]);
int		do_export(char *temp, t_env **env);
int		free_ret_1(char *str);
int		open_dup2(char *line, size_t len, int flag);

#endif 
