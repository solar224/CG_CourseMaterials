## Basic OpenGL Functions

### Window Management

```cpp
#include "glut.h"
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Simple Window");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
```

### Rendering Function

```cpp
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
```

### Window Configuration

```cpp
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}
```

## Additional Notes

- If a `glut.dll` missing error occurs at runtime, try manually placing the file in the project execution directory.
- If using Visual Studio, ensure that `glut.lib` and `glut32.lib` are correctly linked in the project settings.
- It is recommended to use `glViewport(x, y, width, height);` to adjust the viewport and avoid display distortions.
