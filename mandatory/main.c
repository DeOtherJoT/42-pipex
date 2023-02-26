/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:16:12 by jthor             #+#    #+#             */
/*   Updated: 2022/03/24 15:17:11 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		err_msg("Invalid input");
	pipex(argv, envp);
	return (0);
}
