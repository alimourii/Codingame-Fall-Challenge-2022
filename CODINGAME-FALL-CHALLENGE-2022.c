#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct t_cord
{
    int x;
    int y;
    int yes;
}t_cord;

typedef struct t_var
{
    int a;
    int b;
    int c;
    int d;
    int e;
}t_var;

typedef struct t_attac
{
    int front;
    int up;
    int dwon;
    int back;
    int dif_front;
}t_attac;


typedef struct t_map
{
    int scrap_amount;
	int owner;
    int units;
    int recycler;
    int can_build;
    int can_spawn;
    int in_range_of_recycler;

    int opp_robo_in_line;
    int my_robo_in_line;
    int opp_erea_in_line;
    int my_erea_in_line;

    int all_opp_erea;
    int all_my_erea;

    int my_matter;
    int opp_matter;

    int my_side;
    int opp_side;

    int end;
    int star;
    int pas;
    int first_y_dst;
    t_cord my_hom;
    t_cord opp_hom;

    int width;
    int height;

    int add_unit;
    int moved_unit;
    int iter;
    t_attac attac;

    t_var task;
}t_map;

/**
 * printf("SPAWN 1 %d %d;", hel.y, hel.x);
 * printf("MOVE %d %d %d %d %d;", map[i][j].units, j, i, l, k);
 * printf("BUILD %d %d;", j, i);
 * printf("MESSAGE %d %d;", hel.y, hel.x);
 *
 *
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 /**************************************** FUNCTIONS ************************************/
 int    ft_cord_ok(t_map **map, int x, int y);/*                                        */
 t_map **ft_move(t_map **map, int amount, int fromX, int fromY, int toX, int toY);/*_0  */
 t_map **ft_build(t_map **map, int X, int Y);/*                                         */
 t_map **ft_spawn(t_map **map, int amount, int X, int Y);/*                             */
 int ft_dst_from_first_opp_erea_0_uni_1(t_map **map, int X, int Y, int erea_0_uni_1);/* */
 int ft_my_til_in_front(t_map **map, int X, int Y);/*_2                                 */
 int ft_dst_with_next_grass(t_map **map, int X, int Y);/*_3                             */
 t_map **ft_go_to_end(t_map **map);/*_4                                                 */
 t_map **ft_line_attac(t_map **map);/*_5                                                */
 t_map **ft_build_carefly_my_side(t_map **map);/*_6.                                    */
 int  ft_dst_obstakl(t_map **map, int X, int Y);/*_7                                    */
 int  ft_is_rot_clean_to_midl(t_map **map, int X, int Y);/*_8                           */
 int  ft_is_clean_to_up_down(t_map **map, int X, int Y, int up_down);/*_9               */
 t_cord  ft_get_cord_up_dwon(t_map **map, int up_or_down);/*_10                         */
 t_map  **ft_sad_lfjwa(t_map **map);/*_11                                               */
 t_map  **ft_get_all_attacks(t_map **map);/*_12                                         */
 /***************************************************************************************/
t_map **ft_full_sides(t_map **map, int width, int height, int sido)
{
     for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
            if (sido)
            {
                map[i][j].my_side = (j >= width / 2);
                map[i][j].opp_side = !(j >= width / 2);
            }
            if (!sido)
            {
                map[i][j].my_side = !(j > width / 2);
                map[i][j].opp_side = (j > width / 2);
            }
     }}
     return (map);
}
/***************************************************************************************/
int ft_cord_ok(t_map **map, int x, int y)
{
    if (x >= 0 && x < map[0][0].height && y >= 0 && y < map[0][0].width)
    {
        return (1);
    }
    return (0);
}
/***************************************************************************************/
double ft_vitagors_dst(t_map **map, int x1, int y1, int x2, int y2)
{
    if (ft_cord_ok(map, x1, y1) && ft_cord_ok(map, x2, y2))
    {
        return (sqrt((double)((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))));
    }
    return (-1);
}
/************************************************************* ALL ACTION_FUNCTION_0 ****************************************************************/
t_map **ft_move(t_map **map, int amount, int fromX, int fromY, int toX, int toY)
{
    if ((map[fromX][fromY].units - map[fromX][fromY].moved_unit) >= amount && amount)
    {
        printf("MOVE %d %d %d %d %d;", amount, fromY, fromX, toY, toX);
        map[fromX][fromY].moved_unit += amount;
        if (abs(fromY - toY) == 1 || abs(fromX - toX) == 1)
        {
            map[toX][toY].add_unit += amount;
        }
    }
    return (map);
}

t_map **ft_build(t_map **map, int X, int Y)
{
    if (map[0][0].my_matter >= 10)
    {
        printf("BUILD %d %d;", Y, X);
        map[X][Y].recycler = 1;
        map[0][0].my_matter -= 10;
    }
    
    return (map);
}

t_map **ft_spawn(t_map **map, int amount, int X, int Y)
{

    if (map[0][0].my_matter >= (10 * amount) && map[X][Y].recycler == 0)
    {
        printf("SPAWN %d %d %d;",amount, Y, X);
        map[X][Y].add_unit += amount;
        map[0][0].my_matter -= (10 * amount);
    }

    return (map);
}

/*----------------------------------------------------------------------- end_0 ---------------------------------------------------------------------------*/
/************************************************************* DESTNACE_FUNCTION_1 ****************************************************************/
int ft_dst_from_first_opp_erea_0_uni_1(t_map **map, int X, int Y, int erea_0_uni_1)
{
    int dst_erea_uni = -1;
    int dst_uni = -1;
    int pas = map[0][0].pas;
    for(int j = Y; j != map[0][0].end + pas; j += pas)
    {
        if (map[X][j].owner == 0 && map[X][j].units == 0 && erea_0_uni_1 == 0)
        {
            dst_erea_uni = abs(Y - j);
            break;
        }
        if (map[X][j].owner == 0 && map[X][j].units && erea_0_uni_1 == 1)
        {
            dst_erea_uni = abs(Y - j);
            break;
        }
    }
    return (dst_erea_uni - 1);
}

