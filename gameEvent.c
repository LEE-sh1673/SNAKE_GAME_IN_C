#include "snake.h"

void EndGame()
{
    system("cls");
    DrawMap();
    GoToXY(MAP_WIDTH / 2 - 4, (MAP_HEIGHT - 1) / 2 - 3);
    printf("[Result]\n");
    GoToXY(MAP_WIDTH / 2 - 4, (MAP_HEIGHT - 1) / 2 - 1);
    printf("LENGTH : %ld\n", snake.length);
    GoToXY(MAP_WIDTH / 2 - 4, (MAP_HEIGHT - 1) / 2);
    printf("SPEED  : %ldms\n", snake.speed);
    GoToXY(MAP_WIDTH / 2 - 4, (MAP_HEIGHT - 1) / 2 + 2);
    printf("Exit the game...\n");

    GoToXY(MAP_WIDTH / 2 - 4, (MAP_HEIGHT - 1) / 2 + MAP_HEIGHT);
    Sleep(1000);
    exit(1);
}

void InitGame()
{
    srand((unsigned)time(NULL));
    SetCursorType(NOCURSOR);

    snake.direction = RIGHT;
    snake.length = SNAKE_INIT_LENGTH;
    snake.speed = SPEED_INIT;

    // Draw Snake head first
    snakePos[HEAD].x = MAP_WIDTH / 2 - 5;
    snakePos[HEAD].y = MAP_HEIGHT / 2;
    GoToXY(snakePos[HEAD].x, snakePos[HEAD].y);
    printf("%s", snakeObj[HEAD]);

    // Draw snake bodies.
    for (int i = 1; i < (int)snake.length; i++) {
        
        snakePos[i].x = MAP_WIDTH / 2 - i - 5;
        snakePos[i].y = MAP_HEIGHT / 2;

        GoToXY(snakePos[i].x, snakePos[i].y);
        printf("%s", snakeObj[BODY]);
    }

    // Draw Items
    foodPos.x = MAP_WIDTH / 2 + 5;
    foodPos.y = MAP_HEIGHT / 2;
    GoToXY(foodPos.x, foodPos.y);
    printf("%s", mapObj[HEART]);

    speedDownPos.x = MAP_WIDTH / 2;
    speedDownPos.y = MAP_HEIGHT / 2 + 5;
    GoToXY(speedDownPos.x, speedDownPos.y);
    printf("%s", mapObj[SPEEDDOWN]);
}

void CreateFood()
{
    int checkPos;

    do {
        checkPos = 0;
        foodPos.x = rand() % (MAP_WIDTH - 2) + 1;
        foodPos.y = rand() % (MAP_HEIGHT - 2) + 1;

        for (int i = 0; i < (int)snake.length; i++) {
            if ((snakePos[i].x != foodPos.x) && (snakePos[i].y != foodPos.y)) {
                checkPos = 1;
                break;
            }
        }
    } while (checkPos == 0);

    GoToXY(foodPos.x, foodPos.y);
    printf("%s", mapObj[HEART]);
}

void CreateSpeedDown()
{
    int checkPos;

    do {
        checkPos = 0;
        speedDownPos.x = rand() % (MAP_WIDTH - 2) + 1;
        speedDownPos.y = rand() % (MAP_HEIGHT - 2) + 1;

        for (int i = 0; i < (int)snake.length; i++) {
            if ((snakePos[i].x && speedDownPos.x && foodPos.x) && (snakePos[i].y && speedDownPos.y && foodPos.y)) {
                checkPos = 1;
                break;
            }
        }
    } while (checkPos == 0);

    GoToXY(speedDownPos.x, speedDownPos.y);
    printf("%s", mapObj[SPEEDDOWN]);
}

