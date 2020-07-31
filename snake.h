#ifndef __snake_H__
#define __snake_H__

#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// User defined cursor controller header
#include "cursorCtrl.h"

// Commands
#define ESC 27
#define UP 72 //'w'
#define DOWN 80 //'s'
#define RIGHT 77 //'d'
#define LEFT 75 //'a'

// Map Width & Height
#define MAP_WIDTH 20
#define MAP_HEIGHT 15

// Items
#define MAP_OBJ_SIZE 3

// Snake
#define SNAKE_INIT_LENGTH 4
#define SNAKE_MAX_LENGTH 100
#define SNAKE_OBJ_SIZE 2
#define SNAKE_HEAD 0
#define SNAKE_BODY 1
#define SNAKE_TAIL (snake.length - 1)

// Speed
#define SPEED_INIT 300
#define SPEED_LIMIT 100
#define SPEED_UP_RATE 50
#define SPEED_DOWN_RATE 25

typedef enum MapObj {
	WALL = 0,
	HEART,
	SPEEDDOWN,
}MapObj;

typedef enum SnakeObj {
	HEAD = 0,
	BODY,
}SnakeObj;

typedef struct Snake {
	size_t length;
	size_t speed;
	size_t direction;
}Snake;

typedef struct Pos {
	size_t x;
	size_t y;
}Pos;


// map obj
extern const char* mapObj[MAP_OBJ_SIZE];

// snake obj
extern const char* snakeObj[SNAKE_OBJ_SIZE];
extern Snake snake;

// obj positions
extern Pos snakePos[SNAKE_MAX_LENGTH];
extern Pos foodPos;
extern Pos speedDownPos;

// Game Events
extern void EndGame();
extern void InitGame();
extern void CreateFood();
extern void CreateSpeedDown();
extern void GameProcess();
extern void DrawSnake();
extern void DrawMap();
extern void DrawUI(size_t length, size_t speed);
extern void KeyProcess();
extern void PlaySnake();

#endif