/*----------------------------------------------------------------------- end_1 ---------------------------------------------------------------------------*/
/************************************************************* TILE_IN_THE_FRONT_FUNCTION_2 ****************************************************************/
int ft_my_til_in_front(t_map **map, int X, int Y)
{
    
    int pas = map[0][0].pas;
    if ((Y != 0 || pas > 0) && (Y != map[0][0].width || pas < 0) && map[X][Y].owner == 1)
    {
        for(int j = Y + pas; j != map[0][0].end + pas; j += pas)
        {
        if (map[X][j].owner == 1)
        return (0);
        }
    }
    else
        return (0);
    return (1);
}

/*----------------------------------------------------------------------- end_2 ---------------------------------------------------------------------------*/
/************************************************************* TILE_CLOSET_GRAS_IN_LINE_FUNCTION_3 ****************************************************************/
int ft_dst_with_next_grass(t_map **map, int X, int Y)
{
    
    int pas = map[0][0].pas;
    if ((Y != 0 || pas > 0) && (Y != map[0][0].width || pas < 0))
    {
        for(int j = Y + pas; j != map[0][0].end + pas; j += pas)
        {
        if (map[X][j].scrap_amount == 0)
            return (abs(Y - j) - 1);
        }
    }
    return (-1);
}

/*---------------------------------------------------------------------------- end_3 -------------------------------------------------------------------------*/
/******************************************************************** GO_TO_END_STEP_BY_STEP_4 ****************************************************************/
t_map **ft_go_to_end(t_map **map)
{
    int pas = map[0][0].pas;
    for(int x = 0; x < map[0][0].height; x++)
    {
        for( int y = 0; y < map[0][0].width; y++)
        {
            if (map[x][y].units && map[x][y].owner == 1 && y != map[0][0].end)
            {
                if ((ft_dst_from_first_opp_erea_0_uni_1(map, x, y, 1) > 0) || (map[x][0].opp_robo_in_line == 0))
                {
                    if (ft_dst_obstakl(map, x, y) > 2)
                    {
                        map = ft_move(map, map[x][y].units - map[x][y].moved_unit, x, y, x, y + pas);
                    }
                    else
                    {
                        map = ft_move(map, map[x][y].units - map[x][y].moved_unit, x, y, x, map[0][0].end);
                    }
                }
                    
            }
        }}
    return (map);
}

/*------------------------------------------------------------------------- end_4 ---------------------------------------------------------------------------*/
/********************************************************************* FT_LINE_ATTAC_5 *********************************************************************/
t_map **ft_line_attac(t_map **map)
{
    int pas = map[0][0].pas;
    for(int i = 0; i < map[0][0].height - 1; i++)
    {
        if (map[i][0].opp_robo_in_line && map[i][0].my_erea_in_line == 0 && map[i + 1][0].my_erea_in_line)
        {
            for(int j = 0; j < map[0][0].width; j++)
            {
                if (ft_my_til_in_front(map, i + 1, j) && ft_is_clean_to_up_down(map, i, j, 1))
                {
                    if (map[i + 1][j].units < 2)
                        map = ft_spawn(map, 1, i + 1, j);
                    if (map[i + 1][j].units)
                        map = ft_move(map, 1, i + 1, j, i, j);

                }
            }
        }
    }

    for(int i = map[0][0].height - 1; i > 0; i--)
    {
        if (map[i][0].opp_robo_in_line && map[i][0].my_erea_in_line == 0 && map[i - 1][0].my_erea_in_line)
        {
            for(int j = 0; j < map[0][0].width; j++)
            {
                if (ft_my_til_in_front(map, i - 1, j) && ft_is_clean_to_up_down(map, i, j, 0))
                {
                    if (map[i - 1][j].units < 2)
                        map = ft_spawn(map, 1, i - 1, j);
                    if (map[i - 1][j].units)
                        map = ft_move(map, 1, i - 1, j, i, j);

                }
            }
        }
    }
    return (map);
}

/*----------------------------------------------------------------------------------- end_5 --------------------------------------------------------------------------------*/
/***************************************************************************** FT_BUILD_CAREFLY_IN_MY_SIDE_6 ****************************************************************/
t_map **ft_build_carefly_my_side(t_map **map)
{
    t_var p = {-1,-1,-1,-1,-1};
    t_cord bl = {-1,-1,-1};
    int scrp = 0;

    int pas = map[0][0].pas;

    for(int i = 0; i < map[0][0].height; i++)
    {
        for(int j = map[0][0].star; j != map[0][0].end + pas; j += pas)
        {
            if (map[i][j].owner == 1 && map[i][j].units == 0 && map[i][j].recycler == 0 && (j >= map[0][0].my_hom.y || pas < 0) && (j <= map[0][0].my_hom.y || pas > 0))
            {
                if (j > 0)
                    p.a = map[i][j - 1].scrap_amount + 10 * (map[i][j - 1].scrap_amount == 0);

                if (j < map[0][0].width - 1)
                    p.b = map[i][j + 1].scrap_amount + 10 * (map[i][j + 1].scrap_amount == 0);

                if (i > 0)
                    p.c = map[i - 1][j].scrap_amount + 10 * (map[i - 1][j].scrap_amount == 0);

                if (i < map[0][0].height - 1)
                    p.d = map[i + 1][j].scrap_amount + 10 * (map[i + 1][j].scrap_amount == 0);

                if (p.a != -1 && p.b != -1 && p.c != -1 && p.c != -1 && map[i][j].scrap_amount < p.a && map[i][j].scrap_amount < p.b
                    && map[i][j].scrap_amount < p.c && map[i][j].scrap_amount < p.d && map[i][j].scrap_amount > scrp && map[i][j].scrap_amount > 1)
                {
                    map[i][j].scrap_amount = map[i][j].scrap_amount;
                    bl.x = i;
                    bl.y = j;
                }
            }
        }
    }
    if (bl.x != -1 && bl.y != -1)
    {
        map = ft_build(map, bl.x, bl.y);
    }
    return (map);
}

