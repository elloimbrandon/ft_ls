/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:21:14 by brandonf          #+#    #+#             */
/*   Updated: 2019/09/02 04:58:37 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_ls.h"

long	get_time(char *str1, char *str2)
{
	struct stat	sbuf;
	struct stat	buf;
	long		seconds;

	ft_bzero(&sbuf, sizeof(struct stat));
	ft_bzero(&buf, sizeof(struct stat));
	lstat(str1, &sbuf);
	lstat(str2, &buf);
	seconds = buf.st_mtimespec.tv_sec - sbuf.st_mtimespec.tv_sec;
	if (seconds < 0)
		return (-1);
	if (seconds > 0)
		return (1);
	return (ft_strcmp(str2, str1));
}

void	handle_alpha(t_info *info)
{
	int		i;
	int		j;

	i = 0;
	while (info->path && info->path[i + 1])
	{
		j = 1;
		while (info->path && info->path[j])
		{
			if (ft_strcmp(info->path[j], info->path[j - 1]) < 0)
			{
				double_swap(info->files, j - 1, j);
				double_swap(info->path, j - 1, j);
			}
			j++;
		}
		i++;
	}
}

void	handle_t(t_info *info)
{
	int		i;
	int		j;

	i = 0;
	while (info->path && info->path[i + 1])
	{
		j = 1;
		while (info->path && info->path[j])
		{
			if (get_time(info->path[j], info->path[j - 1]) < 0)
			{
				double_swap(info->files, j - 1, j);
				double_swap(info->path, j - 1, j);
			}
			j++;
		}
		i++;
	}
}

void	handle_r(t_info *info)
{
	char	*temp;
	int		x;
	int		k;

	x = 0;
	k = 0;
	while (info->path[k])
		k++;
	k -= 1;
	while (x <= (k) / 2 + 1 && info->path[x] && info->path[k])
	{
		temp = info->files[x];
		info->files[x] = info->files[k];
		info->files[k] = temp;
		temp = info->path[x];
		info->path[x] = info->path[k];
		info->path[k] = temp;
		k--;
		x++;
	}
}

void	error_check(t_info *info, char **argv, int i)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(argv[info->past_flag][i]);
	ft_putendl("");
	ft_putstr("usage: ft_ls ");
	ft_putstr("[-artlR] ");
	ft_putstr("[file ...]");
}
