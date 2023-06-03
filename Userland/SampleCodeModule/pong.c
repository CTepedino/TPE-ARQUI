#include <pong.h>
#include <stdint.h>
#include <libc.h>

#define PADDLE_SPEED 5


uint32_t width;
uint32_t height;
int ballX, ballY; //Centro de la pelota
int ballSpeedX = 1; 
int ballSpeedY = 1;
int ballRadius;
int paddleLeftX, paddleLeftY, paddleRightX, paddleRightY; //Punto inferior izquierdo del rectangulo
char rightScore = '0';
char leftScore = '0';
int paddleHeight, paddleWidth;



static void drawBoard(){
    drawRectangle(paddleLeftX, paddleLeftY, paddleWidth, paddleHeight);
    drawRectangle(paddleRightX, paddleRightY, paddleWidth, paddleHeight);
    drawCircle(ballX, ballY, ballRadius);
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
    clearCircle(ballX, ballY, ballRadius);
    ballX += ballSpeedX;
    ballY += ballSpeedY;
    if (ballX <= 0){ //Right side scores
        rightScore += 1;
        updateScore();
        resetBall();
        //playSound();
    }
    if (ballX >= width){ //Left side scores
        leftScore += 1;
        updateScore();
        resetBall();
        //playSound();
    }
    if (ballX - ballRadius == paddleLeftX + paddleWidth && ballY >= paddleLeftY && ballY <= paddleLeftY + paddleHeight){ //Hit left paddle
        ballSpeedX = ballSpeedX;
    }
    if (ballX + ballRadius == paddleRightX && ballY >= paddleRightY && ballY <= paddleRightY + paddleHeight){ //Hit right paddle
        ballSpeedX = -ballSpeedX;
    }
    if (ballY <= 0 || ballY >= height){ //Hit top or bottom of screen
        ballSpeedY = -ballSpeedY;
    }
    drawCircle(ballX, ballY, ballRadius);
}

static void movePaddle(char key){
    if (key == 'w'){
        clearRectangle(paddleLeftX, paddleLeftY, paddleWidth, paddleHeight);
        paddleLeftY -= PADDLE_SPEED;
        drawRectangle(paddleLeftX, paddleLeftY, paddleWidth, paddleHeight);
    }
    if (key == 's'){
        clearRectangle(paddleLeftX, paddleLeftY, paddleWidth, paddleHeight);
        paddleLeftY += PADDLE_SPEED;
        drawRectangle(paddleLeftX, paddleLeftY, paddleWidth, paddleHeight);
    }
    if(key == 'i'){
        clearRectangle(paddleRightX, paddleRightY, paddleWidth, paddleHeight);
        paddleRightY -= PADDLE_SPEED;
        drawRectangle(paddleRightX, paddleRightY, paddleWidth, paddleHeight);
    }
    if(key == 'k'){
        clearRectangle(paddleRightX, paddleRightY, paddleWidth, paddleHeight);
        paddleRightY += PADDLE_SPEED;
        drawRectangle(paddleRightX, paddleRightY, paddleWidth, paddleHeight);
    }
}


void pong(){
    clearScreen();
    screenInfo(&width, &height);
    resetBall();
    updateScore();
    paddleLeftX = width/10;
    paddleRightX = width*9/10;
    paddleLeftY = height/2;
    paddleRightY = height/2; 
    paddleHeight = height/8;
    paddleWidth = width/100;
    ballRadius = width/200;
    char key;
    drawBoard();

    while (1){
        updateBall();
        key = getChar();
        movePaddle(key);
    }    
}