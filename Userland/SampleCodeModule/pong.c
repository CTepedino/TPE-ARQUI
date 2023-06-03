#include <pong.h>
#define ESC 27
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 60
#define PADDLE_SPEED 5
#define BALL_SIZE 10

struct paddle{
    int x;
    int y;
};

struct ball{ //internamente la pelota es un cuadrado, aunque la dibujemos como un circulo
    int  x;
    int  y;
    int speed_x;
    int speed_y;
};


static char keys[11];
static char rkeys[11];
static int l_u=0;
static int l_d=0;
static int r_u=0;
static int r_d=0;

static uint32_t width;
static uint32_t height;

static int scoreL = 0;
static int scoreR = 0;

static struct paddle leftPaddle;
static struct paddle rightPaddle;
static struct ball ball;

static void draw();
static void movePaddles();
static void moveBall();
static void checkCollisions();
static void checkGoal();

void pong(){
    screenInfo(&width,&height);
    ball.y =height/2-BALL_SIZE/2;
    ball.x=width/2-BALL_SIZE/2;
    ball.speed_x=3;
    ball.speed_y=3;

    leftPaddle.x = width/10;
    leftPaddle.y = height/2-PADDLE_HEIGHT/2;

    rightPaddle.x = width*9/10;
    rightPaddle.y=height/2-PADDLE_HEIGHT/2;

   /* scoreL =0;
    * scoreR = 0
    * l_u = 0;
    l_d = 0;
    r_u = 0;
    r_d = 0;*/
    //todavia no probe si hace falta, es para el caso de cerrar el juego y volverlo a abrir\

    clearScreen();
    draw();

    int running = 1;
    while(running){
        sleep(1);//para que el juego no vaya a velocidades absurdas

        //TODO: Poder salir con ESC

        getCurrentKeyPress(keys);
        for(int i = 0; keys[i]; i++){
            switch (keys[i]){
                case ESC:
                    running = 0;
                case 'w':
                    l_u = 1;
                    break;
                case 's':
                    l_d =1;
                    break;
                case 'i':
                    r_u = 1;
                    break;
                case 'k':
                    r_d = 1;
                    break;
            }
        }
        getCurrentReleasedKeys(rkeys);
        for(int i = 0; rkeys[i]; i++){
            switch (rkeys[i]){
                case 'w':
                    l_u = 0;
                    break;
                case 's':
                    l_d =0;
                    break;
                case 'i':
                    r_u = 0;
                    break;
                case 'k':
                    r_d = 0;
                    break;
            }
        }
        clearCircle(ball.x+BALL_SIZE/2, ball.y+BALL_SIZE/2, BALL_SIZE/2);
        movePaddles();
        moveBall();
        checkCollisions();
        checkGoal();
        drawCircle(ball.x+BALL_SIZE/2, ball.y+BALL_SIZE/2, BALL_SIZE/2);
        //draw();
    }
    clearScreen();
}

static void movePaddles(){
    if (l_d){
        clearRectangle(leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);

        leftPaddle.y += PADDLE_SPEED;
        if (leftPaddle.y + PADDLE_HEIGHT > height){
            leftPaddle.y = height - PADDLE_HEIGHT;
        }

        drawRectangle(leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);

    }
    if (l_u){
        clearRectangle(leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
        leftPaddle.y -= PADDLE_SPEED;
        if (leftPaddle.y < 0){
            leftPaddle.y = 0;
        }
        drawRectangle(leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);

    }
    if (r_d){
        clearRectangle(rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
        rightPaddle.y += PADDLE_SPEED;
        if (rightPaddle.y + PADDLE_HEIGHT > height){
            rightPaddle.y = height - PADDLE_HEIGHT;
        }
        drawRectangle(rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);

    }
    if (r_u){
        clearRectangle(rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
        rightPaddle.y -= PADDLE_SPEED;
        if (rightPaddle.y < 0){
            rightPaddle.y = 0;
        }
        drawRectangle(rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
    }
}

static void moveBall(){
    ball.x += ball.speed_x;
    ball.y += ball.speed_y;
}


static void checkCollisions(){
    if (ball.y <= 0 || ball.y + BALL_SIZE >= height){
        ball.speed_y = -ball.speed_y;
    }
    if (ball.x <= leftPaddle.x + PADDLE_WIDTH && ball.y >= leftPaddle.y && ball.y <= leftPaddle.y+PADDLE_HEIGHT){
        ball.speed_x = -ball.speed_x;
    }
    if (ball.x >= rightPaddle.x - PADDLE_WIDTH && ball.y >= rightPaddle.y && ball.y <= rightPaddle.y+PADDLE_HEIGHT){
        ball.speed_x = -ball.speed_x;
    }
}


static void checkGoal(){
    if (ball.x <= leftPaddle.x + PADDLE_WIDTH){
        scoreR++;
    }
    if (ball.y <= rightPaddle.x - PADDLE_WIDTH){
        scoreL++;
    }
}

static void draw(){
    clearScreen(); //TODO: escribir mejor esta funcion, asi es lentisima xd
    clearRectangle(leftPaddle.x, 0, PADDLE_WIDTH, height);
    drawRectangle(leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
    drawRectangle(rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
    drawCircle(ball.x+BALL_SIZE/2, ball.y+BALL_SIZE/2, BALL_SIZE/2);
}
