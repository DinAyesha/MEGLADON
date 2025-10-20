/*Name: 				    Id:
1. Ayesha Mehjaben Tonima 	21-45841-3
2.Ayesha Din Jannat		    21-45948-3
3.Zilani Khan			    21-45785-3#include <iostream>*/

#include <GL/glut.h>

#include <math.h>
#include <GL/gl.h>
#include <string>

#define right 1
#define left -1

float s = 400, ss = 140, a = 0, b = 0, aa = -70, bb = 0, flag = 0, home_screen_show = 0, flag4 = 0, game_finished = 0;

float GAME_TIME = 0.5; // in minutes
int game_score = 0;
int game_final_score = 0;
int minimum_score = 5;

//timing showing functionalities
int time_remaining = (int)(GAME_TIME * 60);


float x = 100, y = 0, r = 0.5, y11 = 0, y21 = 0, y31 = 0, y41 = 0, y51 = 0, y61 = 0, y71 = 0, y81 = 0, y91 = 0, y10 = 0, y12 = 0, y13 = 0, y14 = 0, x0 = 0, xo = 0, angle = 0.0, pi = 3.142;

struct fish
{
    float x;
    float y;
    int disappearing_interval = 0;
    fish(float a,float b)
    {
        x =a;
        y=b;
        disappearing_interval = 0;
    }
};

fish fish1(200,200); // will be done by zilani
fish fish2(100,100);
fish fish3(300,300);
fish fish4(100,300);
fish fish5(0,200);

fish fishes[5] = {fish1,fish2,fish3,fish4,fish5};

// all fishes have the same direction and same x_change and y_change
int fish_direction = right;
float x_change = 0;
float y_change = 0;

int fish_normal_position = 1;
int fish_up_position = 0;
int fish_upper_position = 0;
float speed = 1.5;


//shark variables by zilani
int shark_direction = left;

float shark_pos_x = 381.8;
float shark_pos_y = 337;
float shark_highest_speed = 2.5;
float shark_speed = shark_highest_speed;

int game_starts = 0;

int temp = 0;



void drawstring(float x, float y, float z, const char *string, int f);

void init();

void screen();

void gameFinishedScreen();

void reshape(GLint w, GLint h);


void pbSmall();

void pb();

void pb1();

void pb2();

void circleFunc(float yc, int d, int x1, int y1);

void circle(int x);

void plant3L(int x1, int x2, int m);

void plant2L(int x1, int x2, int h1, int h2);

void plant();

void display(void);




void renderBitmapString(float x, float y, void* font, const std::string& string) {
    glRasterPos2f(x, y);
    for (const char& c : string) {
        glutBitmapCharacter(font, c);
    }
}

void drawGradientOval(float cx, float cy, float xRadius, float yRadius, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);

    // Central color for the bottom of the sea
    glColor3f(1.0, 0.808, 0.271); // #FFD89C

    glVertex2f(cx, cy); // Center of the oval

    for (int i = 0; i <= num_segments; ++i)
    {
        float theta = (2.0f * M_PI * static_cast<float>(i)) / static_cast<float>(num_segments);

        // Interpolate colors for a gradient effect
        float r = 1.0;
        float g = 0.82 + 0.03 * cos(theta);
        float b = 0.48 + 0.07 * cos(theta);

        glColor3f(r, g, b);

        float x = cx + xRadius * cos(theta);
        float y = cy + yRadius * sin(theta);

        glVertex2f(x, y);
    }

    glEnd();
}


/* Callback handler for normal-key event */
void keyboardListener(unsigned char key, int x, int y)
{
    // float speed = 5.5;
    switch (key)
    {
    // Control eye (location of the eye)
    // control eyex
    case '1':
        break;
    case '2':
        break;
    // control eyey
    case '3':
        break;
    case '4':
        break;
    // control eyez
    case '5':
        break;
    case '6':
        break;

    // Control center (location where the eye is looking at)
    // control centerx
    case 'w':
        shark_pos_y += 10;
        if(shark_pos_y > 800)
        {
            shark_pos_y = -10;
        }
        break;
    case 's':
        if(shark_pos_y >= 10){
        shark_pos_y -= 10;
        }
        break;
    // control centery
    case 'd':
        shark_direction = right;
        break;
    case 'a':
         shark_direction = left;
        break;
    case 'p':
        home_screen_show = 0;
        flag4 = 0;
        game_starts = 0;
        break;
    case 'o':
        break;
    case 'i':
        break;
    case ',':
        // change the center of the sphere
        break;

    case '.':

        break;

    // Control exit
    case 13:
        // Enter button
        exit(0);
    case 27:     // ESC key
        home_screen_show = 1;
        flag4 = 1;
        game_starts = 1;
        break;
    }
    glutPostRedisplay(); // Post a paint request to activate display()
}