/*--------------------------------------------------------------------------------------- end_6 --------------------------------------------------------------------------------*/
/*************************************************************************** DSTANC_BITWEEN_MY_ROBO_AND_ABSTAKL_7****************************************************************/
int  ft_dst_obstakl(t_map **map, int X, int Y)
{

    int pas = map[0][0].pas;
    for(int j = Y; j != map[0][0].end + pas; j += pas)
    {
        if (map[X][j].scrap_amount == 0 || map[X][j].recycler == 1)
        {
            return (abs(Y - j) - 1);
            break;
        }
        
    }
    return (abs(Y - map[0][0].end) - 1);
}

/*---------------------------------------------------------------------------------------- end_7 ---------------------------------------------------------------------------------*/
/*************************************************************************** FT_IS_IT_CLEAN_TO_MIDEL_8****************************************************************/
int  ft_is_rot_clean_to_midl(t_map **map, int X, int Y)
{

    int pas = map[0][0].pas;
    int midle = (map[0][0].width - 1) / 2 + pas;
    if (map[X][Y].my_side == 1)
    {
        for(int j = Y; j != midle + pas; j += pas)
        {
            if (map[X][j].scrap_amount == 0 || map[X][j].recycler == 1)
            {
                return (0);
            }
            
        }
    }
    return (1);
}

/*---------------------------------------------------------------------------------------- end_8 ---------------------------------------------------------------------------------*/
/*************************************************************************** FT_IS_CLEAN_TO_UP_TO_DOWN_9****************************************************************/
int  ft_is_clean_to_up_down(t_map **map, int X, int Y, int up_down)
{
    
    int pas = map[0][0].pas;
    if (up_down == 1)
    {
        for(int i = X; i >= 0; i--)
        {
            if (map[i][Y].scrap_amount == 0)
                return (0);
            if (ft_is_rot_clean_to_midl(map, i, Y))
            {
                return (1);
            }
            
        }
        return (0);
    }
    if (up_down == 0 )
    {
        for(int i = X; i < map[0][0].height; i++)
        {
            if (map[i][Y].scrap_amount == 0)
                return (0);
            if (ft_is_rot_clean_to_midl(map, i, Y))
            {
                return (1);
            }
            
        }
        return (0);
    }
    return (0);
}

/*---------------------------------------------------------------------------------------- end_9 ---------------------------------------------------------------------------------*/
/******************************************************************************** FT_ONE_TO_UP_ONE_TO_DOWN_10 *********************************************************************/
t_cord  ft_get_cord_up_dwon(t_map **map, int up_or_down)
{
    int pas = map[0][0].pas;
    int w = map[0][0].width;
    int h = map[0][0].height;
    int star = map[0][0].star;
    int end = map[0][0].end;
    t_cord p = {-1,-1,0};

    if (up_or_down == 1)
    {
        for(int i = 0; i < h; i++){
            for(int j = end; j != star - pas; j -= pas)
            {
                if (map[i][j].units && map[i][j].owner == 1)
                {
                    p.x = i;
                    p.y = j;
                    p.yes = 1;
                    return (p);
                }
            }
        }
    }
        if (up_or_down == 0)
    {
        for(int i = h - 1; i >= 0; i--){
            for(int j = end; j != star - pas; j -= pas)
            {
                if (map[i][j].units && map[i][j].owner == 1)
                {
                    p.x = i;
                    p.y = j;
                    p.yes = 1;
                    return (p);
                }
            }
        }
    }
    
    return (p);
}

t_map  **ft_one_to_up_one_down(t_map **map)
{
    t_cord to_up = ft_get_cord_up_dwon(map, 1);
    if (to_up.x > 0 && to_up.x != -1 && to_up.yes)
    {
        if (map[to_up.x - 1][to_up.y].scrap_amount && map[to_up.x - 1][to_up.y].recycler == 0 && ft_is_clean_to_up_down(map, to_up.x - 1, to_up.y, 1))
        {
            map = ft_move(map, 1, to_up.x, to_up.y, to_up.x - 1, to_up.y);
            if (ft_is_rot_clean_to_midl(map, to_up.x, to_up.y))
            {
                map = ft_spawn(map, 1, to_up.x, to_up.y);
            }
        }
    }

    t_cord to_dwon = ft_get_cord_up_dwon(map, 0);
    if (to_dwon.x < map[0][0].height - 1 && to_dwon.x != -1 && to_dwon.yes)
    {
        if (map[to_dwon.x + 1][to_dwon.y].scrap_amount && map[to_dwon.x + 1][to_dwon.y].recycler == 0 && ft_is_clean_to_up_down(map, to_dwon.x + 1, to_dwon.y, 0))
        {
            
            map = ft_move(map, 1, to_dwon.x, to_dwon.y, to_dwon.x + 1, to_dwon.y);
            if (ft_is_rot_clean_to_midl(map, to_dwon.x, to_dwon.y))
            {
                map = ft_spawn(map, 1, to_dwon.x, to_dwon.y);
            }
        }
    }
    
    return (map);
}

/*---------------------------------------------------------------------------------------- end_10 ---------------------------------------------------------------------------------*/

