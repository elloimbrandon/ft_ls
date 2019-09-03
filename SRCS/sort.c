/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:21:10 by brandonf          #+#    #+#             */
/*   Updated: 2019/09/02 05:08:33 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_ls.h"

void	check_dir(t_info *info)
{
	DIR				*dir;
	struct stat		sbuf;

	lstat(info->dirs[info->cur_dir], &sbuf);
	if (!(dir = opendir(info->dirs[info->cur_dir])) && !S_ISREG(sbuf.st_mode))
	{
		ft_putstr("ft_ls: ");
		ft_putstr(info->dirs[info->cur_dir]);
		ft_putendl(": No Such file or directory");
		return ;
	}
	else if (S_ISREG(sbuf.st_mode))
	{
		ft_putendl(info->dirs[info->cur_dir]);
		return ;
	}
	else if (info->dr_count > 1)
	{
		ft_putstr(info->dirs[info->cur_dir]);
		ft_putstr(":\n");
		sort_all(info, dir);
	}
	else
		sort_all(info, dir);
	closedir(dir);
}

void	sort_all(t_info *info, DIR *dir)
{
	ft_store_files(info, dir);
	check_sort(info);
	print_all(info);
}

void	ft_store_files(t_info *info, DIR *dir)
{
	struct dirent	*file;
	struct stat		sbuf;
	int				i;

	lstat(info->dirs[info->cur_dir], &sbuf);
	while ((file = readdir(dir)) != NULL)
		info->total_files++;
	dir = opendir(info->dirs[info->cur_dir]);
	info->files = ft_memalloc(sizeof(char*) * (info->total_files + 1));
	i = 0;
	while ((file = readdir(dir)) != NULL && info->files)
	{
		if (!info->flags->a && !ft_strncmp(file->d_name, ".", 1))
		{
			info->total_files--;
			continue ;
		}
		info->files[i++] = ft_strdup(file->d_name);
	}
	closedir(dir);
}

void	check_sort(t_info *info)
{
	if (info->total_files != 0)
	{
		build_path(info);
		if (info->flags->l)
		{
			info->all_dir_total = ft_itoa(total_file_count(info));
			ft_putstr("total ");
			ft_putendl(info->all_dir_total);
		}
		if (!info->flags->t)
			handle_alpha(info);
		if (info->flags->t)
			handle_t(info);
		if (info->flags->r)
			handle_r(info);
	}
}

int		total_file_count(t_info *info)
{
	struct stat		sbuf;
	int				ret;
	int				i;

	i = 0;
	ret = 0;
	while (info->path[i] && info->path)
	{
		if ((info->flags->a) && (info->path[i]))
		{
			lstat(info->path[i], &sbuf);
			ret += sbuf.st_blocks;
		}
		else if (ft_strcmp(info->path[i], ".") && !info->flags->a)
		{
			lstat(info->path[i], &sbuf);
			ret += sbuf.st_blocks;
		}
		i++;
		ft_bzero(&sbuf, sizeof(struct stat));
	}
	return (ret);
}
