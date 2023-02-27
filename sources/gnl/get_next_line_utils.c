/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:09:31 by jthor             #+#    #+#             */
/*   Updated: 2022/04/07 16:47:05 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(char const *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*save;

	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	save = ret;
	while (*s1)
		*save++ = *s1++;
	while (*s2)
		*save++ = *s2++;
	*save = '\0';
	return (ret);
}

char	*ft_strldup(char const *s, int len)
{
	char	*ret;
	int		i;

	if (len <= 0)
		return (NULL);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i] && i < len)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	ft_handleptr(char **ptr, int mode)
{
	if (mode == 0)
	{
		*ptr = (char *)malloc(1 * sizeof(char));
		*ptr[0] = '\0';
	}
	else if (mode == 1)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
