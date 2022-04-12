/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:47:22 by jthor             #+#    #+#             */
/*   Updated: 2022/03/24 21:37:45 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_count(char const *s, char c)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			ret++;
			while (*s && *s != c)
				s++;
		}
	}
	return (ret);
}

static int	word_len(char const *s, char c)
{
	int	ret;

	ret = 0;
	while (s[ret] && s[ret] != c)
		ret++;
	return (ret);
}

static int	word_split(char const *s, char c, char **ret, int i)
{
	int	j;
	int	x;

	ret[i] = (char *)malloc((word_len(s, c) + 1) * sizeof(char));
	if (!ret[i])
	{
		x = 0;
		while (x < i)
		{
			free(ret[x]);
			x++;
		}
		free(ret);
		return (0);
	}
	j = 0;
	while (*s && *s != c)
		ret[i][j++] = *s++;
	ret[i][j] = '\0';
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = word_count(s, c);
	ret = (char **)malloc((words + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		if (word_split(s, c, ret, i) == 0)
			return (NULL);
		while (*s && *s != c)
			s++;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ret;

	ret = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
