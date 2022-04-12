/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:26:11 by jthor             #+#    #+#             */
/*   Updated: 2022/04/12 22:26:12 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	last_exec(t_ppx_b info, char *cmd, char **envp)
{
	pid_t	child;
	int		infile;

	infile = open(".tempfile.txt", O_RDONLY);
	child = fork();
	if (child < 0)
		err_msg("Error on fork()");
	if (child == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(info.outfile, STDOUT_FILENO);
		exec_cmd(info, cmd, envp);
		err_msg("Error on final child command execution");
	}
	waitpid(child, NULL, 0);
	close(infile);
}

void	loop_exec(t_ppx_b info, char *cmd, char **envp)
{
	int		temp_fd[2];
	pid_t	child;

	manage_temp(temp_fd, 0);
	child = fork();
	if (child < 0)
		err_msg("Error on fork()");
	if (child == 0)
	{
		dup2(temp_fd[0], STDIN_FILENO);
		dup2(temp_fd[1], STDOUT_FILENO);
		exec_cmd(info, cmd, envp);
		err_msg("Error on child command execution");
	}
	waitpid(child, NULL, 0);
	manage_temp(temp_fd, 1);
	manage_temp(temp_fd, 2);
	cp_file(temp_fd[1], temp_fd[0]);
	manage_temp(temp_fd, 1);
	unlink(".tempfile2.txt");
}

void	init_hd(t_ppx_b *info, char **argv, int last)
{
	char	*limiter;
	char	*line;
	int		tempfile;

	limiter = ft_strjoin(argv[2], "\n");
	tempfile = open(".tempfile.txt", O_WRONLY | O_CREAT, 00644);
	write(1, "pipe heredoc>", 13);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		write(tempfile, line, ft_strlen(line));
		free(line);
		write(1, "pipe heredoc>", 13);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(limiter);
	close(tempfile);
	if (access(argv[last], F_OK) == 0)
	{
		if (access(argv[last], W_OK) == -1)
			err_msg("Outfile error");
	}
	info->outfile = open(argv[last], O_WRONLY | O_CREAT | O_APPEND, 00644);
}

void	init_norm(t_ppx_b *info, char **argv, int last)
{
	if (access(argv[1], R_OK | F_OK) == -1)
		err_msg("Infile error");
	else
		info->infile = open(argv[1], O_RDONLY);
	if (access(argv[last], F_OK) == 0)
	{
		if (access(argv[last], W_OK) == -1)
			err_msg("Outfile error");
	}
	info->outfile = open(argv[last], O_TRUNC | O_RDWR | O_CREAT, 00644);
	if (info->infile == -1 || info->outfile == -1)
		err_msg("IO file error");
	prep_tempfile(info->infile);
}

void	pipex(int argc, char **argv, char **envp)
{
	t_ppx_b	info;
	int		index;

	if (argc < 5)
		err_msg("Invalid arguments");
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		init_hd(&info, argv, argc - 1);
		index = 3;
	}
	else
	{
		init_norm(&info, argv, argc - 1);
		index = 2;
	}
	init_paths(&info, envp);
	while (index < argc - 2)
	{
		loop_exec(info, argv[index], envp);
		index++;
	}
	last_exec(info, argv[index], envp);
	close_info(&info);
	return (0);
}