/* Callback handler for special-key event */
void specialKeyListener(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: // up arrow key
        break;
    case GLUT_KEY_DOWN: // down arrow key
        break;

    case GLUT_KEY_RIGHT: // right arrow key
        fish_direction = right;
        break;
    case GLUT_KEY_LEFT: // left arrow key
        fish_direction = left;
        break;

    case GLUT_KEY_PAGE_UP:
        break;
    case GLUT_KEY_PAGE_DOWN:
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
    glutPostRedisplay(); // Post a paint request to activate display()
}

void updateTimer(int value)
{
    glutPostRedisplay();
    if(game_starts)
    {

    // update the x_change and y_change,fish portion
    if(x_change < -500 && fish_direction == left)
    {
        x_change = 1300;
        if(fish_normal_position == 1)
        {
            fish_normal_position = 0;
            fish_up_position = 1;
            fish_upper_position = 0;
        }
        else if(fish_up_position == 1)
        {
            fish_normal_position = 0;
            fish_up_position = 0;
            fish_upper_position = 1;
        }
        else if(fish_upper_position == 1)
        {
            fish_normal_position = 1;
            fish_up_position = 0;
            fish_upper_position = 0;
        }
        if(fish_normal_position)
        {
            y_change= 0;
        }
        else if(fish_up_position || fish_upper_position)
        {
            y_change = y_change + 150;
        }
    }
    else if(x_change < -500 && fish_direction == right)
    {
        x_change = x_change + fish_direction*speed;
    }
    else if(x_change >=-500 && x_change<=1300)
    {
        x_change = x_change + fish_direction*speed;
    }
    else if(x_change > 1300 && fish_direction == left)
    {
        x_change = x_change + fish_direction * speed;
    }
    else if(x_change > 1300 && fish_direction == right)
    {
        x_change=-500;
        if(fish_normal_position == 1)
        {
            fish_normal_position = 0;
            fish_up_position = 1;
            fish_upper_position = 0;
        }
        else if(fish_up_position == 1)
        {
            fish_normal_position = 0;
            fish_up_position = 0;
            fish_upper_position = 1;
        }
        else if(fish_upper_position == 1)
        {
            fish_normal_position = 1;
            fish_up_position = 0;
            fish_upper_position = 0;
        }
        if(fish_normal_position)
        {
            y_change= 0;
        }
        else if(fish_up_position || fish_upper_position)
        {
            y_change = y_change + 150;
        }
    }

    // shark portion
    if(shark_pos_x < -300 && shark_direction == left)
    {
        shark_pos_x = 1300;
    }
    else if(shark_pos_x < -300 && shark_direction == right)
    {
        shark_pos_x = shark_pos_x + shark_direction*shark_speed;
    }
    else if(shark_pos_x >=-300 && shark_pos_x<=1300)
    {
        shark_pos_x = shark_pos_x + shark_direction*shark_speed;
    }
    else if(shark_pos_x > 1300 && shark_direction == left)
    {
        shark_pos_x = shark_pos_x + shark_direction*shark_speed;
    }
    else if(shark_pos_x > 1300 && shark_direction == right)
    {
        shark_pos_x=-300;
    }
    // now handle the second and minute showcasing
    if(value % 100 == 0)
    {
        //1 second elapsed
        time_remaining --;
    }
    // check if GAME_TIME finished, if total time elapsed ends, game ends
    if(time_remaining == 0 )
    {
        //game finished
        game_finished = 1;
        game_final_score = game_score;
        game_starts = 0;
        home_screen_show = 0;
        flag4 = 0;
    }
    glutTimerFunc(10, updateTimer, value + 1);
    }
    else
    {
      glutTimerFunc(10, updateTimer, value);
    }
}

int main(int argc, char **argv)

{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(0, 0);

    glutInitWindowSize(1200, 600);

    glutCreateWindow("AQUARIUM");

    init();

    glutReshapeFunc(reshape);

    // glutKeyboardFunc(key);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);

    glutTimerFunc(0, updateTimer, 0);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;

}

