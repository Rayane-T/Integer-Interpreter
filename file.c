/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtayache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:39:21 by rtayache          #+#    #+#             */
/*   Updated: 2022/07/10 21:39:23 by rtayache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 8000

struct s_kv
{
	char	key[256];
	char	val[256];
};

void	betweener(struct s_kv *arr, char *str, int j, int n)
{
	while (*str != '\0')
	{
		j = 0;
		while (*str != ':' && *str != ' ' && *str != '\0')
		{
			arr[n].key[j] = *str++;
			j++;
		}
		while (*str == ' ')
			str++;
		arr[n].key[j] = '\0';
		j = 0;
		str++;
		while (*str == ' ')
			str++;
		while (*str != '\n' && *str != '\0')
		{
			arr[n].val[j] = *str++;
			j++;
		}
		arr[n].val[j] = '\0';
		str++;
		n++;
	}
}

struct s_kv	*clean_dick(char *str)
{
	int				j;
	int				n;
	struct s_kv		*arr;

	n = 0;
	j = 0;
	arr = (struct s_kv *)malloc(sizeof(struct s_kv) * 256);
	betweener(arr, str, j, n);
	return (arr);
}

struct s_kv	*file_read(char *str)
{
	char	*buf;
	int		fd;
	int		ret;

	buf = (char *)malloc(BUF_SIZE * sizeof(char));
	fd = open(str, O_RDONLY);
	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
	close(fd);
	return (clean_dick(buf));
}
