/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:48:34 by jthor             #+#    #+#             */
/*   Updated: 2022/04/12 21:41:01 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Function that returns the length of the string s.
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
Function that compares the strings s1 and s2 and returns the
difference betweeen them, or 0 if they are identical.
*/
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

/*
Modified version of ft_strjoin() for formatting reasons.
*/
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

/*
Function that frees the string array passed as the parameter.
*/
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

/*
Function that terminates the program with an error message.
*/
void	err_msg(char *s)
{
	write(2, "Error message: ", 15);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	perror("Error description: ");
	exit(EXIT_FAILURE);
}
