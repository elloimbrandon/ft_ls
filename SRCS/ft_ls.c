/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:20:44 by brandonf          #+#    #+#             */
/*   Updated: 2019/09/03 17:29:46 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_ls.h"

void			ft_ls(t_info *info, int argc)
{
	if (info->flags->c && ft_strcmp(info->dirs[0], "."))
	{
		if (info->recursive_check)
			ft_putendl("");
		ft_putstr(info->dirs[0]);
		ft_putendl(":");
	}
	check_dir(info);
	if (info->dr_count != 1)
		info->cur_dir++;
	if (info->past_flag < argc)
		ft_putendl("");
	if (info->flags->c)
		recursive_check(info, argc);
}

t_info			*recursive_struct(t_info *info, int i)
{
	t_info *recur_dir;

	recur_dir = (t_info *)ft_memalloc(sizeof(t_info) + 1);
	recur_dir->flags = (t_flags *)ft_memalloc(sizeof(t_flags) + 1);
	recur_dir->flags->l = info->flags->l;
	recur_dir->flags->t = info->flags->t;
	recur_dir->flags->a = info->flags->a;
	recur_dir->flags->r = info->flags->r;
	recur_dir->flags->c = info->flags->c;
	recur_dir->total_files = 0;
	recur_dir->past_flag = info->past_flag;
	recur_dir->dr_count = info->dr_count;
	recur_dir->cur_dir = 0;
	recur_dir->all_dir_total = 0;
	recur_dir->dirs = (char **)ft_memalloc(sizeof(char *) * 2);
	recur_dir->dirs[0] = info->path[i];
	recur_dir->recursive_check = 1;
	recur_dir->files = NULL;
	recur_dir->path = NULL;
	return (recur_dir);
}

void			recursive_check(t_info *info, int argc)
{
	struct stat	sbuf;
	t_info		*recur_path;
	int			i;

	i = 0;
	ft_bzero(&sbuf, sizeof(struct stat));
	while (info->path && info->path[i])
	{
		lstat(info->path[i], &sbuf);
		if (S_ISDIR(sbuf.st_mode))
		{
			recur_path = recursive_struct(info, i);
			ft_ls(recur_path, argc);
			free_recur(recur_path);
		}
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_info		*info;
	int			i;

	i = 0;
	info = (t_info*)malloc(sizeof(t_info));
	info->flags = (t_flags*)malloc(sizeof(t_flags));
	zero_out_info(info);
	parse_flags(info, argv);
	dir_count(info, argv);
	info->dirs = ft_memalloc(sizeof(char *) * (argc - info->past_flag + 1));
	if (argc == 0 || info->dr_count == 0)
	{
		get_dot(info);
		ft_ls(info, argc);
	}
	else
	{
		while (argv[info->past_flag] && (info->past_flag < argc))
		{
			info->dirs[i++] = ft_strdup(argv[info->past_flag++]);
			ft_ls(info, argc);
		}
		free_all(info);
	}
	return (0);
}
