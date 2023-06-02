#include <pong.h>
#include <stdint.h>
#include <libc.h>

#define PADDLE_HEIGHT 50
#define PADDLE_WIDTH 10
#define BALL_RADIUS 5


uint32_t width;
uint32_t height;
int ballX, ballY; //Centro de la pelota
int ballSpeedX = 1; 
int ballSpeedY = 1;
int paddleLeftX, paddleLeftY, paddleRightX, paddleRightY; //Punto inferior izquierdo del rectangulo
char rightScore = '0';
char leftScore = '0';



static void drawBoard(){
    drawRectangle(paddleLeftX, paddleLeftY, PADDLE_WIDTH, PADDLE_HEIGHT);
    drawRectangle(paddleRightX, paddleRightY, PADDLE_WIDTH, PADDLE_HEIGHT);
    drawCircle(ballX, ballY, BALL_RADIUS);
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
        //playSound();
    }
    if (ballY == width){ //Left side scores
        leftScore += 1;
        updateScore();
        resetBall();
        //playSound();
    }
    if (ballX - BALL_RADIUS == paddleLeftX + PADDLE_WIDTH && ballY >= paddleLeftY && ballY <= paddleLeftY + PADDLE_HEIGHT){ //Hit left paddle
        ballSpeedX = 1;
    }
    if (ballX + BALL_RADIUS == paddleRightX && ballY >= paddleRightY && ballY <= paddleRightY + PADDLE_HEIGHT){ //Hit right paddle
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
    clearScreen();
    screenInfo(&width, &height);
    resetBall();
    updateScore();
    paddleLeftX = width/8;
    paddleRightX = width*7/8;
    paddleLeftY = height/2;
    paddleRightY = height/2; 
    char key;

    while (1){
        drawBoard();
        updateBall();
        key = getChar();
        movePaddle(key);
    }    
}