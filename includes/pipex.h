/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:46:39 by jthor             #+#    #+#             */
/*   Updated: 2022/04/12 22:38:29 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_ppx_b
{
	int		infile;
	int		outfile;
	char	**paths;
}	t_ppx_b;

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
void	pipex(int argc, char **argv, char **envp);
void	execute_child_1(t_pipex info, int pipe_fd[2], char **envp);
void	execute_child_2(t_pipex info, int pipe_fd[2], char **envp);
void	close_struct(t_pipex *info);

/* Struct Initialisation */
void	init_struct(t_pipex *info, int argc, char **argv, char **envp);
void	test_and_fill_io(t_pipex *info, char **argv);
void	fill_arg(t_pipex *info, char *com_line, int flag);
void	fill_path(t_pipex *info, char *name, char **envp, int flag);
int		check_alt_name(t_pipex *info, char *name, int flag);

/* Utils */
size_t	ft_strlen(const char *s);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strjoin_pipex(const char *s1, const char *s2);
void	ft_free_arr(char **free_me);
char	*ft_strdup(const char *s);

/* Error handling */
void	err_msg(char *s);

/* Bonus */
void	close_info(t_ppx_b *info);
void	exec_cmd(t_ppx_b info, char *cmd, char **envp);
void	manage_temp(int	*temp_fd, int flag);
void	prep_tempfile(int infile);
void	init_paths(t_ppx_b *info, char **envp);
void	cp_file(int src, int dest);

/* GNL */
char	*get_next_line(int fd);
ssize_t	read_buff(int fd, char **buff, ssize_t *read_ret);
void	handle_buff(char **stat_str, char **buff);
char	*final_line(char **stat_str);
char	*ft_strchr(char const *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strldup(char const *s, int len);
void	ft_handleptr(char **ptr, int mode);

/* Bonus 2 */
void	ft_calloc(size_t count, size_t size);

#endif