// void speed()

// {

//     a = a - 9.0;

//     s = s - 10;

//     b = b + 10;

// }

void slow()

{

    a = a - 0.0001;
    s = s + 10;
    b = b - 10;

}

void key(unsigned char k, int x, int y)

{

    if (k == 'i')

        // glutIdleFunc(speed);

        if (k == 'd')

        {

            // glutIdleFunc(slow);

        }

    if (k == 'p')

    {

        home_screen_show = 1;

        flag4 = 1;

    }

}

void Shark(float ex, float ey, float eyeSize) {
    // For Shark Body
    glBegin(GL_TRIANGLE_FAN);
    for (angle = 0; angle < 320; angle += 2) {
        glColor3ub(120, 118, 119);
        y = (sin(angle * pi / 319) * 30);
        x = angle;
        glVertex2f(ex + (x - 51.8)*-1*shark_direction, y + ey - 2);
    }
    glColor3ub(200, 200, 200);
    glVertex2f(ex + (x- 51.8)*-1*shark_direction, y + ey -22);
    for (angle = 298; angle > 35; angle -= 2) {
        x = angle;
        y = -(sin(angle * pi / 319) * 20);
        glVertex2f(ex + (x- 51.8)*-1*shark_direction, y - 22 + ey);
    }
    //glVertex2f((300)*-1*shark_direction + ex, 265 + ey);
    glEnd();
    //this is the mouth portion
    glColor3ub(138, 3, 3);
    glBegin(GL_POLYGON);
    glVertex2f(ex + shark_direction*29.8, ey - 24);
    glVertex2f(ex + shark_direction*1.8, ey - 11);
    glVertex2f(ex + shark_direction*34.8, ey - 19);
    glEnd();

    //For Shark Tail
    glColor3ub(115, 116, 117);
    glBegin(GL_POLYGON);

    glVertex2f(ex + 266.2*-1*shark_direction, ey - 1.4);
    glVertex2f(ex + 308.2*-1*shark_direction, ey + 43);

    glColor3ub(rand() % 40 + 190, rand() % 40 + 190, rand() % 40 + 190);

    glVertex2f(ex + 296.2*-1*shark_direction, ey - 12);
    glVertex2f(ex + 308.2*-1*shark_direction, ey - 67);
    glVertex2f(ex + 266.2*-1*shark_direction, ey - 22);

    glEnd();

    glColor3ub(100, 106, 107);
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(ex + 78.2*-1*shark_direction, ey + 26);

    glColor3ub(150, 150, 150);

    glVertex2f(ex + 128.2*-1*shark_direction, ey + 73);
    glVertex2f(ex + 143.2*-1*shark_direction, ey + 26);
    glEnd();

    glColor3ub(115, 116, 117);
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(ex + 88.2*-1*shark_direction, ey - 27);
    glVertex2f(ex + 118.2*-1*shark_direction, ey - 77);

    glColor3ub(rand() % 40 + 190, rand() % 40 + 190, rand() % 40 + 190);
    glVertex2f(ex + 128.2*-1*shark_direction, ey - 27);
    glEnd();

    // ... (other parts of the shark's body)

    glBegin(GL_TRIANGLE_FAN);
    for (angle = 0; angle < 360.0; angle += 0.1) {
        glColor3ub(0, 0, 0);
        y = (sin(angle * pi / 180) * 5);
        x = (cos(angle * pi / 180) * 5);
        glVertex2f((x + 0.2)*-1*shark_direction + ex, y + ey);
    }
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(ex,ey);
    glEnd();
}

void helloF()

{

    glClear(GL_COLOR_BUFFER_BIT);

    pb1();

    pb2();

    pb();

    plant();

    // Shark();

}

void init()

{

    glClearColor(0.529, 0.769, 1, 0.529);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0, 800, 0, 800);

}

void screen()

{

glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1.0,0.0,0.0);

drawstring(310,425,0.0,"American International University Bangladesh",1);

glColor3f(0.0,0.0,0.0);

