/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:33:46 by vwautier          #+#    #+#             */
/*   Updated: 2025/01/03 14:15:56 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*save;
	char			*line;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_save(&save, buffer, fd);
	free(buffer);
	buffer = NULL;
	if (save == NULL)
		return (NULL);
	extract_line(&save, &line);
	clean_save(&save);
	if ((line != NULL) && (line[0] == '\0'))
	{
		ft_lstclear(&save);
		save = NULL;
		free(line);
		line = NULL;
	}
	return (line);
}

void	read_save(t_list **save, char *buffer, int fd)
{
	ssize_t	size_read;
	t_list	*current_node;

	size_read = 1;
	while ((!have_new_line_last(*save)) && (size_read != 0))
	{
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (size_read == 0)
			break ;
		if (size_read == -1)
		{
			ft_lstclear(save);
			break ;
		}
		buffer[size_read] = '\0';
		current_node = ft_lstnew(ft_strdup(buffer));
		if (!current_node)
		{
			ft_lstclear(save);
			break ;
		}
		ft_lstadd_back(save, current_node);
	}
}

void	extract_line(t_list **list, char **ligne)
{
	char	*line;
	size_t	len;
	t_list	*current;
	char	*content;

	current = *list;
	len = size_content(current);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return ;
	line[len] = '\0';
	len = 0;
	while (current != NULL)
	{
		content = (char *)current->content;
		while (*content && *content != '\n')
			line[len++] = *content++;
		if (*content == '\n')
		{
			line[len] = *content;
			break ;
		}
		current = current->next;
	}
	*ligne = line;
}

void	clean_save(t_list **save)
{
	t_list	*last;
	t_list	*newnode;
	char	*content;

	if (!save || !*save)
		return ;
	last = *save;
	while (last && last->next)
		last = last->next;
	content = (char *)last->content;
	while (*content != '\n' && *content != '\0')
		content++;
	if (*content == '\n' && *content)
		content++;
	if (*content != '\0')
	{
		newnode = ft_lstnew(ft_strdup(content));
		ft_lstclear(save);
		*save = newnode;
	}
	else
		ft_lstclear(save);
}

int	have_new_line_last(t_list *list)
{
	char	*content;
	t_list	*last;

	if (!list)
		return (0);
	last = list;
	while (last && last->next)
		last = last->next;
	if (last->next == NULL)
	{
		content = (char *)last->content;
		while (*content != '\0')
		{
			if (*content == '\n')
				return (1);
			content++;
		}
	}
	return (0);
}

/*
int main()
{
	int fd;
	char *line = NULL;

	fd = open("42.fdf", O_RDONLY);
	if (fd == -1)
		return (0);
	//line = get_next_line(fd);
	//printf("%s",line);
	
	while (1)
	{
		line = get_next_line(fd);			
		if(line)
			printf("%s", line);
		if (!line)
		{
			break;
		}
		free(line);
	}
	close(fd);
	return 0;
}
*/