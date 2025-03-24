## 課程大綱
1. 簡介
2. OpenGL API
3. 基本元素與屬性
4. OpenGL視圖
5. 2D範例：Sierpinski Gasket

---

## 一、簡介

### 圖學系統介面
- **輸入介面**：函式呼叫與輸入裝置測量
- **輸出介面**：查詢資料與顯示圖形

### API類型
- Windows API：作業系統相關
- Graphics API：
  - 基本元素
  - 轉換函式
  - 視圖函式

---

## 二、OpenGL API

### 基本知識
- 硬體獨立的圖學函式庫
- GL：核心函式庫
- GLU：公用函式庫（基於GL）
- GLUT：提供與視窗系統互動功能

### 基本架構程式碼
```c
#include "glut.h"
int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(500,500);
  glutCreateWindow("simple");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
```

### 基本函式
- **glClear()**：清除視窗
- **glFlush()**：執行繪圖命令
- **glClearColor()**：設定清除顏色
- **glColor3f()**：設定繪圖顏色

---

## 三、基本元素與屬性

### 基本元素
- 光柵元素（Raster）：像素陣列
- 幾何元素（Geometric）：點、線段、三角形

#### 幾何元素定義方式
```c
glBegin(type);
  glVertex*();
  // 其他頂點
  glVertex*();
glEnd();
```

### 幾何基本元素類型
- 點 (**GL_POINTS**)
- 線段 (**GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP**)
- 多邊形 (**GL_POLYGON, GL_TRIANGLES, GL_QUADS**)

### 屬性
- **顏色模型**
  - RGB顏色模型
  - 索引顏色模型

- **線條樣式**
  - 使用 `glLineStipple()` 和 `glEnable(GL_LINE_STIPPLE)` 設定

---

## 四、OpenGL 視圖

### 正投影視圖 (Orthographic View)
- OpenGL 預設的視圖模式
- 透過函式 `glOrtho()` 設定

### 二維視圖
- 使用 `gluOrtho2D(left, right, bottom, top)` 設定視圖矩形

### 縱橫比 (Aspect Ratio)
- 為避免影像變形，視圖矩形與顯示視窗應具相同比例
- 使用函式 `glViewport(x, y, width, height)` 調整

---

## 五、2D範例：Sierpinski Gasket

### 描述
- 分形幾何應用，透過隨機與遞迴方式生成

### 建構過程
1. 選擇初始點
2. 隨機選擇一個頂點
3. 在中間位置繪製點
4. 將該中點作為新點
5. 重複步驟2

### 範例程式碼
```c
void display(){
  GLfloat vertices[3][2] = {{0.0,0.0},{25.0,50.0},{50.0,0.0}};
  GLfloat p[2] = {25.0, 25.0};
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);
  for(int k = 0; k < 10000; k++){
    int j = rand() % 3;
    p[0] = (p[0]+vertices[j][0])/2;
    p[1] = (p[1]+vertices[j][1])/2;
    glVertex2fv(p);
  }
  glEnd();
  glFlush();
}
```
