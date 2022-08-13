/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 22:55:34 by lmiehler          #+#    #+#             */
/*   Updated: 2022/07/10 22:55:54 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

struct s_kv
{
	char	key[256];
	char	val[256];
};

void		parsestr(char *str, struct s_kv dict[256], int strlen);
char		*zerofiller(char *str, int len);
char		*check_input(char *str);
struct s_kv	*file_read(char *str);
int			ft_strlen(char *str);
void		ft_strcpy(char *dest, char *src);
void		ft_putstr(char *str, int *first);
char		*sdict_char(struct s_kv dict[256], char a, char b);


void	cpy_input(char *dest, char *src)
{
	while (*src >= '0' && *src <= '9')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

char	*check_input(char *str)
{
	int		i;
	char	*dest;
	char	*tmp;

	dest = (char *)malloc(sizeof(char) * 500);
	tmp = dest;
	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i] == '0')
		i++;
	cpy_input(dest, &str[i]);
	return (tmp);
}

int	check_zero(char *str, struct s_kv *dict)
{
	int first;

	first = 0;
	if (*str == '\0')
	{
		ft_putstr (sdict_char(dict, '0', 0), &first);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	struct s_kv	*dict;
	char		*str;
	char		*in;

	if (argc == 2)
		dict = file_read ("dict.txt");
	else if (argc == 3)
		dict = file_read (argv[2]);
	else
	{
		write (1, "Error\n", 6);
		return (-1);
	}
	in = check_input(argv[1]);
	if (in == 0)
	{
		write (1, "Error\n", 6);
		return (-1);
	}
	if (check_zero (in, dict))
		return (0);
	str = zerofiller(in, ft_strlen(in));
	parsestr(str, dict, ft_strlen(str));
}
