#include <iostream>
#include <cmath>
#include "glut.h"
using namespace std;
int n;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);

    glLoadIdentity();
    gluOrtho2D(-0.5, 0.5, -0.5, 0.5);
}// 


void display() {
    float theta;
    float radius = 0.25; // 正多邊形的半徑

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP); // 使用線段連接頂點

    for (int i = 0; i < n; i++) {
        theta = 2.0f * 3.1415926f * i / n; // 計算角度
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    cout << "input parameter：";
    cin >> n;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("Regular Polygon");
        glutDisplayFunc(display);
        init();
        glutMainLoop();
    
}


