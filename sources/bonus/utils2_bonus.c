/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 22:26:22 by jthor             #+#    #+#             */
/*   Updated: 2022/04/12 22:26:25 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Lonely function that serves to copy the file contents of src to dest,
referenced by their file descriptors.
*/
void	cp_file(int src, int dest)
{
	char	*line;

	line = get_next_line(src);
	if (line == NULL)
		write(dest, "\0", 1);
	while (line != NULL)
	{
		write(dest, line, ft_strlen(line));
		free(line);
		line = get_next_line(src);
	}
	free(line);
}
