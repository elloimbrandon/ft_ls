/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:21:45 by brandonf          #+#    #+#             */
/*   Updated: 2019/09/02 05:10:49 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_ls.h"

void	build_path(t_info *info)
{
	int i;

	i = 0;
	info->path = (char**)ft_memalloc(sizeof(char*) * (info->total_files + 1));
	while (i < info->total_files)
	{
		info->path[i] = ft_strnew(ft_strlen(info->files[i])
			+ ft_strlen(info->dirs[info->cur_dir]) + 1);
		ft_strcat(info->path[i], info->dirs[info->cur_dir]);
		ft_strcat(info->path[i], "/");
		ft_strcat(info->path[i], info->files[i]);
		i++;
	}
	info->total_files = 0;
}

void	double_swap(char **ptr, int i, int j)
{
	char	*tmp;

	tmp = ptr[i];
	ptr[i] = ptr[j];
	ptr[j] = tmp;
}

void	free_recur(t_info *recur_path)
{
	free(recur_path->flags);
	free(recur_path->dirs);
	free(recur_path);
}

void	free_all(t_info *info)
{
	free(info->files);
	free(info->path);
	free(info->flags);
	free(info);
}