/*********************************************************************************** FT_CLOSE_THE_HOLE_11***************************************************************************/
t_map  **ft_sad_lfjwa(t_map **map)
{

    int pas = map[0][0].pas;
    for(int j = map[0][0].end; j != map[0][0].star + pas; j -= pas)
    {
        for(int i = 1; i < map[0][0].height - 1; i++)
        {
            if (map[i][j].scrap_amount == 0 && ft_is_rot_clean_to_midl(map, i, j + pas) && map[i][0].my_robo_in_line == 0 && map[i][j].my_side)
            {
                if (map[i][j + pas].owner != 1 && map[i][j].add_unit == 0)
                {
                    if (map[i + 1][j + pas].owner == 1 && map[i + 1][j + pas].recycler == 0 && map[i][j + pas].scrap_amount)
                    {
                        map = ft_spawn(map, 1, i + 1, j + pas);
                        map = ft_move(map, 1, i + 1, j + pas, i, j + pas);
                    }
                    else if (map[i - 1][j + pas].owner == 1 && map[i - 1][j + pas].recycler == 0 && map[i][j + pas].scrap_amount)
                    {
                        map = ft_spawn(map, 1, i - 1, j + pas);
                        map = ft_move(map, 1, i - 1, j + pas, i, j + pas);
                    }
                }
            }
            if (map[i][0].my_robo_in_line == 0 && map[i][0].opp_robo_in_line && map[i][j].owner == 1 && ft_dst_obstakl(map, i, j) > 2 && ft_my_til_in_front(map, i, j) && map[i][j + pas].owner != 0)
            {
                map = ft_spawn(map, 1, i, j);
            }
        }
    }
    return (map);
}

/*---------------------------------------------------------------------------------------- end_11 -----------------------------------------------------------------------------------*/
/*********************************************************************************** FT_GET_ALL_ATTACK_12***************************************************************************/
t_map  **ft_get_all_attacks(t_map **map)
{
    int pas = map[0][0].pas;
    for(int i = 0; i < map[0][0].height; i++)
    {
        for(int j = map[0][0].star; j != map[0][0].end + pas; j += pas)
        {
            if (map[i][j].owner == 1)
            {
                if (ft_cord_ok(map, i, j + pas) && map[i][j + pas].owner == 0)
                {
                    map[i][j].attac.front = map[i][j + pas].units * (map[i][j + pas].owner == 0);
                    map[i][j].attac.dif_front = map[i][j].units - map[i][j + pas].units;
                }
                if (ft_cord_ok(map, i + 1, j))
                {
                    map[i][j].attac.dwon = map[i + 1][j].units * (map[i + 1][j].owner == 0);
                }
                if (ft_cord_ok(map, i - 1, j))
                {
                    map[i][j].attac.up = map[i - 1][j].units * (map[i - 1][j].owner == 0);
                }
                if (ft_cord_ok(map, i, j - pas))
                {
                    map[i][j].attac.back = map[i][j - pas].units * (map[i][j - pas].owner == 0);
                }
            }
        }
    }
   
    return (map);
}

/*---------------------------------------------------------------------------------------- end_12 -----------------------------------------------------------------------------------*/
/*********************************************************************************** FT_GET_ALL_ATTACK_13***************************************************************************/
t_map  **ft_go_to_close_nutr(t_map **map)
{
    int width = map[0][0].width;
    int height = map[0][0].height;

    int pas = map[0][0].pas;

    for(int j = map[0][0].star; j != map[0][0].end; j += pas)
    {
        for(int i = 0; i < map[0][0].height; i++)
        {
            if (map[i][j].owner == 1 && map[i][j].recycler == 0)
            {
                if (j + 1 < width &&  map[i][j + 1].scrap_amount && map[i][j + 1].owner == -1)
                {
                    if (map[i][j].units == 0)
                        map = ft_spawn(map, 1, i, j);
                    map = ft_move(map, 1, i, j, i, j + 1);
                }
                else if (j > 0 && map[i][j - 1].scrap_amount && map[i][j - 1].owner == -1)
                {
                    if (map[i][j].units == 0)
                        map = ft_spawn(map, 1, i, j);
                    map = ft_move(map, 1, i, j, i, j - 1);
                }
                else if (i + 1 < height && map[i + 1][j].scrap_amount && map[i + 1][j].owner == -1)
                {
                    if (map[i][j].units == 0)
                        map = ft_spawn(map, 1, i, j);
                    map = ft_move(map, 1, i, j, i + 1, j);
                }
                else if (i > 0 && map[i - 1][j].scrap_amount && map[i - 1][j].owner == -1)
                {
                    if (map[i][j].units == 0)
                        map = ft_spawn(map, 1, i, j);
                    map = ft_move(map, 1, i, j, i - 1, j);
                }
            }
        }
    }
    return (map);
}

/*---------------------------------------------------------------------------------------- end_13 -----------------------------------------------------------------------------------*/
/*********************************************************************************** FT_GET_ALL_ATTACK_13***************************************************************************/
t_map  **ft_back_robo_go_nutr(t_map **map)
{
    int width = map[0][0].width;
    int height = map[0][0].height;

    int pas = map[0][0].pas;

    for(int j = map[0][0].star; j != map[0][0].end + pas; j += pas)
    {
        for(int i = 0; i < map[0][0].height; i++)
        {
            if (map[i][j].owner == 1 && map[i][j].units)
            {
                if (ft_cord_ok(map, i, j - pas) &&  map[i][j - pas].scrap_amount && map[i][j - pas].owner == -1)
                {
                    map = ft_move(map, 1, i, j, i, j - pas);
                    return (map);
                }
                else if (ft_cord_ok(map, i + 1, j) && map[i + 1][j].scrap_amount && map[i + 1][j].owner == -1)
                {
                    map = ft_move(map, 1, i, j, i + 1, j);
                    return (map);
                }
                else if (ft_cord_ok(map, i - 1, j) && map[i - 1][j].scrap_amount && map[i - 1][j].owner == -1)
                {
                    map = ft_move(map, 1, i, j, i - 1, j);
                    return (map);
                }
                else if (ft_cord_ok(map, i, j + pas) && map[i][j + pas].scrap_amount && map[i][j + pas].owner == -1)
                {
                    map = ft_move(map, 1, i, j, i, j + pas);
                    return (map);
                }
            }
        }
    }
    return (map);
}

