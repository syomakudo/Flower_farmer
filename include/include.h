/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:34:01 by syoma.k           #+#    #+#             */
/*   Updated: 2023/05/22 00:59:33 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# define KEY_PRESS 2
# define DESTROY_NOTIFY 17
# define KEY_A 97
# define KEY_D 100
# define KEY_W 119
# define KEY_S 115
# define KEY_ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364
# define IMG_ZERO "./img/kusa.xpm"
# define IMG_WALL "./img/flower.xpm"
# define IMG_ITEM "./img/villain.xpm"
# define IMG_PLAYER "./img/human.xpm"
# define IMG_GOAL "./img/trash.xpm"

# include "../minilibx-linux/mlx.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img
{
	void			*img;
	int				width;
	int				height;
}					t_img;

/*
**col:横のマスの数
**row:縦のマスの数
**map:マップの情報
**x_now:現在のx座標 xは横(row)
**y_now:現在のy座標 yは縦(col)
*/
typedef struct s_data
{
	void			*mlx;
	void			*win;
	char			**map;
	int				x_now;
	int				y_now;
	int				x_start;
	int				y_start;
	int				items;
	int				count;
	int				col;
	int				row;
	t_img			img[5];
}					t_data;

/*mapエラーチェック用の構造体*/
typedef struct s_mapcheck
{
	int				count_p;
	int				count_c;
	int				count_e;

}					t_mapcheck;

typedef struct s_stack
{
	int				x;
	int				y;
	size_t			num_c;
	size_t			num_e;
	struct s_stack	*next;
}					t_stack;

void				ft_error(int num);
void				free_all(t_data *data);
/*map作成*/
t_data				make_map(char *file_name);

/*mapエラーチェック*/
void				check_map(t_data *data);
int					check_count_pce(t_data *data, t_mapcheck *cmap);
int					check_position_pce(t_data *data);

void				free_map(char **map);
void				free_stack(t_stack *stack);
char				**copy_map(t_data *data);

/*map表示*/
void				set_mlx(t_data *data);
int					draw_map(t_data *data);
int					button_event(t_data *data);
int					key_event(int keycode, t_data *data);

#endif