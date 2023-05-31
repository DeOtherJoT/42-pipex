#include "../../includes/pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*retptr;
	size_t	i;

	retptr = (void *)malloc(count * size);
	if (!retptr)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		((char *)retptr)[i] = 0;
		i++;
	}
	return (retptr);
}

void	init_paths(t_bppx *info, char **envp)
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

void	close_info(t_bppx *info)
{
	close(info->infile);
	close(info->outfile);
	ft_free_arr(info->paths);
}