drawstring(245,385,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",1);

glColor3f(0.6,1.0,0.0);

drawstring(210,350,0.0,"A MINI PROJECT ON COMPUTER GRAPHICS AND VISUALIZATION",1);

glColor3f(1.0,1.0,0.0);

drawstring(440,300,0.0,"MEGLADON",1);

glColor3f(1.0,0.0,0.0);

drawstring(135,205,0.0," STUDENT NAME",0);

glColor3f(0.0,0.0,0.0);

// displaying student name
drawstring(140,170,0.0,"Zilani Khan",0);
drawstring(140,135,0.0,"Ayesha Mehjaben Tonima",0);
drawstring(140,100,0.0,"Ayesha Din Jannat",0);

glColor3f(1.0,0.0,0.0);

drawstring(710,205,0.0,"Under the Guidance of",0);

glColor3f(0.0,0.0,0.0);

drawstring(720,170,0.0,"Rahul Biswas",0);

glColor3f(1.0,1.0,0.0);

drawstring(456,95,0.0,"Academic Year 2023-24",0);

drawstring(460,65,0.0,"Press 'ESC' to start",0);
drawstring(460,35,0.0,"Press 'p' to pause",0);

glFlush();

glutSwapBuffers();

}

void reshape(GLint w, GLint h)

{

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    if(h>w)

        gluOrtho2D(0, 500, ((float)h/(float)w)*(0), ((float)h/(float)w)*500);

    else

        gluOrtho2D(((float)w/(float)h)*(0), ((float)w/(float)h)*(520), 0, 500);

    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();

}

