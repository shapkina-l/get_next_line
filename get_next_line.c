/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:02:52 by lshapkin          #+#    #+#             */
/*   Updated: 2024/06/19 18:40:09 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    char *line;
    char *buffer;
    static char *left_line;

    buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
    {
        free(left_line);
        free(buffer);
        left_line = NULL;
        buffer = NULL;
        return (NULL);
    }
    if (!buffer)
        return (NULL);
    line = fill_line_buffer(fd, left_line, buffer);
    free (buffer);
    buffer = NULL;
    if (!line)
        return (NULL);
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
    while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
        i++;
    if (line_buffer[i] == 0 || line_buffer[i + 1] == 0)
        return (NULL);
    len = ft_strlen(line_buffer);
    left = ft_substr(line_buffer, i + 1, len - i);
    if (*left == 0)
    {
        free(left);
        left = NULL;
    }
    line_buffer[i + 1] = '\0';
    return(left);
}
