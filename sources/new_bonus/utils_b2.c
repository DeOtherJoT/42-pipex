#include "pipex.h"

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