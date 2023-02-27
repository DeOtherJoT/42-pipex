/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:48:42 by jthor             #+#    #+#             */
/*   Updated: 2022/04/12 19:01:43 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// NOTE: This file contains functions for mandatory only. 

/*
This function and the one below it does the following :-
	1.	Close the end of the pipe that is not in use
	2.	Use dup2() to modify the IO stream of the command
	3.	Use execve() to execute the command with it's arguments.
	4.	execve() exits the program on success, so if it failed, the err_msg()
		is executed.
*/
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

/*
Function to close the pipes for the parent process, because the
execute_child_x() function only closes the ends of the pipe for the
child process.
*/
void	close_pipe_fd(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

/*
Destructor function to prevent memory leaks or whatever.
*/
void	close_struct(t_pipex *info)
{
	close(info->infile);
	close(info->outfile);
	free(info->path_1);
	free(info->path_2);
	ft_free_arr(info->args_1);
	ft_free_arr(info->args_2);
}

/*
Main pipex function for the mandatory part only. The flow is as follows :-
	1.	Initialize the struct for the program, that contains the
			a)	File descriptors of the input and output files
			b)	Paths for the commands e.g. user/bin/cat
			c)	Arguments for the commands, represented by an array of strings
	2.	Create the pipe using pipe()
	3.	Start the forking process
	4.	Wait for the forking process to finish their tasks using waitpid()
	5.	Clean up

Explanation for fork() :-
	On fork(), the calling function is designated as the parent process and
	an exact copy of the program is created and desginated as the child
	process. The value of child_x would be different depending on which of
	the processes it is in.
		-	In the parent process, the child_x variable is assigned the
			process ID of the child process.
		-	In the child process, the child_x variable is assigned 0.
		-	If failure, fork() returns a negative int.
	Using the characteristics above, we can use the value of child_x in order
	to call the function execute_child_x() if its the child process.
*/
void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	info;
	int		pipe_fd[2];
	pid_t	child_1;
	pid_t	child_2;

	init_struct(&info, argc, argv, envp);
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
