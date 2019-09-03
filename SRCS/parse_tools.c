/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 04:20:14 by brfeltz           #+#    #+#             */
/*   Updated: 2019/09/02 05:12:57 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HEADERS/ft_ls.h"

void	dir_count(t_info *info, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			i++;
		else
		{
			info->dr_count++;
			i++;
		}
	}
}

void	get_dot(t_info *info)
{
	info->dirs[0] = ft_memalloc(sizeof(char) + 1);
	info->dr_count = 1;
	info->dirs[0][0] = '.';
}

void	parse_flags(t_info *info, char **argv)
{
	int i;

	i = 0;
	while (argv[++info->past_flag] && argv[info->past_flag][0] == '-')
	{
		i = 0;
		while (argv[info->past_flag][++i])
		{
			if (argv[info->past_flag][i] == 'l')
				info->flags->l = 1;
			else if (argv[info->past_flag][i] == 't')
				info->flags->t = 1;
			else if (argv[info->past_flag][i] == 'a')
				info->flags->a = 1;
			else if (argv[info->past_flag][i] == 'r')
				info->flags->r = 1;
			else if (argv[info->past_flag][i] == 'R')
				info->flags->c = 1;
			else
			{
				error_check(info, argv, i);
				exit(1);
			}
		}
	}
}

void	zero_out_info(t_info *info)
{
	info->flags->l = 0;
	info->flags->t = 0;
	info->flags->a = 0;
	info->flags->r = 0;
	info->flags->c = 0;
	info->recursive_check = 0;
	info->total_files = 0;
	info->past_flag = 0;
	info->dr_count = 0;
	info->cur_dir = 0;
	info->all_dir_total = NULL;
	info->new_path = NULL;
	info->dirs = NULL;
	info->files = NULL;
	info->path = NULL;
}

void	free_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}
