/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skudo <skudo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:41:00 by syoma.k           #+#    #+#             */
/*   Updated: 2023/05/25 13:11:45 by skudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*リストの作成*/
t_stack	*ft_lstnew(int y, int x, size_t num_c, size_t num_e)
{
	t_stack	*result;

	result = malloc(sizeof(t_stack));
	if (!(result))
		ft_error(-1);
	result->x = x;
	result->y = y;
	result->num_c = num_c;
	result->num_e = num_e;
	result->next = NULL;
	return (result);
}

/*map書き込み,リストの追加
*もとの位置をXに変更
*リストを追加
@param data マップ情報
@param stack リスト
*/
t_stack	*change_map(char **c_map, t_stack *stack, int y, int x)
{
	t_stack	*tmp;

	if (c_map[stack->y][stack->x] != 'X')
		c_map[stack->y][stack->x] = 'X';
	tmp = ft_lstnew(y, x, stack->num_c, stack->num_e);
	tmp->next = stack;
	return (tmp);
}

/*C,Eの数をカウント,上下左右のチェック
・現在位置がC,Eだったらカウント
・上下左右が壁でないかチェック
・上下左右が壁でなければリストに追加
・作成したリストのnextに現在のリストを追加
*@returns 作成したリストのアドレス
*/
t_stack	*check_position(char **c_map, t_stack *stack)
{
	if (c_map[stack->y][stack->x] == 'C')
		stack->num_c++;
	if (c_map[stack->y][stack->x] == 'E')
		stack->num_e++;
	if (c_map[stack->y - 1][stack->x] != '1' && c_map[stack->y
		- 1][stack->x] != 'X')
		stack = change_map(c_map, stack, stack->y - 1, stack->x);
	else if (c_map[stack->y + 1][stack->x] != '1' && c_map[stack->y
			+ 1][stack->x] != 'X')
		stack = change_map(c_map, stack, stack->y + 1, stack->x);
	else if (c_map[stack->y][stack->x - 1] != '1' && c_map[stack->y][stack->x
			- 1] != 'X')
		stack = change_map(c_map, stack, stack->y, stack->x - 1);
	else if (c_map[stack->y][stack->x + 1] != '1' && c_map[stack->y][stack->x
			+ 1] != 'X')
		stack = change_map(c_map, stack, stack->y, stack->x + 1);
	return (stack);
}

/*チェックのメイン部分
スタックを使用してマップをチェック
stack->next->num_c = stack->num_c;
stack->next->num_e = stack->num_e;
で次のリストに現在のC,Eの数を渡して情報を引き継いでいる
@param c_map マップ情報
@param stack リストのアドレス
@param tmp リストのアドレス
@returns 作成したリストのアドレス
*/
t_stack	*stack_main(char **c_map, t_stack *stack)
{
	t_stack	*tmp;

	tmp = check_position(c_map, stack);
	if (tmp == stack)
	{
		if (stack->next)
		{
			stack->next->num_c = stack->num_c;
			stack->next->num_e = stack->num_e;
		}
		c_map[stack->y][stack->x] = 'X';
		stack = stack->next;
		free(tmp);
	}
	else
		stack = tmp;
	return (stack);
}

/*P,C,E位置チェック
・Pが全てのCを取得してEまで辿り着けるかのチェック
@returns 0:成功 -1:失敗
*/
int	check_position_pce(t_data *data)
{
	t_stack	*stack;
	char	**c_map;

	c_map = copy_map(data);
	stack = ft_lstnew(data->y_start, data->x_start, 0, 0);
	while (stack)
	{
		stack = stack_main(c_map, stack);
		if (stack && stack->num_c == data->items && stack->num_e == 1)
		{
			free_map(c_map);
			free_stack(stack);
			return (0);
		}
	}
	free_map(c_map);
	return (-1);
}
