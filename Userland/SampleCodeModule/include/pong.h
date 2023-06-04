#ifndef PONG_H
#define PONG_H
#include <stdint.h>
#include <libc.h>
#define ESC 27
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 60
#define PADDLE_SPEED 7
#define BALL_SIZE 10
#define BALL_INITIAL_SPEED_X 8
#define BALL_INITIAL_SPEED_Y 5

void pong();

#endif