/*---------------------------------------------------------------------------------------- end_13 -----------------------------------------------------------------------------------*/
/*********************************************************************************** FT_GET_ALL_ATTACK_14***************************************************************************/
t_map  **ft_attack(t_map **map)
{
    int pas = map[0][0].pas;

    for(int j = map[0][0].star; j != map[0][0].end; j += pas)
    {
        for(int i = 0; i < map[0][0].height; i++)
        {

            if (map[i][j].owner == 1)
            {
                if (map[i][j + pas].owner == 0 && map[i][j].can_build && map[i][j + pas].units && map[i][j + pas].opp_side)
                {
                    map = ft_build(map, i, j);
                }
                if (map[i][j].attac.dif_front < -2)
                {
                    map = ft_build(map, i, j);
                }
                if (map[i][j].attac.dif_front < 0)
                {
                    map = ft_spawn(map, abs(map[i][j].attac.dif_front), i, j);
                }
                if (map[i][j].attac.dif_front > 0)
                {
                    map = ft_move(map, 1, i, j, i, j + pas);
                }
                if (map[i][j].attac.back)
                {
                    if (map[i][j].units == 0)
                        map = ft_spawn(map, 1, i, j);
                    map = ft_move(map, 1, i, j, i, j - pas);
                }
            }
                
        }
    }

    return (map);
}
/**********************************/
/*********************************************************************************** FT_GET_ALL_ATTACK_15***************************************************************************/
t_map  **ft_back_robo_go_nutr_opp_side(t_map **map)
{
    int width = map[0][0].width;
    int height = map[0][0].height;

    int pas = map[0][0].pas;
    //printf("MESSAGE  +//;"); /*######## message #######*/
    for(int j = map[0][0].star; j != map[0][0].end + pas; j += pas)
    {
        for(int i = 0; i < map[0][0].height; i++)
        {
            if (map[i][j].owner == 1 && map[i][j].units && map[i][j].opp_side)
            {
                //printf("MESSAGE  &_%d_&_%d;",j ,i); /*######## message #######*/
                
                if (ft_cord_ok(map, i + 1, j) && map[i + 1][j].scrap_amount && map[i + 1][j].owner == -1)
                {
                    map = ft_move(map, 1, i, j, i + 1, j);
                }
                else if (ft_cord_ok(map, i - 1, j) && map[i - 1][j].scrap_amount && map[i - 1][j].owner == -1)
                {
                    map = ft_move(map, 1, i, j, i - 1, j);
                }
                else if (ft_cord_ok(map, i, j + pas) && map[i][j + pas].scrap_amount && map[i][j + pas].owner == -1)
                {
                    map = ft_move(map, 1, i, j, i, j + pas);
                }
                else  if (ft_cord_ok(map, i, j - pas) &&  map[i][j - pas].scrap_amount && map[i][j - pas].owner == -1)
                {
                    map = ft_move(map, 1, i, j, i, j - pas);
                }
            }
        }
    }
    //printf("MESSAGE  //;"); /*######## message #######*/
    return (map);
}

/*---------------------------------------------------------------------------------------- end_15 -----------------------------------------------------------------------------------*/
/*********************************************************** FT_ATTAC_HELP ********************************************************************/

int  ft_how_many_attac(t_map **map, int width, int height)
{
    int how_attac = 0;
    int pas = map[0][0].pas;

    for (int i = 0; i < height; i++) {
    for (int j = 1; j < width; j++) {
            
          if (map[i][j].owner == 1 && map[i][j + pas].owner == 0 && map[i][j + pas].units && map[i][j].recycler == 0)
            how_attac++;
           
     }}
    return (how_attac);

}
/***********************/

