/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/09/02 17:01:55 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*loop_buf(int fd, int *ret, char *tmp)
{
	char	*str;
	char	buf[BUFFER_SIZE + 1];
	int		i;

	*ret = read(fd, buf, BUFFER_SIZE);
	if (*ret == -1)
		return (NULL);
	i = *ret;
	while (i <= BUFFER_SIZE)
		buf[i++] = 0;
	if (tmp)
		str = gnl_strdup(tmp);
	else
		str = gnl_strdup("");
	if (!str)
		return (NULL);
	free(tmp);
	tmp = NULL;
	tmp = gnl_strjoin(str, buf);
	free(str);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*get_line(char *tmp)
{
	size_t	i;
	char	*str;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*get_tmp(char *tmp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == 0 || tmp[i + 1] == 0)
	{
		free(tmp);
		return (NULL);
	}
	str = malloc(sizeof(char) * (gnl_strlen(tmp) - i));
	if (!str)
		return (NULL);
	j = 0;
	i++;
	while (tmp[i])
		str[j++] = tmp[i++];
	free(tmp);
	str[j] = 0;
	return (str);
}

int	get_next_line(int fd, char **line)
{
	static char	*tmp = NULL;
	int			ret;

	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	ret = 1;
	while (!gnl_strchr(tmp, '\n') && ret)
	{
		tmp = loop_buf(fd, &ret, tmp);
		if (!tmp)
			return (-1);
	}
	*line = get_line(tmp);
	if (!line)
		return (del_str(&tmp, -1));
	tmp = get_tmp(tmp);
	if (ret == 0 && !tmp)
		return (0);
	return (1);
}
