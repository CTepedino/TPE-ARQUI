#include <pong.h>
#define ESC 27
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 60
#define PADDLE_SPEED 7
#define BALL_SIZE 10
#define BALL_INITIAL_SPEED_X 5
#define BALL_INITIAL_SPEED_Y 5


struct paddle{
    int x;
    int y;
    int prev_y ;
};

struct ball{ //internamente la pelota es un cuadrado, aunque la dibujemos como un circulo
    int  x;
    int  y;
    int prev_x ;
    int prev_y ;
    int speed_x;
    int speed_y;
};


static char keys[11];
static char rkeys[11];
static int l_u;
static int l_d;
static int r_u;
static int r_d;

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
static void checkCollisionsAndGoals();
static void setStart();

void pong(){
    screenInfo(&width,&height);
    ball.prev_x = 0;
    ball.prev_y = 0;
    leftPaddle.prev_y = 0;
    rightPaddle.prev_y = 0;
    clearScreen();
    setStart();

   /* scoreL =0;
    * scoreR = 0
    * */
    //todavia no probe si hace falta, es para el caso de cerrar el juego y volverlo a abrir\

    int running = 1;
    while(running){
        sleep(1);//para que el juego no vaya a velocidades absurdas

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
        movePaddles();
        moveBall();
        checkCollisionsAndGoals();
        draw();
    }
    clearScreen();
}

static void movePaddles(){
    leftPaddle.prev_y = leftPaddle.y;
    rightPaddle.prev_y = rightPaddle.y;
    if (l_d){
        leftPaddle.y += PADDLE_SPEED;
        if (leftPaddle.y + PADDLE_HEIGHT > height){
            leftPaddle.y = height - PADDLE_HEIGHT;
        }
    }
    if (l_u){
        leftPaddle.y -= PADDLE_SPEED;
        if (leftPaddle.y < 0){
            leftPaddle.y = 0;
        }
    }
    if (r_d){
        rightPaddle.y += PADDLE_SPEED;
        if (rightPaddle.y + PADDLE_HEIGHT > height){
            rightPaddle.y = height - PADDLE_HEIGHT;
        }
    }
    if (r_u){
        rightPaddle.y -= PADDLE_SPEED;
        if (rightPaddle.y < 0){
            rightPaddle.y = 0;
        }
    }
}

static void moveBall(){
    ball.prev_x = ball.x;
    ball.prev_y = ball.y;
    ball.x += ball.speed_x;
    ball.y += ball.speed_y;
}


static void checkCollisionsAndGoals(){
    if (ball.y <= 0 || ball.y + BALL_SIZE >= height){
        ball.speed_y = -ball.speed_y;
    }

    if (ball.x <= leftPaddle.x + PADDLE_WIDTH && ball.y >= leftPaddle.y && ball.y <= leftPaddle.y+PADDLE_HEIGHT){
        ball.speed_x = -ball.speed_x;
    }
    else if (ball.x <= leftPaddle.x + PADDLE_WIDTH){
        scoreR++;
        beep(0x777, 1); //TODO: buscar alguna frecuencia que no suene tan fea
        setStart();
    }

    if (ball.x >= rightPaddle.x - PADDLE_WIDTH && ball.y >= rightPaddle.y && ball.y <= rightPaddle.y+PADDLE_HEIGHT){
        ball.speed_x = -ball.speed_x;
    }
    else if (ball.x >= rightPaddle.x - PADDLE_WIDTH){
        scoreL++;
        beep(0x777, 1);
        setStart();
    }

}


static void draw() {
    clearRectangle(leftPaddle.x, leftPaddle.prev_y, PADDLE_WIDTH, PADDLE_HEIGHT);
    clearRectangle(rightPaddle.x, rightPaddle.prev_y, PADDLE_WIDTH, PADDLE_HEIGHT);
    clearCircle(ball.prev_x + BALL_SIZE / 2, ball.prev_y + BALL_SIZE / 2, BALL_SIZE / 2);

    drawRectangle(leftPaddle.x, leftPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
    drawRectangle(rightPaddle.x, rightPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
    drawCircle(ball.x + BALL_SIZE / 2, ball.y + BALL_SIZE / 2, BALL_SIZE / 2);
}

static void setStart(){
    ball.y =height/2-BALL_SIZE/2;
    ball.x=width/2-BALL_SIZE/2;
    ball.speed_x= BALL_INITIAL_SPEED_X;
    ball.speed_y= BALL_INITIAL_SPEED_Y;

    leftPaddle.x = width/10;
    leftPaddle.y = height/2-PADDLE_HEIGHT/2;

    rightPaddle.x = width*9/10;
    rightPaddle.y=height/2-PADDLE_HEIGHT/2;

    l_u = 0;
    l_d = 0;
    r_u = 0;
    r_d = 0;

    draw();

    char c;
    do{
        c = getChar();
    } while( c != ' ' && c != '\n');
}