int  ft_build_help(t_map **map, int width, int height)
{
    int how_attac = 0;
    int pas = map[0][0].pas;
    int one_3 = (width / 3) * (map[0][0].star == 0) +  2 * (width / 3) * (map[0][0].star == width); /*55555555555555555555555555555555555555555555555555555555555555555555555555555555555555*/

    for (int i = 0; i < height; i++) {
    for (int j = 1; j < width; j++) {
            
          if (j == one_3 && map[0][0].my_matter < 20 && ft_how_many_attac(map, width, height) == 0)
          {
            if (map[i][j].owner == 1 && map[i][j].units == 0 && map[0][0].my_matter >= 10)
            {
                printf("BUILD %d %d;", j, i);
                map[0][0].my_matter -= 10;
                //printf("MESSAGE  ft_build_help;"); /*######## message #######*/
            }
          }
           
     }}
    return (how_attac);

}
/****************************************************************************************************************************************************/
void ft_attacko(t_map **map, int width, int height)
{

    t_cord t1;
    int pas = map[0][0].pas;
    //printf("MESSAGE attc_big ;"); /*######## message #######*/

    ft_build_help(map, width, height);
    map  = ft_back_robo_go_nutr_opp_side(map);
        for (int j = map[0][0].star; j != map[0][0].end; j += pas) {
             for (int i = 0; i < height; i++) {

        if (ft_cord_ok(map, i + 1,j) && map[i][j].owner == 1 && map[i][j].can_build)
        {
            if (map[i + 1][j].units && map[i + 1][j].owner == 0)
                map = ft_build(map, i, j);
        }
        if (ft_cord_ok(map, i - 1,j) && map[i][j].owner == 1 && map[i][j].can_build)
        {
            if (map[i - 1][j].units && map[i - 1][j].owner == 0)
                map = ft_build(map, i, j);
        }

        if (ft_cord_ok(map, i + 1, j + pas) && ft_cord_ok(map, i - 1, j + pas) && map[i][j].owner == 1 && map[i][j].units && map[i][j].attac.front == 0)
        {
            if (map[i + 1][j + pas].owner == 0 && map[i + 1][j + pas].units && map[i + 1][j].scrap_amount && map[i + 1][j].recycler == 0)
            {
                map = ft_move(map, 1, i, j, i + 1, j);
            }
            if (map[i - 1][j + pas].owner == 0 && map[i - 1][j + pas].units && map[i - 1][j].scrap_amount && map[i - 1][j].recycler == 0)
            {
                map = ft_move(map, 1, i, j, i - 1, j);
            }
        }

        
        if (ft_cord_ok(map, i + 1,j) && map[i][j].owner == 1 && map[i][j].can_build)
        {
            if (map[i + 1][j].units && map[i + 1][j].owner == 0)
                map = ft_build(map, i, j);
        }
        if (ft_cord_ok(map, i - 1,j) && map[i][j].owner == 1 && map[i][j].can_build)
        {
            if (map[i - 1][j].units && map[i - 1][j].owner == 0)
                map = ft_build(map, i, j);
        }

        if (map[i][j].owner == 1 && map[i][j].can_build && map[i][j + pas].owner == 0 && map[0][0].my_matter >= 10 && map[i][j + pas].recycler == 0 && map[i][j + pas].units) 
        {
                if (map[i][j + pas].units + map[i][j + 2 * pas].units > ((width < 16)) * (ft_how_many_attac(map, width, height) < map[0][0].my_matter / 10))    /*  hhhhhhhjhjhhHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH.     */
                {
                        printf("BUILD %d %d;", j, i);
                        map[0][0].my_matter -= 10;
                    
                }
                else if (map[i][j + pas].units == 1)
                {
                    if (map[0][0].my_matter >= 20)
                    {
                        printf("SPAWN %d %d %d;", 2, j, i);
                        map[0][0].my_matter -= 20;
                    }
                    else
                    {
                        printf("SPAWN %d %d %d;", 1, j, i);
                        map[0][0].my_matter -= 10;
                    }
                }
                //printf("MESSAGE attc_0 ;"); /*######## message #######*/
                
        }
    }}

    //ft_attac_brage(map, width, height);

    for (int j = map[0][0].star; j != map[0][0].end; j += pas) {
             for (int i = 0; i < height; i++) {
            
            // if (map[i][j].owner == 1 && map[i][j].units && map[i][j - 2 * pas].opp_side )
            // {
            //     ft_close_nutre_area(map, width, height, i, j);
            //    // printf("MESSAGE attc_1 ;"); /*######## message #######*/
            // }


            if (map[i][j].units && map[i][j].owner == 1 && map[i][j + pas].owner == 0 && map[i][j].units > map[i][j + pas].units) /* ########  nes_by_nes ####### */
            {
                if (i + 1 < height && i > 0 && map[i][j + pas].units == 0 && (map[i + 1][j].owner != 1 || map[i - 1][j].owner != 1))
                {
                    if (map[i + 1][j].owner != 1 && map[i + 1][j].scrap_amount)
                        printf("MOVE %d %d %d %d %d;", 1 , j, i, j, i + 1);
                    else if (map[i - 1][j].owner != 1 && map[i - 1][j].scrap_amount)
                        printf("MOVE %d %d %d %d %d;", 1 , j, i, j, i - 1);
                }
               // printf("MESSAGE attc_3 ;"); /*######## message #######*/
            }

            if (map[i][j].owner == 1 && map[i][j + pas].owner == 0 && map[i][j].recycler == 0 && map[i][j + pas].recycler == 0) // for opp_units attac
            {
                    if ((map[0][0].my_matter / 10 > (map[i][j + pas].units + 1 - map[i][j].units)) && map[i][j + pas].units > map[i][j].units)// error hase to fixed
                    {
                        printf("SPAWN %d %d %d;", map[i][j + pas].units + 1 - map[i][j].units, j, i);
                        map[0][0].my_matter -= map[i][j + pas].units + 1 - map[i][j].units;
                        printf("MOVE %d %d %d %d %d;", map[i][j].units , j, i, j + pas, i);
                    }
                    else if (2 * map[i][j + pas].units < map[i][j].units)
                    {
                        printf("MOVE %d %d %d %d %d;", map[i][j].units / 2 + 1 , j, i, j + pas, i);
                    }
                    else if (map[i][j + pas].units < map[i][j].units)
                    {
                        printf("MOVE %d %d %d %d %d;",  map[i][j].units - map[i][j + pas].units, j, i, j + pas, i);
                    }
                    else if(map[i][j + pas].units == map[i][j].units && map[0][0].my_matter >= 10)
                    {
                        printf("SPAWN %d %d %d;", 1, j, i);
                        map[0][0].my_matter -= 10;
                        printf("MOVE %d %d %d %d %d;", 1 , j, i, j + pas, i);
                    }
                
              //  printf("MESSAGE attc_4 ;"); /*######## message #######*/    
            }

             if (map[i][j].can_build && map[i][j + pas].units && !map[i][j + pas].owner && map[i][j + pas].opp_side) /* -  && map[i][j].recycler == 0 */
            {
                

                if (map[0][0].my_matter >= 10)
                {
                    printf("BUILD %d %d;", j, i);
                    printf("MESSAGE build %d %d;", j, i); /*######## message #######*/
                    map[0][0].my_matter -= 10;
                }
               // printf("MESSAGE attc_5 ;"); /*######## message #######*/
            }


          if (map[i][j].scrap_amount && map[i][j].owner == -1 && map[i][j + pas].owner == 0 && map[i][j + pas].my_side) // error mokin cause j + pas get more lins erea
          {
                if (i + 1 < height && map[i + 1][j].owner == 1 && map[i + 1][j].my_robo_in_line == 0 && map[0][0].my_matter >= 10 && (map[i + 1][j + pas].units < map[i + 1][j].units || map[i + 1][j + pas].owner != 0))
                {
                    printf("MOVE %d %d %d %d %d;", 1, j, i + 1, j, i);
                    printf("SPAWN 1 %d %d;", j, i + 1);
                    map[0][0].my_matter -= 10;
                }
                if (i  > 0 && map[i - 1][j].owner == 1 && map[i - 1][j].my_robo_in_line == 0 && map[0][0].my_matter >= 10 && (map[i - 1][j + pas].units < map[i - 1][j].units || map[i - 1][j + pas].owner != 0))
                {
                    printf("MOVE %d %d %d %d %d;", 1, j, i - 1, j, i);
                    printf("SPAWN 1 %d %d;", j, i - 1);
                    map[0][0].my_matter -= 10;
                }
           // printf("MESSAGE attc_6 ;"); /*######## message #######*/
          }
         
        //   if (map[i][j].owner == 1 && map[i][j + pas].owner == 0 && !map[i][j + pas].units && map[i][j + pas].recycler == 0) // for opp_units attac
        //   {
        //         if (map[i][j].units)
        //         {
        //             printf("MOVE %d %d %d %d %d;", map[i][j].units, j, i, j + pas, i);
        //         }
        //         else if (map[0][0].my_matter >= 10)
        //         {
        //             printf("SPAWN %d %d %d;", 1, j, i);
        //             map[0][0].my_matter -= 10;
        //         }
        //         //printf("MESSAGE attc_7 ;"); /*######## message #######*/
        //   }
        //   if ( map[i][0].my_robo_in_line == 0 && map[i][j].owner == 1 && map[i][j + pas].owner != 1 && map[i][0].opp_robo_in_line && map[i][j + pas].scrap_amount) // for spawn new robo in emty line
        //   {
        //         if (map[0][0].my_matter >= 10 && map[i][j].recycler == 0)
        //         {
        //             printf("SPAWN %d %d %d;", 1, j, i);
        //             map[0][0].my_matter -= 10;
        //         }
        //         //printf("MESSAGE attc_8 ;"); /*######## message #######*/
        //   }

     }}
   // printf("MESSAGE attc_end ;"); /*######## message #######*/
}


