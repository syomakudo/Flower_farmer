#ifndef MY_MLX_HOOKS_H
# define MY_MLX_HOOKS_H

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define POINTER_MOVE 6
# define DESTROY_NOTIFY 17

# define KEY_PRESS_MASK (1L << 0)
# define KEY_RELEASE_MASK (1L << 1)
# define BUTTON_PRESS_MASK (1L << 2)
# define BUTTON_RELEASE_MASK (1L << 3)
# define POINTER_MOVE_MASK (1L << 6)
# define STRUCTURE_NOTIFY_MASK (1L << 17)
#endif

#include "../minilibx-linux/mlx.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}			t_img;

/*
**col:横のマスの数
**row:縦のマスの数
*/
typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		x_now;
	int		y_now;
	int		x_start;
	int		y_start;
	int		x_goal;
	int		y_goal;
	int		items;
	int		x_max;
	int		y_max;
	int		col;
	int		row;
}			t_data;

/*mapエラーチェック用の構造体*/
typedef struct s_mapcheck
{
	int		count_P;
	int		count_C;
	int		count_E;

}			t_mapcheck;

void		ft_error(int i);

void		make_map(t_data *data, char *file_name);

/*mapエラーチェック用の関数*/
void		check_map(t_data *data);
int			check_count_pce(t_data *data, t_mapcheck *cmap);