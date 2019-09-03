/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 04:02:04 by brfeltz           #+#    #+#             */
/*   Updated: 2019/09/02 04:58:32 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_ls.h"

void				print_all(t_info *info)
{
	int				i;
	int				k;

	k = 0;
	i = 0;
	while (info->path && info->path[i] && info->files[i])
	{
		if (info->flags->l)
		{
			while (info->path && info->path[i])
			{
				add_stat(info, i);
				ft_putstr("  ");
				print_info(info, i);
				print_time(info, i);
				ft_putendl(info->files[i]);
				i++;
			}
		}
		else
			ft_putendl(info->files[i++]);
	}
}

void				print_time(t_info *info, int i)
{
	struct stat		sbuf;
	char			*time;

	ft_bzero(&sbuf, sizeof(struct stat));
	lstat(info->path[i], &sbuf);
	time = (ctime(&sbuf.st_mtime));
	time[ft_strlen(time) - 1] = '\0';
	ft_putstr(time);
	ft_putstr(" ");
}

static void			put_perm(struct stat *sbuf)
{
	if (sbuf->st_size < 99999 && sbuf->st_size > 9999)
	{
		ft_putstr("  ");
		ft_putnbr(sbuf->st_size);
	}
	if (sbuf->st_size > 999 && sbuf->st_size < 9999)
	{
		ft_putstr("   ");
		ft_putnbr(sbuf->st_size);
	}
	if (sbuf->st_size > 99 && sbuf->st_size < 999)
	{
		ft_putstr("    ");
		ft_putnbr(sbuf->st_size);
	}
	if (sbuf->st_size < 99 && sbuf->st_size > 10)
	{
		ft_putstr("     ");
		ft_putnbr(sbuf->st_size);
	}
	if (sbuf->st_size < 10)
	{
		ft_putstr("      ");
		ft_putnbr(sbuf->st_size);
	}
}

void				print_info(t_info *info, int i)
{
	struct stat		sbuf;
	struct passwd	*password;
	struct group	*group;

	ft_bzero(&sbuf, sizeof(struct stat));
	lstat(info->path[i], &sbuf);
	password = getpwuid(sbuf.st_uid);
	group = getgrgid(sbuf.st_gid);
	if (sbuf.st_nlink > 99)
		ft_putnbr(sbuf.st_nlink);
	if (sbuf.st_nlink < 99)
	{
		ft_putstr("  ");
		ft_putnbr(sbuf.st_nlink);
	}
	ft_putstr(" ");
	ft_putstr(password->pw_name);
	ft_putstr("  ");
	ft_putstr(group->gr_name);
	put_perm(&sbuf);
	ft_putstr(" ");
}

void				add_stat(t_info *info, int i)
{
	struct stat		sbuf;

	ft_bzero(&sbuf, sizeof(struct stat));
	lstat(info->path[i], &sbuf);
	if (S_ISLNK(sbuf.st_mode))
		ft_putchar('l');
	else
		ft_putchar((S_ISDIR(sbuf.st_mode)) ? 'd' : '-');
	ft_putchar((sbuf.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((sbuf.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((sbuf.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((sbuf.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((sbuf.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((sbuf.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((sbuf.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((sbuf.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((sbuf.st_mode & S_IXOTH) ? 'x' : '-');
}
