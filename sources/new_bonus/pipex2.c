#include "pipex.h"

int	init_hd(t_ppx_b *info, char **argv, int last)
{
	char	*limiter;
	char	*input;
	char	*hd_str;
	char	*temp_hd;

	limiter = ft_strjoin(argv[2], "\n");
	hd_str = ft_calloc(1, sizeof(char));
	input = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		temp_hd = ft_strjoin(hd_str, input);
		free(input);
		free(hd_str);
		hd_str = temp_hd;
		input = get_next_line(STDIN_FILENO);
	}
	free(input);
	free(limiter);
	info->infile = open_hd(hd_str);
	free(hd_str);
	if (access(argv[last], F_OK) == 0)
	{
		if (access(argv[last], W_OK) == -1)
			err_msg("Outfile error");
	}
	info->outfile = open(argv[last], O_WRONLY | O_CREAT | O_APPEND, 00644);
}

void	pipex(int argc, char **argv, char **envp)
{
	t_ppx_b	info;
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
		loop_exec(info, argv[index], envp);
	last_exec(info, argv[index], envp);
	close_info(&info);
}