/************************************************************************************************************************************/
/*---------------------------------------------------------------------------------------- end_14 -----------------------------------------------------------------------------------*/

 /**************************************** FUNCTIONS ************************************/
 int    ft_cord_ok(t_map **map, int x, int y);/*                                        */
 t_map **ft_move(t_map **map, int amount, int fromX, int fromY, int toX, int toY);/*_0  */
 t_map **ft_build(t_map **map, int X, int Y);/*                                         */
 t_map **ft_spawn(t_map **map, int amount, int X, int Y);/*                             */
 int ft_dst_from_first_opp_erea_0_uni_1(t_map **map, int X, int Y, int erea_0_uni_1);/* */
 int ft_my_til_in_front(t_map **map, int X, int Y);/*_2                                 */
 int ft_dst_with_next_grass(t_map **map, int X, int Y);/*_3                             */
 t_map **ft_go_to_end(t_map **map);/*_4                                                 */
 t_map **ft_line_attac(t_map **map);/*_5                                                */
 t_map **ft_build_carefly_my_side(t_map **map);/*_6.                                    */
 int  ft_dst_obstakl(t_map **map, int X, int Y);/*_7                                    */
 int  ft_is_rot_clean_to_midl(t_map **map, int X, int Y);/*_8                           */
 int  ft_is_clean_to_up_down(t_map **map, int X, int Y, int up_down);/*_9               */
 t_cord  ft_get_cord_up_dwon(t_map **map, int up_or_down);/*_10                         */
 t_map  **ft_sad_lfjwa(t_map **map);/*_11                                               */
 t_map  **ft_get_all_attacks(t_map **map);/*_12                                         */
 /***************************************************************************************/

