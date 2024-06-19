/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshapkin <lshapkin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:56:56 by lshapkin          #+#    #+#             */
/*   Updated: 2024/06/19 23:54:28 by lshapkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef MAX_FD
# define MAX_FD 10240
# endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1000
# endif

char    *get_next_line(int fd);
char    *fill_line_buffer(int fd, char *left_line, char *buffer);
char    *set_line(char *line_buffer);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strchr(char *s, int c);
size_t  ft_strlen(const char *s);
char    *ft_strdup(char *src);
char    *ft_strjoin(char const *s1, char const *s2);

# endif