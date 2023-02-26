/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:48:42 by jthor             #+#    #+#             */
/*   Updated: 2022/03/24 19:21:57 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_child_1(t_pipex info, int pipe_fd[2], char **envp)
{
	close(pipe_fd[0]);
	dup2(info.infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	execve(info.path_1, info.args_1, envp);
	err_msg("Failed to execute command 1");
}

void	execute_child_2(t_pipex info, int pipe_fd[2], char **envp)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(info.outfile, STDOUT_FILENO);
	execve(info.path_2, info.args_2, envp);
	err_msg("Failed to execute command 2");
}

void	close_pipe_fd(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	close_struct(t_pipex *info)
{
	close(info->infile);
	close(info->outfile);
	free(info->path_1);
	free(info->path_2);
	ft_free_arr(info->args_1);
	ft_free_arr(info->args_2);
}

void	pipex(char **argv, char **envp)
{
	t_pipex	info;
	int		pipe_fd[2];
	pid_t	child_1;
	pid_t	child_2;

	init_struct(&info, argv, envp);
	if (pipe(pipe_fd) == -1)
		err_msg("Error on pipe().");
	child_1 = fork();
	if (child_1 < 0)
		err_msg("Error with child 1.");
	if (child_1 == 0)
		execute_child_1(info, pipe_fd, envp);
	child_2 = fork();
	if (child_2 < 0)
		err_msg("Error with child 2.");
	if (child_2 == 0)
		execute_child_2(info, pipe_fd, envp);
	close_pipe_fd(pipe_fd);
	waitpid(child_1, NULL, 0);
	waitpid(child_2, NULL, 0);
	close_struct(&info);
}
