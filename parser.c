/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtayache <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:48:06 by rtayache          #+#    #+#             */
/*   Updated: 2022/07/10 22:55:00 by rtayache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_putstr(char *str, int *first);
void	ft_strcpy(char *dest, char *src);
int		ft_strlen(char *str);

struct s_kv
{
	char	key[256];
	char	val[256];
};

char	*zerofiller(char *str, int len)
{
	char	*arr;
	char	*ptr;

	if (len % 3 == 0)
		return (str);
	arr = (char *)malloc(len * sizeof(char) + 2);
	ptr = arr;
	if (len % 3 == 1)
	{
		*arr++ = '0';
		*arr++ = '0';
		ft_strcpy(arr, str);
		return (ptr);
	}
	*arr++ = '0';
	ft_strcpy(arr, str);
	return (ptr);
}

char	*sdict_tens(struct s_kv dict[256], int expec)
{
	int		i;
	int		zeros;

	i = 0;
	while (i < 256)
	{
		if (dict[i].key[0] == '1')
		{
			zeros = 1;
			while (dict[i].key[zeros] == '0')
			{
				if (expec == zeros)
					return (dict[i].val);
				zeros++;
			}
		}
		i++;
	}
	return (0);
}

char	*sdict_char(struct s_kv dict[256], char a, char b)
{
	int		i;

	if (a == '0')
		return (0);
	i = 0;
	while (i < 256)
	{
		if (dict[i].key[0] == a && dict[i].key[1] == '\0' && b == 0)
		{
			return (dict[i].val);
		}
		else if (dict[i].key[0] == a && dict[i].key[1] == b
			&& dict[i].key[2] == '\0')
		{
			return (dict[i].val);
		}
		i++;
	}
	return (0);
}

void	blockparse(char *str, struct s_kv dict[256], int pos, int *first)
{
	int	len;

	len = ft_strlen (str);
	ft_putstr (sdict_char (dict, str[pos], 0), first);
	if (str[pos] != '0')
	{
		ft_putstr (sdict_tens (dict, 2), first);
	}
	if (str[pos + 1] != '1')
	{
		ft_putstr (sdict_char (dict, str[pos + 1], '0'), first);
		ft_putstr (sdict_char (dict, str[pos + 2], 0), first);
	}
	else
	{
		ft_putstr (sdict_char (dict, str[pos + 1], str[pos + 2]), first);
	}
	ft_putstr (sdict_tens (dict, len - pos - 3), first);
}

void	parsestr(char *str, struct s_kv dict[256], int strlen)
{
	int		i;
	int		first;

	first = 1;
	i = 0;
	while (i < strlen)
	{
		blockparse (str, dict, i, &first);
		i += 3;
	}
	write (1, "\n", 1);
}