/*################################################################################################################################################################################*/
/*#*/int main()/*                                                                                                                                                               ##*/
/*#*/{/*                                                                                                                                                                        ##*/
/*#*/    int width;/*                                                                                                                                                           ##*/
/*#*/    int height;/*                                                                                                                                                          ##*/
/*#*/    scanf("%d%d", &width, &height);/*                                                                                                                                      ##*/
/*#*//*                                                                                                                                                                         ##*/
/*#*/    t_map **map;/*                                                                                                                                                         ##*/
/*#*//*                                                                                                                                                                         ##*/
/*#*/    map = (t_map **)malloc(sizeof(t_map *) * height);/*                                                                                                                    ##*/
/*#*/    int iter = 0;/*                                                                                                                                                        ##*/
/*#*/    int star;/*                                                                                                                                                            ##*/
/*#*/    int end;/*                                                                                                                                                             ##*/
/*#*/    int pas;/*                                                                                                                                                             ##*/
/*#*/    int sido;/*                                                                                                                                                            ##*/
/*#*/    int go_ah = 0;/*                                                                                                                                                       ##*/
/*#*/    int old_opp = 0;/*                                                                                                                                                     ##*/
/*#*/    t_cord my_hom = {0,0};/*                                                                                                                                               ##*/
/*#*/    t_cord opp_hom = {0,0};/*                                                                                                                                              ##*/
/*#*/    // game loop/*                                                                                                                                                         ##*/
/*#*/    while (1) {/*                                                                                                                                                          ##*/
/*#*/        int my_matter;/*                                                                                                                                                   ##*/
/*#*/        int opp_matter;/*                                                                                                                                                  ##*/
/*#*/       iter++;/*                                                                                                                                                           ##*/
/*#*/        scanf("%d%d", &my_matter, &opp_matter);/*                                                                                                                          ##*/
/*#*/        for (int i = 0; i < height; i++) {/*                                                                                                                               ##*/
/*#*/            int opp_robo = 0;/*                                                                                                                                            ##*/
/*#*/            int my_robo = 0;/*                                                                                                                                             ##*/
/*#*/            int opp_erea = 0;/*                                                                                                                                            ##*/
/*#*/            int my_erea = 0;/*                                                                                                                                             ##*/
/*#*/            map[i] = (t_map *)malloc(sizeof(t_map ) * width);/*                                                                                                            ##*/
/*#*/            for (int j = 0; j < width; j++) {/*                                                                                                                            ##*/
/*#*/                int scrap_amount;/*                                                                                                                                        ##*/
/*#*/                // 1 = me, 0 = foe, -1 = neutral/*                                                                                                                         ##*/
/*#*/                int owner;/*                                                                                                                                               ##*/
/*#*/                int units;/*                                                                                                                                               ##*/
/*#*/                int recycler;/*                                                                                                                                            ##*/
/*#*/                int can_build;/*                                                                                                                                           ##*/
/*#*/                int can_spawn;/*                                                                                                                                           ##*/
/*#*/                int in_range_of_recycler;/*                                                                                                                                ##*/
/*#*/                scanf("%d%d%d%d%d%d%d", &scrap_amount, &owner, &units, &recycler, &can_build, &can_spawn, &in_range_of_recycler);/*                                        ##*/
/*#*/                map[i][j].scrap_amount = scrap_amount;/*                                                                                                                   ##*/
/*#*/                map[i][j].owner = owner;/*                                                                                                                                 ##*/
/*#*/                map[i][j].units = units;/*                                                                                                                                 ##*/
/*#*/                map[i][j].recycler = recycler;/*                                                                                                                           ##*/
/*#*/                map[i][j].can_build = can_build;/*                                                                                                                         ##*/
/*#*/                map[i][j].can_spawn = can_spawn;/*                                                                                                                         ##*/
/*#*/                map[i][j].in_range_of_recycler = in_range_of_recycler;/*                                                                                                   ##*/
/*#*/                map[i][j].add_unit = 0;/*                                                                                                                                  ##*/
/*#*/                map[i][j].moved_unit = 0;/*                                                                                                                                ##*/
/*#*/                opp_robo += (units) * (owner == 0);/*                                                                                                                      ##*/
/*#*/                my_robo += (units) * (owner == 1);/*                                                                                                                       ##*/
/*#*/                opp_erea += (scrap_amount != 0) * (owner == 0);/*                                                                                                          ##*/
/*#*/                my_erea += (scrap_amount != 0) * (owner == 1);/*                                                                                                           ##*/
/*#*//*                                                                                                                                                                         ##*/
/*#*/                if (iter == 1 && map[i][j].units == 0)/*                                                                                                                   ##*/
/*#*/                {/*                                                                                                                                                        ##*/
/*#*/                    if (map[i][j].owner == 1)/*                                                                                                                            ##*/
/*#*/                    {/*                                                                                                                                                    ##*/
/*#*/                       sido = (j > width / 2);/*                                                                                                                           ##*/
/*#*/                       star = (width - 1) * (j > width / 2);/*                                                                                                             ##*/
/*#*/                       end = (width - 1) * !(j > width / 2);/*                                                                                                             ##*/
/*#*/                       pas = -1 * (j > width / 2) + !(j > width / 2);/*                                                                                                    ##*/
/*#*/                       my_hom.x = i;/*                                                                                                                                     ##*/
/*#*/                       my_hom.y = j;/*                                                                                                                                     ##*/
/*#*/                    }/*                                                                                                                                                    ##*/
/*#*/                    if (map[i][j].owner == 0)/*                                                                                                                            ##*/
/*#*/                    {/*                                                                                                                                                    ##*/
/*#*/                       opp_hom.x = i;/*                                                                                                                                    ##*/
/*#*/                       opp_hom.y = j;/*                                                                                                                                    ##*/
/*#*/                    }/*                                                                                                                                                    ##*/
/*#*/                }/*                                                                                                                                                        ##*/
/*#*/            }/*                                                                                                                                                            ##*/
/*#*/            map[0][0].star = star;/*                                                                                                                                       ##*/
/*#*/            map[0][0].end = end;/*                                                                                                                                         ##*/
/*#*/            map[0][0].pas = pas;/*                                                                                                                                         ##*/
/*#*//*                                                                                                                                                                         ##*/
/*#*/            map[0][0].my_hom.x = my_hom.x;/*                                                                                                                               ##*/
/*#*/            map[0][0].my_hom.y = my_hom.y;/*                                                                                                                               ##*/
/*#*/            map[0][0].opp_hom.x = opp_hom.x;/*                                                                                                                             ##*/
/*#*/            map[0][0].opp_hom.y = opp_hom.y;/*                                                                                                                             ##*/
/*#*//*                                                                                                                                                                         ##*/
/*#*/            map[0][0].all_my_erea += my_erea;/*                                                                                                                            ##*/
/*#*/            map[0][0].all_opp_erea += opp_erea;/*                                                                                                                          ##*/
/*#*/            map[i][0].opp_robo_in_line = opp_robo;/*                                                                                                                       ##*/
/*#*/            map[i][0].my_robo_in_line = my_robo;/*                                                                                                                         ##*/
/*#*/            map[i][0].opp_erea_in_line = opp_erea;/*                                                                                                                       ##*/
/*#*/            map[i][0].my_erea_in_line = my_erea;/*                                                                                                                         ##*/
/*#*//*                                                                                                                                                                         ##*/
/*#*/            map[0][0].all_my_erea += my_erea;/*                                                                                                                            ##*/
/*#*/            map[0][0].all_opp_erea += opp_erea;/*                                                                                                                          ##*/
/*#*/        }/*                                                                                                                                                                ##*/
/*#*/        map[0][0].my_matter = my_matter;/*                                                                                                                                 ##*/
/*#*/        map[0][0].opp_matter = opp_matter;/*                                                                                                                               ##*/
/*#*/        map[0][0].width = width;/*                                                                                                                                         ##*/
/*#*/        map[0][0].height = height;/*                                                                                                                                       ##*/
/*#*/        map[0][0].iter = iter;/*                                                                                                                                           ##*/
/*#*/        map = ft_full_sides(map, width, height, sido);/*                                                                                                                   ##*/
/*#*/        map = ft_get_all_attacks(map);/*                                                                                                                                   ##*/
/*################################################################################################################################################################################*/      
                                        /*#*/  
                                        /*#*/  
                                        /*#*/   
                                        /*#*/  
                                        /*#*/   
                                        /*#*/   
                                        /*#*/   
                                        /*#*/   
                                        /*######################################################################################################*/
                                                                            /*#*/ printf("WAIT\n"); /*#*/
                                                                            /*#*/   }               /*#*/
                                                                            /*#*/    return 0;      /*#*/
                                                                            /*#*/        }          /*#*/
                                                                            /*#########################*/