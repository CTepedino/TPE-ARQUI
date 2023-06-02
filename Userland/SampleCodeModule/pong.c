#include <pong.h>
#include <stdint.h>
#include <libc.h>

#define WHITE 0xFFFFFF
#define MAX_HEIGHT 1000
#define MAX_WIDTH  1000

char screen[MAX_HEIGHT][MAX_WIDTH] = {0};
uint32_t width;
uint32_t height;
int ballX, ballY;
int ballSpeedX = 1; 
int ballSpeedY = 1;
int paddleLeftX, paddleLeftY, paddleRightX, paddleRightY;
int paddleHeight;
char rightScore = '0';
char leftScore = '0';



static void drawBoard(){
    // for(int i = 0; i < height; i++){
    //     for(int j = 0; j < width; j++){
    //         if((j == paddleLeftX && i >= paddleLeftY && i <= paddleLeftY + paddleHeight) || (j == paddleRightX && i >= paddleRightY && i <= paddleRightY + paddleHeight) || (j == ballX && i == ballY))
    //             screen[i][j] = 1;
    //     }
    // }
    drawScreen(0, height, width, height, screen);
}

static void resetBall(){
    ballX = width/2;
    ballY = height/2;
}

static void updateScore(){
    textPosition(width/4, height/10);
    putChar(leftScore);
    textPosition(width*3/4, height/10);
    putChar(rightScore);
}

static void updateBall(){
    ballX += ballSpeedX;
    ballY += ballSpeedY;
    if (ballX == 0){ //Right side scores
        rightScore += 1;
        updateScore();
        resetBall();
    }
    if (ballY == width){ //Left side scores
        leftScore += 1;
        updateScore();
        resetBall();
    }
    if (ballX == paddleLeftX + 1 && ballY >= paddleLeftY && ballY <= paddleLeftY + paddleHeight){ //Hit left paddle
        ballSpeedX = 1;
    }
    if (ballX == paddleRightX + 1 && ballY >= paddleRightY && ballY <= paddleRightY + paddleHeight){ //Hit right paddle
        ballSpeedX = -1;
    }
    if (ballY == 0 || ballY == height){ //Hit top or bottom of screen
        ballSpeedY = -ballSpeedY;
    }
}

static void movePaddle(char key){
    if (key == 'w'){
        paddleLeftY += 1;
    }
    if (key == 's'){
        paddleLeftY -= 1;
    }
    if(key == 'i'){
        paddleRightY += 1;
    }
    if(key == 'k'){
        paddleRightY -= 1;
    }
}


void pong(){
    screenInfo(&width, &height);
    resetBall();
    updateScore();
    paddleLeftX = width/8;
    paddleRightX = width*7/8;
    paddleLeftY = height/2;
    paddleRightY = height/2; 
    paddleHeight = height/10;
    char key;

    while (1){
        drawBoard();
        updateBall();
        key = getChar();
        movePaddle(key);
    }    
}