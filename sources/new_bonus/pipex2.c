#include "../../includes/pipex.h"

char	*hd_helper(char *limiter)
{
	char	*ret;
	char	*temp;
	char	*input;

	write(1, "pipex heredoc >", 15);
	input = get_next_line(STDIN_FILENO);
	ret = ft_calloc(1, sizeof(char));
	while (ft_strncmp(input, limiter, ft_strlen(input)) != 0)
	{
		temp = ft_strjoin(ret, input);
		free(ret);
		free(input);
		ret = temp;
		write(1, "pipex_heredoc >", 15);
		input = get_next_line(STDIN_FILENO);
	}
	free(input);
	return (ret);
}

int	open_hd(char *str)
{
	int	fd[2];

	if (pipe(fd) == -1)
		err_msg("Failed on hd pipe");
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
}

int	init_hd(t_bppx *info, char **argv, int last)
{
	char	*limiter;
	char	*hd_str;

	limiter = ft_strjoin(argv[2], "\n");
	hd_str = hd_helper(limiter);
	free(limiter);
	info->infile = open_hd(hd_str);
	free(hd_str);
	if (access(argv[last], F_OK) == 0)
	{
		if (access(argv[last], W_OK) == -1)
			err_msg("Outfile error");
	}
	info->outfile = open(argv[last], O_WRONLY | O_CREAT | O_APPEND, 00644);
	return (1);
}

void	init_norm(t_bppx *info, char **argv, int last)
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
}

void	pipex(int argc, char **argv, char **envp)
{
	t_bppx	info;
	int		index;

	if (argc < 5)
		err_msg("Invalid arguments");
	index = 1;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		index += init_hd(&info, argv, argc - 1);
	else
		init_norm(&info, argv, argc - 1);
	init_paths(&info, envp);
	while (++index < argc - 2)
		loop_exec2(&info, argv[index], envp);
	last_exec2(&info, argv[index], envp);
	close_info(&info);
}