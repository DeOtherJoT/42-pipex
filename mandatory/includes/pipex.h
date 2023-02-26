/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:46:39 by jthor             #+#    #+#             */
/*   Updated: 2022/03/24 21:41:34 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	*path_1;
	char	*path_2;
	char	**args_1;
	char	**args_2;
}	t_pipex;

/* pipex.c */
void	pipex(char **argv, char **envp);
void	execute_child_1(t_pipex info, int pipe_fd[2], char **envp);
void	execute_child_2(t_pipex info, int pipe_fd[2], char **envp);
void	close_struct(t_pipex *info);

/* Struct Initialisation */
void	init_struct(t_pipex *info, char **argv, char **envp);
void	test_and_fill_io(t_pipex *info, char **argv);
void	fill_arg(t_pipex *info, char *com_line, int flag);
void	fill_path(t_pipex *info, char *name, char **envp, int flag);
int		check_alt_name(t_pipex *info, char *name, int flag);

/* Utils */
int		ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin_pipex(const char *s1, const char *s2);
void	ft_free_arr(char **free_me);
char	*ft_strdup(const char *s);

/* Error handling */
void	err_msg(char *s);

#endif