void GameProcess()
{
    if (snakePos[HEAD].x <= 0 || snakePos[HEAD].x >= MAP_WIDTH - 1 ||
        snakePos[HEAD].y <= 0 || snakePos[HEAD].y >= MAP_HEIGHT - 1) {
        EndGame();
    }

    for (int i = 1; i < (int)snake.length; i++) {
        if ((snakePos[HEAD].x == snakePos[i].x) && (snakePos[HEAD].y == snakePos[i].y)) {
            EndGame();
        }
    }

    if (snakePos[HEAD].x == foodPos.x && snakePos[HEAD].y == foodPos.y) {
        snake.speed -= SPEED_UP_RATE;
        snake.length++;

        if (snake.speed < SPEED_LIMIT) {
            snake.speed = SPEED_LIMIT;
        }
        CreateFood();
     
        snakePos[SNAKE_TAIL].x = snakePos[SNAKE_TAIL - 1].x;
        snakePos[SNAKE_TAIL].y = snakePos[SNAKE_TAIL - 1].y;
    }

    if (snakePos[HEAD].x == speedDownPos.x && snakePos[HEAD].y == speedDownPos.y) {
        snake.speed += SPEED_DOWN_RATE;

        if (snake.speed >= SPEED_INIT) {
            snake.speed = SPEED_INIT;
        }

        CreateSpeedDown();
    }
}

void DrawSnake()
{
    // replace head to body.
    GoToXY(snakePos[HEAD].x, snakePos[HEAD].y);
    printf("%s", snakeObj[BODY]);

    // Remove Tail
    GoToXY(snakePos[SNAKE_TAIL].x, snakePos[SNAKE_TAIL].y);
    printf("  ");

    // Move All body sections.
    for (int i = SNAKE_TAIL; i > HEAD; i--) {
        snakePos[i].x = snakePos[i - 1].x;
        snakePos[i].y = snakePos[i - 1].y;
    }

    switch (snake.direction)
    {
    case UP:
        snakePos[HEAD].y--;
        break;
    case DOWN:
        snakePos[HEAD].y++;
        break;
    case RIGHT:
        snakePos[HEAD].x++;
        break;
    case LEFT:
        snakePos[HEAD].x--;
        break;
    default:
        break;
    }

    // Draw head on new position
    GoToXY(snakePos[HEAD].x, snakePos[HEAD].y);
    printf("%s", snakeObj[HEAD]);
}

void DrawMap()
{
	for (int i = 0; i < MAP_WIDTH; i++) {
        GoToXY(i, 0); 
        printf("%s", mapObj[WALL]);

        GoToXY(i, MAP_HEIGHT - 1); 
        printf("%s", mapObj[WALL]);
	}

    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        GoToXY(0, i); 
        printf("%s", mapObj[WALL]);

        GoToXY(MAP_WIDTH - 1, i);
        printf("%s", mapObj[WALL]);
    }
    printf("\n\n");
}

void DrawUI(size_t length, size_t speed)
{
    int offset = 5;
    int uiWidthSize = 25;
    int uiHeightSize = 12;

    for (int i = MAP_WIDTH + offset; i < MAP_HEIGHT + uiWidthSize; i++) {
        GoToXY(i, offset);
        printf("+");

        GoToXY(i, uiHeightSize);
        printf("+");
    }
    for (int i = offset; i < uiHeightSize; i++) {
        GoToXY(MAP_WIDTH + offset, i);
        printf("+");

        GoToXY((MAP_WIDTH + uiWidthSize - offset * 3 - 1), uiHeightSize - offset + 1);
        printf("LENGTH : %ld", length);
        GoToXY((MAP_WIDTH + uiWidthSize - offset * 3 - 1), uiHeightSize - offset + 2);
        printf("SPEED  : %ldms", speed);

        GoToXY(MAP_WIDTH + uiWidthSize - offset - 1, i);
        printf("+");
    }
    printf("\n\n");
}

void KeyProcess()
{
    int key = 0;

    if (kbhit()) {
        key = getch();

        if (key == 224) {
            key = getch();

            switch (key)
            {
            case UP:
                if (snake.direction != DOWN) {
                    snake.direction = key;
                }
                break;
            case DOWN:
                if (snake.direction != UP) {
                    snake.direction = key;
                }
                break;
            case RIGHT:
                if (snake.direction != LEFT) {
                    snake.direction = key;
                }
                break;
            case LEFT:
                if (snake.direction != RIGHT) {
                    snake.direction = key;
                }
                break;
            default:
                break;
            }

        } else {
            if (key == ESC) {
                EndGame();
            }
        }
    }
}


void PlaySnake()
{
    DrawMap();
    InitGame();
    
    while (1) {
        DrawUI(snake.length, snake.speed);
        KeyProcess();
        GameProcess();
        DrawSnake();
        Sleep(snake.speed);
    }
}