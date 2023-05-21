/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:41:04 by syoma.k           #+#    #+#             */
/*   Updated: 2023/05/21 20:00:41 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*
*map の解放
*/
void	free_map(char **map)
{
	int	j;

	j = 0;
	while (map[j])
	{
		free(map[j]);
		j++;
	}
	free(map);
}

/*
*リストの解放
@param stack リスト
*/
void	free_stack(t_stack *stack)
{
	t_stack	*tmp;

	while (stack)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
	}
}

/*
・mapのコピー
@param data マップ情報
@returns コピーしたマップのアドレス
*/
char	**copy_map(t_data *data)
{
	char	**c_map;
	int		i;
	int		j;

	j = 0;
	c_map = malloc(sizeof(char *) * (data->row + 1));
	if (!(c_map))
		ft_error(-1);
	while (j < data->row)
	{
		c_map[j] = malloc(sizeof(char) * (data->col + 1));
		if (!(c_map[j]))
			ft_error(-1);
		i = 0;
		while (i < data->col)
		{
			c_map[j][i] = data->map[j][i];
			i++;
		}
		c_map[j][i] = '\0';
		j++;
	}
	c_map[j] = NULL;
	return (c_map);
}
