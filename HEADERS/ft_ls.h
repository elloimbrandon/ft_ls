/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfeltz <brfeltz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:21:53 by brandonf          #+#    #+#             */
/*   Updated: 2019/09/02 04:58:35 by brfeltz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <inttypes.h>
# include <locale.h>
# include <math.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <stdbool.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <time.h>
# include "../libft/libft.h"

/*
** Structs
*/

typedef struct		s_flags
{
	bool			l;
	bool			t;
	bool			a;
	bool			r;
	bool			c;
}					t_flags;

typedef struct		s_info
{
	t_flags			*flags;
	int				past_flag;
	int				dr_count;
	int				no_arg;
	char			**dirs;
	char			**files;
	char			**path;
	char			**new_path;
	char			*all_dir_total;
	int				total_files;
	int				cur_dir;
	bool			recursive_check;
}					t_info;

/*
** Functions
*/

t_info				*recursive_struct(t_info *info, int i);
void				recursive_check(t_info *info, int argc);
void				build_path(t_info *info);
void				add_stat(t_info *info, int i);
void				print_info(t_info *info, int i);
void				print_time(t_info *info, int i);
void				handle_alpha(t_info *info);
void				handle_t(t_info *info);
void				handle_r(t_info *info);
void				check_dir(t_info *info);
void				check_sort(t_info *info);
void				check_file(t_info *info);
void				ft_store_files(t_info *info, DIR *dir);
void				sort_all(t_info *info, DIR *dir);
void				get_dir(char **ret, int x);
void				print_all(t_info *info);
void				start_ls(t_info *info);
void				zero_out_info(t_info *info);
void				dir_count(t_info *info, char **argv);
void				parse_flags(t_info *info, char **argv);
void				get_dot(t_info *info);
void				ft_ls(t_info *info, int argc);
void				double_swap(char **ptr, int i, int j);
void				free_recur(t_info *recur_path);
void				free_all(t_info *info);
void				free_str(char **str);
long				get_time(char *str1, char *str2);
int					total_file_count(t_info *info);
void				error_check(t_info *info, char **argv, int i);
#endif
