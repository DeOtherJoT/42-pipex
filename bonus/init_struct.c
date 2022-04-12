/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:48:53 by jthor             #+#    #+#             */
/*   Updated: 2022/04/12 21:43:23 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *info, int argc, char **argv, char **envp)
{
	if (argc != 5)
		err_msg("Invalid input");
	test_and_fill_io(info, argv);
	fill_arg(info, argv[2], 1);
	fill_arg(info, argv[3], 2);
	fill_path(info, info->args_1[0], envp, 1);
	fill_path(info, info->args_2[0], envp, 2);
}

void	test_and_fill_io(t_pipex *info, char **argv)
{
	if (access(argv[1], R_OK | F_OK) == -1)
		err_msg("Infile error");
	else
		info->infile = open(argv[1], O_RDONLY);
	if (access(argv[4], F_OK) == 0)
	{
		if (access(argv[4], W_OK) == -1)
			err_msg("Outfile error");
		info->outfile = open(argv[4], O_TRUNC | O_RDWR, 00644);
	}
	else
		info->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (info->infile == -1)
		err_msg("Infile open() failure.");
	if (info->outfile == -1)
		err_msg("Outfile open() failure.");
}

void	fill_arg(t_pipex *info, char *com_line, int flag)
{
	char	**temp_val;

	temp_val = ft_split(com_line, ' ');
	if (temp_val == NULL)
		err_msg("Argument split error");
	if (flag == 1)
		info->args_1 = temp_val;
	else
		info->args_2 = temp_val;
}

int	check_alt_name(t_pipex *info, char *name, int flag)
{
	char	*temp_path;

	if ((ft_strncmp(name, "/", 1) != 0) && (ft_strncmp(name, ".", 1) != 0))
		return (0);
	temp_path = ft_strdup(name);
	if (!temp_path)
	{
		err_msg("Unexpected malloc error");
		return (0);
	}
	else if (access(temp_path, F_OK | X_OK) == 0)
	{
		if (flag == 1)
			info->path_1 = temp_path;
		else
			info->path_2 = temp_path;
		return (1);
	}
	else
	{
		free(temp_path);
		err_msg("Invalid command path");
		return (0);
	}
}

void	fill_path(t_pipex *info, char *name, char **envp, int flag)
{
	char	**temp_env;
	char	*temp_path;
	char	**save_free;

	if (check_alt_name(info, name, flag) == 1)
		return ;
	while (*envp && (ft_strncmp(*envp, "PATH=", 5) != 0))
		envp++;
	temp_env = ft_split(*envp + 5, ':');
	save_free = temp_env;
	while (*temp_env != NULL)
	{
		temp_path = ft_strjoin_pipex(*temp_env, name);
		if (access(temp_path, F_OK) == 0)
			break ;
		free(temp_path);
		temp_env++;
	}
	ft_free_arr(save_free);
	if (temp_path == NULL || access(temp_path, X_OK) == -1)
		err_msg("Failed to find valid command path.");
	if (flag == 1)
		info->path_1 = temp_path;
	else
		info->path_2 = temp_path;
}
