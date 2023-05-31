#include "../../includes/pipex.h"

void	execute(t_bppx *info, char *cmd, char **envp)
{
	char	*cmd_path;
	char 	**cmd_args;
	int		i;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_args[0][0] == '.')
		cmd_path = cmd_args[0];
	else
	{
		i = 0;
		while (info->paths[i])
		{
			cmd_path = ft_strjoin_pipex(info->paths[i], cmd_args[0]);
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

void	loop_exec2(t_bppx *info, char *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	child;

	if (pipe(pipe_fd) == -1)
		err_msg("Failed on loop pipe()");
	child = fork();
	if (child < 0)
		err_msg("Error on fork()");
	if (child == 0)
	{
		close(pipe_fd[0]);
		dup2(info->infile, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execute(info, cmd, envp);
		err_msg("Error on child command execution");
	}
	close(pipe_fd[1]);
	waitpid(child, NULL, 0);
	close(info->infile);
	info->infile = pipe_fd[0];
}

void	last_exec2(t_bppx *info, char *cmd, char **envp)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		err_msg("Error on fork()");
	if (child == 0)
	{
		dup2(info->infile, STDIN_FILENO);
		dup2(info->outfile, STDOUT_FILENO);
		execute(info, cmd, envp);
		err_msg("Error on final child command execution");
	}
	waitpid(child, NULL, 0);
	close(info->infile);
}