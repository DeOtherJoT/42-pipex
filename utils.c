/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:48:34 by jthor             #+#    #+#             */
/*   Updated: 2022/03/23 14:56:38 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!(s1[i] || s2[i]))
		return (0);
	while (i < n)
	{
		if ((s1[i] != s2[i]) || !(s1[i] && s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_pipex(const char *s1, const char *s2)
{
	char	*retptr;
	char	*save;

	retptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!retptr)
		return (NULL);
	save = retptr;
	while (*s1)
		*save++ = *s1++;
	*save = '/';
	save++;
	while (*s2)
		*save++ = *s2++;
	*save = '\0';
	return (retptr);
}

void	ft_free_arr(char **free_me)
{
	int	i;

	i = 0;
	while (free_me[i] != NULL)
	{
		free(free_me[i]);
		i++;
	}
	free(free_me);
}

void	err_msg(char *s)
{
	write(2, "Error message: ", 15);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	perror("Error description: ");
	exit(EXIT_FAILURE);
}
