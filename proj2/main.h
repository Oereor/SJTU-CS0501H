//
// Created by unkn0 on 2026-03-23.
//

#ifndef PROJ2_MAIN_H
#define PROJ2_MAIN_H

int getMapWidth();
int getMapHeight();
int getMapCell(int x, int y); // 0=空地 1=墙壁 2=蛇头 3=蛇身 4=正食物 5=负食物
int getSnakeLength();
int getSnakeX(int i);
int getSnakeY(int i);
int getFoodX();
int getFoodY();
int getNegFoodCount();
int getNegFoodXAt(int i);
int getNegFoodYAt(int i);
int abs(int x);
int min(int a, int b);
int max(int a, int b);
int randomInt(int n);

#endif //PROJ2_MAIN_H