#include <windows.h>

#include <cmath>
#include <iostream>

#include "glut.h"
using namespace std;

// 五個自由度變數
float theta = 0.0f;  // 旋轉角度
float x = 0.0f;      // X 平移
float y = 0.0f;      // Y 平移
float h = 0.2f;      // 垂直連桿高度
float l = 0.2f;      // 底部支腳間距

//--------------------------------------------------------------------//
void idle();
void init();
void display();
void draw_cube();

void myMenu(int id);
void reshape(int w, int h);
void keyboard(unsigned char key, GLint x, GLint y);

int main(int argc, char **argv) {
    // 初始化 GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HW_03");

    // 回呼函式
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    init();
    glutMainLoop();
    return 0;
}

void myMenu(int id) {
    switch (id) {
        case 11:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void Xdirection(int id) {
    switch (id) {
        case 1:
            x += 0.1f;
            break;
        case 2:
            x -= 0.1f;
            break;
    }
}

void Ydirection(int id) {
    switch (id) {
        case 3:
            y += 0.1f;
            break;
        case 4:
            y -= 0.1f;
            break;
    }
}

void ArmRotation(int id) {
    switch (id) {
        case 5:
            theta += 5.0f;
            break;
        case 6:
            theta -= 5.0f;
            break;
    }
}

void GripperHeight(int id) {
    switch (id) {
        case 7:
            h = max(0.1f, h - 0.05f);
            break;  // 最小不要低於 0.1
        case 8:
            h = min(h + 0.05f, 0.6f);
            break;
    }
}

void GripperControl(int id) {
    switch (id) {
        case 9:
            l = min(l + 0.05f, 0.4f);
            break;
        case 10:
            l = max(0.1f, l - 0.05f);
            break;
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);

    // 建立右鍵選單
    int _Xdirection = glutCreateMenu(Xdirection);
    glutAddMenuEntry("Increase", 1);
    glutAddMenuEntry("Decrease", 2);

    int _Ydirection = glutCreateMenu(Ydirection);
    glutAddMenuEntry("Increase", 3);
    glutAddMenuEntry("Decrease", 4);

    int _ArmRotation = glutCreateMenu(ArmRotation);
    glutAddMenuEntry("Clockwise", 5);
    glutAddMenuEntry("CounterClockwise", 6);

    int _GripperHeight = glutCreateMenu(GripperHeight);
    glutAddMenuEntry("Up", 7);
    glutAddMenuEntry("Down", 8);

    int _GripperControl = glutCreateMenu(GripperControl);
    glutAddMenuEntry("Open", 9);
    glutAddMenuEntry("Close", 10);

    glutCreateMenu(myMenu);
    glutAddSubMenu("X direction", _Xdirection);
    glutAddSubMenu("Y direction", _Ydirection);
    glutAddSubMenu("Arm Roattion", _ArmRotation);
    glutAddSubMenu("Gripper Height", _GripperHeight);
    glutAddSubMenu("Gripper Control", _GripperControl);

    glutAddMenuEntry("Exit", 11);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    gluPerspective(60.0, aspect, 0.1, 50.0);

    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // 1) 設 Camera
    gluLookAt(5.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // 繪出三軸
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -2.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -2.0);
    glVertex3f(0.0, 0.0, 2.0);
    glEnd();

    // 全局平移
    glTranslatef(x, y, 0.0f);

    // 第一段基座
    glTranslatef(0.2f, 0.2f, 0.0f);
    glPushMatrix();
    glScalef(0.4f, 0.4f, 0.4f);
    draw_cube();
    glPopMatrix();

    // 第二段手臂 (加入旋轉θ)
    glTranslatef(0.0f, 0.5f, 0.0f);
    glRotatef(theta, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glScalef(0.2f, 0.6f, 0.2f);
    draw_cube();
    glPopMatrix();

    // 第三段手臂
    glTranslatef(0.5f, 0.2f, 0.0f);
    glPushMatrix();
    glScalef(0.8f, 0.2f, 0.2f);
    draw_cube();
    glPopMatrix();

    // 第四段
    glTranslatef(0.3f, -0.2f, 0.0f);
    glPushMatrix();
    glScalef(0.2f, 0.2f, 0.2f);
    draw_cube();
    glPopMatrix();

    // 第五段垂直連桿 (高度由 h 控制)
    glTranslatef(0.0f, -(0.1f + h / 2.0f), 0.0f);
    glPushMatrix();
    glScalef(0.1f, h, 0.1f);
    draw_cube();
    glPopMatrix();

    // 支撐橫樑
    glTranslatef(0.0f, -(h / 2.0f) - 0.05f, 0.0f);
    glPushMatrix();
    glScalef(0.6f, 0.1f, 0.1f);
    draw_cube();
    glPopMatrix();

    // 左右支腳 (間距由 l 控制)
    glPushMatrix();
    glTranslatef(l / 2.0f, -0.15f, 0.0f);
    glScalef(0.1f, 0.2f, 0.1f);
    draw_cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-l / 2.0f, -0.15f, 0.0f);
    glScalef(0.1f, 0.2f, 0.1f);
    draw_cube();
    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, GLint x, GLint y) {
    if (key == 'q' || key == 'Q') exit(0);
}

void draw_cube() {
    glBegin(GL_QUADS);
    // 前面
    glColor3f(1, 0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // 後面
    glColor3f(0, 1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // 左面
    glColor3f(0, 0, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // 右面
    glColor3f(1, 1, 0);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // 上面
    glColor3f(1, 0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    // 下面
    glColor3f(0, 1, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
}