void drawFish(float b, float bb)
{
    // Fish body
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(fish_direction*(-80) + b, -4 + bb); //A
    glVertex2f(fish_direction*(-130) + b, -29 + bb); //B
    glVertex2f(fish_direction*(-120) + b, -4 + bb); //C
    glVertex2f(fish_direction*(-130) + b, 21 + bb); // D
    glEnd();

    // Fish tail
    glColor3f(1.0, 0.357, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(fish_direction*(-85) + b, -4 + bb);
    glVertex2f(fish_direction*(-25) + b, 21 + bb);
    glVertex2f(fish_direction*(15) + b, -4 + bb);
    glVertex2f(fish_direction*(-25) + b, -29 + bb);
    glEnd();

    // Fish fin 1
    glBegin(GL_TRIANGLES);
    glVertex2f(fish_direction*(-24) + b, 19 + bb);
    glColor3f(0.0,0.0,0.0);
    glVertex2f(fish_direction*(-40) + b, 6 + bb);
    glVertex2f(fish_direction*(-65) + b, 46 + bb);
    glEnd();

    // Fish fin 2
    glBegin(GL_TRIANGLES);
    glVertex2f(fish_direction*(-24) + b, -27 + bb);
    glColor3f(fish_direction*0.0, 0.0, 0.0);
    glVertex2f(fish_direction*(-40) + b, -13 + bb);
    glVertex2f(fish_direction*(-65) + b, -54 + bb);
    glEnd();

    // Fish eye
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(b,bb);
    glEnd();
}






void pbSmall()

{

    glBegin(GL_TRIANGLE_FAN);

    for(angle=0; angle<360.0; angle+=.1)
    {

        glColor3ub(46,47,47);

        y =(sin(angle*pi/180)*30);

        x =(cos(angle*pi/180)*50);

        glVertex2f(x+150,y-5);

    }

    glEnd();

}

void pb()
{

    pbSmall();

    glBegin(GL_TRIANGLE_FAN);

    for(angle=0; angle<360.0; angle+=.1)
    {

        glColor3ub( 142,20,30);

        y =(sin(angle*pi/180)*45);

        x =(cos(angle*pi/180)*75);

        glVertex2f(x+250,y-10);

    }

    glEnd();

}


void pb1()

{

    glBegin(GL_TRIANGLE_FAN);

    for(angle=0; angle<360.0; angle+=.1)
    {

        glColor3ub( 20,20,20);

        y =(sin(angle*pi/180)*35);

        x =(cos(angle*pi/180)*65);

        glVertex2f(x+370,y-5);

    }

    glEnd();

}

void pb2()

{

    glBegin(GL_TRIANGLE_FAN);

    for(angle=0; angle<360.0; angle+=.1)
    {

        glColor3ub(36, 60, 2);

        y =(sin(angle*pi/180)*40);

        x =(cos(angle*pi/180)*75);

        glVertex2f(x+610,y+10);

    }

    glEnd();

}

void circleFunc(float yc, int d, int x1, int y1)

{

    for(angle=0; angle<360.0; angle+=.1)

    {

        y =yc+(sin(angle*pi/180)*d);

        x =(cos(angle*pi/180)*d);

        glVertex2f(x+x1,y-y1);

    }

}

float checkBubPos(float y, float c)

{

    if(y<500)
    {

        return y+c;

    }

    else
    {

        return 0;

    }

}

void circle(int x)

{

    //to draw circles

    glBegin(GL_POINTS);

    circleFunc(y21,15,x+10,30);

    circleFunc(y31,5,x,60);

    circleFunc(y41,7,x+10,90);

    circleFunc(y51,12,x,120);

    circleFunc(y61,15,x+10,150);

    circleFunc(y71,5,x,180);

    circleFunc(y81,3,x+10,210);

    circleFunc(y81,15,x,240);

    circleFunc(y91,12,x+10,270);

    circleFunc(y10,10,x,300);

    circleFunc(y12,16,x+10,330);

    circleFunc(y13,15,x,360);

    circleFunc(y14,10,x+10,400);

    glEnd();

    y11 = checkBubPos(y11,2.0);

    y21 = checkBubPos(y21,3.0);

    y31 = checkBubPos(y31,4.5);

    y41 = checkBubPos(y41,7.0);

    y51 = checkBubPos(y51,6.5);

    y61 = checkBubPos(y61,18.0);

    y71 = checkBubPos(y71,17.5);

    y81 = checkBubPos(y81,8.0);

    y91 = checkBubPos(y91,7.5);

    y10 = checkBubPos(y10,10.0);

    y12 = checkBubPos(y12,11.0);

    y14 = checkBubPos(y14,8.0);

    y12 = checkBubPos(y12,9.0);

    y13 = checkBubPos(y13,1.0);

    glutPostRedisplay();

}

void plant3L(int x1, int x2, int m)

{

    int dis = x2-x1;

    dis = dis/3;

    glColor3ub( 40,170,5);

    glBegin(GL_POLYGON);

    glVertex2f(x1,0);

    glVertex2f(x1-10,m-10);

    glColor3f(0.0,0.5,0.0);

    glVertex2f(x1+dis,15);

    glVertex2f(x1+((x2-x1)/2),m);

    glVertex2f(x2-dis,15);

    glVertex2f(x2+12,m+10);

    glVertex2f(x2,0);

    glEnd();

}

void plant2L(int x1, int x2, int h1, int h2)

{

    glColor3ub( 60,170,15);

    glBegin(GL_POLYGON);

    glVertex2f(x1,0);

    glVertex2f(x1-20,h1);

    glColor3f(0.0,0.3,0.0);

    glVertex2f(x2,0);

    glVertex2f(x1+15,h2);

    glEnd();

}

void plant()

{

    plant2L(50,40,40,60);

    plant2L(95,85,50,60);

    plant2L(120,110,45,65);

    plant2L(70,60,60,40);

    plant2L(140,130,43,60);

    plant2L(950,940,40,50);

    plant2L(870,860,50,60);

    plant2L(470,460,40,50);

    plant2L(490,480,55,65);

    plant2L(520,510,40,50);

    plant2L(540,530,50,60);

    plant2L(700,690,40,50);

    plant2L(730,720,55,65);

    plant2L(795,785,40,50);

    plant3L(10,20,60);

    plant3L(160,170,50);

    plant3L(310,320,70);

    plant3L(435,445,60);

    plant3L(750,760, 55);

    plant3L(820,830,80);

    plant3L(900,910, 55);

}

// adding the hill function
void drawHill()
{
    glBegin(GL_POLYGON);
    glColor3f(0.039,0.301,0.407); // Light blue color for the top of the hill
    // glVertex2f(-100.5, 0.0); // ignore
    // glVertex2f(100.5, 400.0);
    // glVertex2f(0.0, 400.5);
    glVertex2f(0.0, 200);
    glVertex2f(100, 250);
    //  glColor3f(0.04, 0.21,0.4156); // deep  blue color for the top of the hill
    glVertex2f(200, 100);
    glVertex2f(250.0, 120);
    glVertex2f(280.0, 110.0);
    //  glColor3f(0.004, 0.454, 0.745); // Light blue color for the top of the hill
    glVertex2f(300.0, 250);
    glVertex2f(400.0, 115.0);
    glVertex2f(420.0, 120);
    //  glColor3f(0.04, 0.21,0.4156); // deep  blue color for the top of the hill

    glVertex2f(610.0, 0);
    glVertex2f(0, 0);
    glVertex2f(0.0, 200);

    glEnd();
}

void drawHill2()
{
    glBegin(GL_POLYGON);
    glColor3f(0.031,0.513,0.584); // Light blue color for the top of the hill

    glVertex2f(420.0, 0);
    glVertex2f(600, 175);
    //  glColor3f(0.039, 0.431,0.741); // deep  blue color for the top of the hill
    glVertex2f(650, 185);
    glVertex2f(680.0, 150);
    glVertex2f(840.0, 200.0);
    //  glColor3f(0.352, 0.588, 0.890); // Light blue color for the top of the hill
    glVertex2f(900.0, 160);
    glVertex2f(960.0, 200.0);
    glVertex2f(1050.0, 140);
    //  glColor3f(0.039, 0.431,0.741); // deep  blue color for the top of the hill

    glVertex2f(1050.0, 0);
    glVertex2f(420, 0);


    glEnd();
}

void drawHill3()
{
    glBegin(GL_POLYGON);
    glColor3f(0.031,0.513,0.584); // Light blue color for the top of the hill

    glVertex2f(300.0, 0);
    glVertex2f(420, 100);
    glVertex2f(480, 85);
    glVertex2f(550.0, 150);
    glVertex2f(840.0, 0);
    glVertex2f(300.0, 0);



    glEnd();
}

void drawHill4()
{
    glBegin(GL_POLYGON);
    glColor3f(0.427, 0.725, 0.937); // Light blue color for the top of the hill

    glVertex2f(0.0, 0);
    glVertex2f(420, 300);
    glVertex2f(610, 250);
    glVertex2f(650.0, 320);
    glVertex2f(1050.0, 0);
    glVertex2f(0.0, 0);



    glEnd();
}

void display(void)

{

    glClear(GL_COLOR_BUFFER_BIT);

    if(game_finished == 0)
    {
    //first check if shark has eaten any of the fish
    for(int i =0 ;i<5;i++)
    {
        if(fishes[i].disappearing_interval == 0)
        {

           //gettting the fish tail and eue variables
           double fish_tail_x = fish_direction*(-85) + fishes[i].x + x_change;
           double fish_tail_y = fishes[i].y + y_change - 4;
           double fish_eye_x = fishes[i].x + x_change;
           double fish_eye_y = fishes[i].y + y_change;

           //now get the mouth position of the shark
           double shark_mouth_upper_x = shark_pos_x + shark_direction*34.8;
           double shark_mouth_upper_y = shark_pos_y - 19;

           double shark_mouth_lower_x = shark_pos_x + shark_direction*29.8;
           double shark_mouth_lower_y = shark_pos_y - 24;

           double shark_mouth_middle_x = (shark_mouth_lower_x + shark_mouth_upper_x)/2;
           double shark_mouth_middle_y = (shark_mouth_lower_y + shark_mouth_upper_y)/2;
           // now check if the fish is between the eye position of the fish and the tail position of the fish
           if(((shark_mouth_middle_x > fish_tail_x && shark_mouth_middle_x < fish_eye_x) || (shark_mouth_middle_x > fish_eye_x && shark_mouth_middle_x < fish_tail_x)) && ((abs(shark_mouth_middle_y - fish_eye_y)<10) || (abs(shark_mouth_middle_y - fish_tail_y)<10)))
           {
                //shark has eaten the fish
                fishes[i].disappearing_interval = 1200;
                game_score ++;
           }
        }
    }
    }

    drawHill4();

    drawHill3();

    drawHill2();

    drawHill();

    //drawing the first sand
    // sand_big();
    drawGradientOval(1100,10,160,100,60); //(center_x,center_y,radius_x,radius_y,number_of_segments)
    drawGradientOval(900,10,90,60,60);
    drawGradientOval(800,10,80,40,60);
    drawGradientOval(700,10,70,30,60);
    drawGradientOval(600,0,70,25,60);
    drawGradientOval(500,0,70,20,60);
    drawGradientOval(400,0,70,15,60);
    drawGradientOval(300,0,70,10,60);
    drawGradientOval(200,0,50,8,60);
    drawGradientOval(100,0,50,8,60);
    drawGradientOval(0,0,50,8,60);

    plant();

    int eaten_fish_count = 0;
    for(int i=0;i<5;i++)
    {
        if(fishes[i].disappearing_interval == 0)
        {
           drawFish(fishes[i].x+x_change,fishes[i].y+y_change);

        }
        else if(fishes[i].disappearing_interval != 0 && game_finished == 0)
        {
        fishes[i].disappearing_interval --;
        eaten_fish_count ++;
        }
    }
    // now adjust the shark speed according to the current number of eaten fishes, the more shark eats fishes, the more the speed of the shark decreases
    shark_speed = shark_highest_speed - eaten_fish_count*0.4;

    // Shark();
    Shark(shark_pos_x, shark_pos_y , 10);


    glColor3f(1.0, 1.0, 1.0);

    glPointSize(2.0);

    circle(30);

    circle(930);

    // showing scores
    glColor3f(1.0, 1.0, 1.0);

    if (home_screen_show == 0 && game_finished == 0)
    {
       screen();

    }
    if(game_finished == 1)
    {
        // Convert the score to a string
        std::string scoreString = "Your Score: " + std::to_string(game_final_score);
        const char* scoreCString = scoreString.c_str();
        // drawstring(score_x,score_y,0,scoreCString,1);
        // gameFinishedScreen();
        glColor3f(1.0,1.0,0.0);

        drawstring(456,125,0.0,"Game Finished",0);

        // drawstring(460,65,0.0,"Your SCORE = ",1);
        drawstring(460,95,0.0,scoreCString,1);
        drawstring(460,35,0.0,"Press 'Enter' to exit",0);

        if(game_final_score >= minimum_score)
        {
            //you won
            glColor3f(15.0/255.0,247.0/255.0,7.0/255.0);
            drawstring(456,65,0.0,"You Won",1);
        }
        else
        {
            //you lose
            glColor3f(250.0/255.0,28.0/255.0,7.0/255.0);
            drawstring(456,65,0.0,"You Lost",1);
        }

        //glFlush();

        //glutSwapBuffers();
    }
    // showing the remaining time
    int minute_remaining = (int)(time_remaining)/60;
    int second_remaining = (int)time_remaining - (minute_remaining * 60);
    std::string timeString = "Time Remaining: " + std::to_string(minute_remaining) + " : " +std::to_string(second_remaining);
    const char* timeCString = timeString.c_str();

    //showing remaining time
    if(time_remaining < 15)
    {
        glColor3f(1.0,0,0);
    }
    else
    {
    glColor3f(0,0,0);

    }
    drawstring(0,470,0.0,timeCString,1);

    std::string currentScoreString = "Score: " + std::to_string(game_score);
    const char* currentScoreCString = currentScoreString.c_str();

    //showing scores
    if(game_score >= minimum_score)
    {
        glColor3f(7.0/255.0,122.0/255.0,17.0/255.0);
    }
    else
    {
        glColor3f(1.0,0,0);

    }

    drawstring(0,420,0.0,currentScoreCString,1);


    glFlush();

    glutSwapBuffers();

}

void gameFinishedScreen()
{

glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1.0,0.0,0.0);

drawstring(310,425,0.0,"American International University Bangladesh",1);

glColor3f(0.0,0.0,0.0);

drawstring(245,385,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",1);

glColor3f(0.6,1.0,0.0);

drawstring(210,350,0.0,"A MINI PROJECT ON COMPUTER GRAPHICS AND VISUALIZATION",1);

glColor3f(1.0,1.0,0.0);

drawstring(440,300,0.0,"MEGLADON",1);

glColor3f(1.0,0.0,0.0);

drawstring(135,205,0.0," STUDENT NAME",0);

glColor3f(0.0,0.0,0.0);

// displaying student name
drawstring(140,170,0.0,"Zilani Khan",0);
drawstring(140,135,0.0,"Ayesha Mehjaben Tonima",0);
drawstring(140,100,0.0,"Ayesha Din Jannat",0);

glColor3f(1.0,0.0,0.0);

drawstring(710,205,0.0,"Under the Guidance of",0);

glColor3f(0.0,0.0,0.0);

drawstring(720,170,0.0,"Rahul Biswas",0);

glColor3f(1.0,1.0,0.0);

drawstring(456,95,0.0,"Game Finished",0);

drawstring(460,65,0.0,"Your SCORE = ",1);
drawstring(460,35,0.0,"Press 'Enter' to exit",0);

glFlush();

glutSwapBuffers();

}


void drawstring(float x, float y, float z, const char *string, int f)

{

    const char *c;

    glRasterPos3f(x, y, z);

    for (c = string; *c != '\0'; c++)

    {

        if (f == 0)

            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

        else

            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    }

}

