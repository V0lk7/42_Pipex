/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:41:01 by jduval            #+#    #+#             */
/*   Updated: 2023/02/07 15:32:28 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
//#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	//if (argc != 5)
	//	return (0);
	open("lolo", O_RDONLY);
	perror(NULL);
	printf("%d\n", errno);
	return (0);
}
