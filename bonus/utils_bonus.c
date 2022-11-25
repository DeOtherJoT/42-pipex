/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:25:54 by jthor             #+#    #+#             */
/*   Updated: 2022/04/12 22:25:56 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Helper function that closes file descriptors, frees malloc'd array and
deletes the hidden tempfile from the current directory.
*/
void	close_info(t_ppx_b *info)
{
	close(info->infile);
	close(info->outfile);
	ft_free_arr(info->paths);
	unlink(".tempfile.txt");
}

/*
Helper function that executes the command line passed as cmd. Example :-

BEFORE
char *cmd = "echo Hello"

AFTER
char **cmd_args = {'echo', 'Hello'}
char *cmd_path = "usr/bin/echo" (example)

As applied in the mandatory part, it is possible to use self-made commands
as long as the relative path to the executable is stated.
*/
void	exec_cmd(t_ppx_b info, char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;
	int		i;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args[0][0] == '.')
		cmd_path = cmd_args[0];
	else
	{
		i = 0;
		while (info.paths[i])
		{
			cmd_path = ft_strjoin_pipex(info.paths[i], cmd_args[0]);
			if (access(cmd_path, F_OK) == 0)
				break ;
			free(cmd_path);
			i++;
		}
	}
	if (!cmd_path)
		err_msg("Cannot find command path");
	execve(cmd_path, cmd_args, envp);
}

/*
Helper function that manages how the tempfiles are accessed, depending on the
value of the parameter flag.
	0 -	open tempfile.txt as input file, and create tempfile2.txt as the
		output file.
	1 -	close the file descriptors for both tempfiles
	2 -	open both tempfiles in order to copy tempfile2 into tempfile.
*/
void	manage_temp(int *temp_fd, int flag)
{
	if (flag == 0)
	{
		temp_fd[0] = open(".tempfile.txt", O_RDWR);
		temp_fd[1] = open(".tempfile2.txt", O_RDWR | O_CREAT, 00644);
		if (temp_fd[0] == -1 || temp_fd[1] == -1)
			err_msg("Error with temp_fd open()");
	}
	else if (flag == 1)
	{
		close(temp_fd[0]);
		close(temp_fd[1]);
	}
	else
	{
		temp_fd[0] = open(".tempfile.txt", O_RDWR | O_TRUNC);
		temp_fd[1] = open(".tempfile2.txt", O_RDWR);
	}
}

/*
This function takes the contents of the infile and copies it into a
hidden tempfile. This allows the input file to always be .tempfile.txt
during the execution of loop_exec().
*/
void	prep_tempfile(int infile)
{
	int		tempfile;
	char	*line;

	tempfile = open(".tempfile.txt", O_WRONLY | O_CREAT, 00644);
	line = get_next_line(infile);
	if (!line)
		write(tempfile, "\0", 1);
	while (line)
	{
		write(tempfile, line, ft_strlen(line));
		free(line);
		line = get_next_line(infile);
	}
	free(line);
	close(tempfile);
}

/*
This function gets and stores the possible paths where the command executables
are kept, e.g. usr/bin
*/
void	init_paths(t_ppx_b *info, char **envp)
{
	int		flag;

	flag = 0;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			flag = 1;
			break ;
		}
		envp++;
	}
	if (flag == 1)
		info->paths = ft_split(*envp + 5, ':');
	else
		err_msg("Cannot find valid paths");
}
