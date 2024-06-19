/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:02:52 by lshapkin          #+#    #+#             */
/*   Updated: 2024/06/19 17:09:38 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
# endif

char    *get_next_line(int fd);
char *fill_line_buffer(int fd, char *left_line, char *buffer);
char *set_line(char *line_buffer);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);

char    *get_next_line(int fd)
{
    char *line;
    char *buffer;
    static char *left_line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
    {
        free(left_line);
        free(buffer);
        left_line = NULL;
        buffer = NULL;
        return (NULL);
    }
    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    line = fill_line_buffer(fd, left_line, buffer);
    free (buffer);
    left_line = set_line(line);
    return (line);    
}

char *fill_line_buffer(int fd, char *left_line, char *buffer)
{
    char *left_line_copy;
    int check;

    check = 1;
    while (check > 0)
    {
        check = read(fd, buffer, BUFFER_SIZE);
        if (check == -1)
            return(NULL);
        else if (check == 0)
            break;
        else
        {
            buffer[check] = '\0';
            if (left_line == NULL)
                left_line = ft_strdup("");
            left_line_copy = left_line;
            left_line = ft_strjoin(left_line_copy, buffer);
            free(left_line_copy);
            left_line_copy = NULL;
            if (ft_strchr(left_line, '\n') != 0)
                break;
        }
    }
    return (left_line);
}

char *set_line(char *line_buffer)
{
    char *left;
    int i;
    int len;

    i = 0;
    while (line_buffer[i] != '\n')
        i++;
    len = ft_strlen(line_buffer);
    left = ft_substr(line_buffer, i + 1, len - i);
    line_buffer[i + 1] = '\0';
    return(left);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s || !(new_str = (char *)malloc(len + 1)))
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

char	*ft_strchr(char *s, int c)
{
    int i;

    i = 0;
	while ((s[i] != '\0') && (s[i] != c))
	{
		i++;
	}
	if (s[i] == c)
	{
		return ((char *)s[i]);
	}
	return ((char*)NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		++size;
	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		return (str);
	}
	return (NULL);
}

int main (void)
{
    int fd;

    fd = open("text.txt", O_RDONLY);
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
    printf("%s\n", get_next_line(fd));
}