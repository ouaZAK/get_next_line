/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouaraqa <zouaraqa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:59:34 by zouaraqa          #+#    #+#             */
/*   Updated: 2023/02/20 18:12:16 by zouaraqa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_after_nl(char *stock)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	len = ft_strlen(stock) - i;
	if (!stock[i])
		return (free(stock), NULL);
	if (len == 1)
		return (free(stock), NULL);
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (0);
	j = 0;
	i++;
	while (stock[i])
		str[j++] = stock[i++];
	str[j] = '\0';
	free(stock);
	return (str);
}

char	*get_befor_nl(char *stock)
{
	char	*str;
	int		i;

	i = 0;
	if (!stock[i])
		return (0);
	while (stock[i] && stock[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (0);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		str[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*read_and_stock(int fd, char *stock)
{
	char	*buff;
	int		nbr_readed;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	nbr_readed = 1;
	while (nbr_readed > 0)
	{
		nbr_readed = read(fd, buff, BUFFER_SIZE);
		if (nbr_readed == -1)
		{
			free(buff);
			free(stock);
			return (0);
		}
		buff[nbr_readed] = '\0';
		stock = ft_strjoin(stock, buff);
		if (locate(stock, '\n'))
			break ;
	}
	free(buff);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0 || fd == 1 || fd == 2)
		return (0);
	stock = read_and_stock(fd, stock);
	if (!stock)
		return (0);
	line = get_befor_nl(stock);
	stock = get_after_nl(stock);
	return (line);
}
