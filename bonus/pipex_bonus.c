/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:26:11 by jthor             #+#    #+#             */
/*   Updated: 2022/04/13 01:49:25 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
This function does the last execve. The reason why this is different from
loop_exec() is because the output goes to the intended outfile. For this
reason, the use of tempfile2 is unnecessary.
*/
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

/*
The first command until (n - 1) commands are executed using this function.
The logic flow is as follows :-
	1.	manage_temp( , 0) initialises two hidden tempfiles.
			.tempfile.txt  => Input file
			.tempfile2.txt => Output file
	2.	Start the forking process. In the child process, the command is
		executed using exec_cmd(), and the execve terminates the child process.
	3.	After the command is executed, the contents of tempfile2 needs to be
		copied into tempfile so that it can be used as the input for the next
		command.
	4.	Finally, delete tempfile2 using unlink().
*/
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

/*
Struct initialiser for multiple pipes with here_doc. Here the input text is
written by the user until a limiter is reached. This input text is stored
in a tempfile that will reside as a hidden file in the current directory.
Finally, the outfile is tested and stored.
*/
void	init_hd(t_ppx_b *info, char **argv, int last)
{
	char	*limiter;
	char	*line;
	int		tempfile;

	limiter = ft_strjoin(argv[2], "\n");
	tempfile = open(".tempfile.txt", O_WRONLY | O_CREAT, 00644);
	write(1, "pipex heredoc> ", 15);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		write(tempfile, line, ft_strlen(line));
		free(line);
		write(1, "pipex heredoc> ", 15);
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

/*
Struct initialiser for multiple pipes in the absence of here_doc. Here, the IO
files are tested for access and stored. In the end, prep_tempfile() takes the
input file and then copies its contents into a tempfile that will reside as a
hidden file in the current directory {.tempfile.txt}.
*/
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

/*
Main pipex function for the bonus section. This version handles multiple pipes
and heredoc. Logic flow is a s follows :-
	1.	Simple argument count error checks
	2.	Check if here_doc is present as the first argument. if it is, run
		struct initialiser to handle here_doc situation.
	3.	If here_doc is not in use, continue to normal struct initialisation.
	4.	Initialise the possible paths for the commands using init_paths().
	5.	In steps 2 and 3, a different index is assigned. This index points to
		the first command in the argument line. Using {index < argc - 2} as
		the loop control, we can execute each command excluding the last command.
	6.	At the last command, run last_exec(). The reason this is different from
		loop_exec() is the redirection for the final output.
	7.	Clean up.
*/
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
