#include <GL/glut.h>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 600;

const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 60;
const int PADDLE_SPEED = 5;

const int BALL_RADIUS = 10;
float ballX = WIDTH / 2;
float ballY = HEIGHT / 2;
float ballSpeedX = -2;
float ballSpeedY = -2;

int player1Y = HEIGHT / 2;
int player2Y = HEIGHT / 2;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void drawPaddle(int x, int y)
{
    glBegin(GL_QUADS);
    glVertex2i(x, y - PADDLE_HEIGHT / 2);
    glVertex2i(x, y + PADDLE_HEIGHT / 2);
    glVertex2i(x + PADDLE_WIDTH, y + PADDLE_HEIGHT / 2);
    glVertex2i(x + PADDLE_WIDTH, y - PADDLE_HEIGHT / 2);
    glEnd();
}

void drawBall()
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(ballX, ballY);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.14159 / 180;
        float x = ballX + BALL_RADIUS * cos(angle);
        float y = ballY + BALL_RADIUS * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  //white

    drawPaddle(20, player1Y);
    drawPaddle(WIDTH - PADDLE_WIDTH - 20, player2Y);

    drawBall();

    glutSwapBuffers();  //to update the screen
}
/*
 *
 * */
void update(int value)
{
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    if (ballY >= HEIGHT - BALL_RADIUS || ballY <= BALL_RADIUS)
    {
        ballSpeedY *= -1;
    }

    if ((ballX <= 30 + PADDLE_WIDTH && ballY >= player1Y - PADDLE_HEIGHT / 2 && ballY <= player1Y + PADDLE_HEIGHT / 2) ||
        (ballX >= WIDTH - 30 - PADDLE_WIDTH - BALL_RADIUS && ballY >= player2Y - PADDLE_HEIGHT / 2 && ballY <= player2Y + PADDLE_HEIGHT / 2))
    {
        ballSpeedX *= -1;
    }

    if (GetAsyncKeyState('W') && player1Y < HEIGHT - PADDLE_HEIGHT / 2)
    {
        player1Y += PADDLE_SPEED;
    }
    if (GetAsyncKeyState('S') && player1Y > PADDLE_HEIGHT / 2)
    {
        player1Y -= PADDLE_SPEED;
    }

    if (GetAsyncKeyState(VK_UP) && player2Y < HEIGHT - PADDLE_HEIGHT / 2)
    {
        player2Y += PADDLE_SPEED;
    }

    if (GetAsyncKeyState(VK_DOWN) && player2Y > PADDLE_HEIGHT / 2)
    {
        player2Y -= PADDLE_SPEED;
    }

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Pong Game");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0);
    glutMainLoop();

    return 0;
}