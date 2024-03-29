/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:25:20 by jduval            #+#    #+#             */
/*   Updated: 2023/03/08 16:39:16 by jduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	size_t	size_alloc;
	char	*new_s;
	size_t	size_srcs;

	size_alloc = ft_strlen(s1) + ft_strlen(s2);
	new_s = malloc(size_alloc * (sizeof(char) + 1));
	if (!new_s)
	{
		free (s2);
		return (NULL);
	}
	if (!s2)
	{
		ft_strlcpy(new_s, s1, size_alloc + 1);
		return (new_s);
	}
	size_alloc = ft_strlen(s1) + 1;
	ft_strlcpy(new_s, s1, size_alloc);
	size_alloc = ft_strlen(new_s);
	size_srcs = ft_strlen(s1) + ft_strlen(s2) + 1;
	ft_strlcpy(&new_s[size_alloc], s2, size_srcs);
	free (s2);
	return (new_s);
}

int	ft_find_quotes(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == 39)
			quote++;
		i++;
	}
	return (quote);
}

void	ft_error_quit(void)
{
	perror(NULL);
	exit(0);
}

int	ft_last_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	if (i > 0)
		i--;
	return (i);
}

void	ft_close_fds(int fd1, int fd2, int fd3)
{
	if (fd1 > 2)
		close(fd1);
	if (fd2 > 2)
		close(fd2);
	if (fd3 > 2)
		close(fd3);
}
