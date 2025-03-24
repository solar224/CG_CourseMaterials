#include <iostream>
#include <windows.h>
#include <cmath>
#include "glut.h"
#define PI 3.14159 
using namespace std;

float theta = 0.0;
float xx = 0.0;
float yy = 0.0;
bool wise = 0;

void idle();
void myMenu(int id);
void init();
void myMenu(int id);
void reshape(int x, int y);
void display();
void mouse(GLint button, GLint state, GLint x, GLint y);
void keyboard(unsigned char key, GLint x, GLint y);

int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("HW_02");

        glutDisplayFunc(display);   // 渲染畫面
        glutIdleFunc(idle);         // idle

        glutMouseFunc(mouse);       // 滑鼠
        glutKeyboardFunc(keyboard); // 鍵盤
        glutReshapeFunc(reshape);   // 改變大小

        init();
        glutMainLoop();
}


void myMenu(int id) {
    switch (id) {
    case 1: exit(0);
    }
}

void myRotation(int id) {
    switch(id) {
    case 0:
        glutIdleFunc(idle);
        break;
    case 1:
        glutIdleFunc(NULL);
        break;
    default:
        break;
    }
}

void myDirection(int id) {
    switch (id) {
    case 0:
        wise = 0;
        break;
    case 1:
        wise = 1;
        break;
    default:
        break;
    }
    glutIdleFunc(idle);
}

void myTranslation(int id) {
    switch (id) {
    case 0:
        xx += 0.1;
        break;
    case 1:
        xx -= 0.1;
        break;
    case 2:
        yy += 0.1;
        break;
    case 3:
        yy -= 0.1;
        break;
    default:
        break;
    }
    glutIdleFunc(idle);
}

void init() {   //初始

    int sub_Rotation = glutCreateMenu(myRotation);
    glutAddMenuEntry("start", 0);
    glutAddMenuEntry("Abort", 1);

    int sub_Direction = glutCreateMenu(myDirection);
    glutAddMenuEntry("Clockwise", 0);
    glutAddMenuEntry("Counterclockwise", 1);

    int sub_Translation = glutCreateMenu(myTranslation);
    glutAddMenuEntry("Increase x", 0);
    glutAddMenuEntry("Decrease x", 1);
    glutAddMenuEntry("Increase y", 2);
    glutAddMenuEntry("Decrease y", 3);


    /* set the main menu */
    glutCreateMenu(myMenu);
    glutAddSubMenu("Rotation", sub_Rotation);
    glutAddSubMenu("Direction", sub_Direction);
    glutAddSubMenu("Translation", sub_Translation);
    glutAddMenuEntry("Quit", 1);


    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glClearColor(0.0, 0.0, 0.0, 0.0);

}

void idle() {
    theta += (wise ? -1: 1);
    if (theta >= 360.0)
        theta = 0.0;

    Sleep(1);
    glutPostRedisplay();
}

void reshape(int x, int y) {

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);   // 清空 back
    // 畫紅色的座標軸
    glColor3f(1.0, 0.0, 0.0); // 設定紅色
    glBegin(GL_LINES);
    // X 軸
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    // Y 軸
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();


    glColor3f(0.0, 0.0, 1.0); // 設定藍色

    int num_segments = 200; // 控制圓滑程度

    float thetar = theta * PI / (180);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        float angle = 2.0f * 3.14159f * i / num_segments;
        float x = 0.2 * cos(angle);
        float y = 0.4 * sin(angle);

        // 旋轉橢圓
        float px, py;
        px = x * cos(thetar) + y * sin(thetar) + xx;
        py = -x * sin(thetar) + y * cos(thetar) + yy;
        glVertex2f(px, py);
    }

    glEnd();
    glFlush();
    glutSwapBuffers();
}

void mouse(GLint button, GLint state, GLint x, GLint y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            //glutIdleFunc(idle);
        break;

    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
        break;
    default:
        break;
    }//switch

}

void keyboard(unsigned char key, GLint x, GLint y) {
    if (key == 'q' || key == 'Q')
        exit(0);
}
