## 課程大綱
1. 簡介
2. 表示法
3. 仿射轉換
4. 轉換串接
5. OpenGL轉換矩陣

---

## 一、簡介

### 幾何學
- 研究空間物件之間的關係。
- 在電腦圖學中，以三維空間物件為主。

### 座標系統
- 用於解決物體參考的問題。
- 基本幾何關係不依賴座標系統。

### 三維基本元素
- 三維物件可透過表面描述、頂點集合指定，並以凸多邊形逼近。

---

## 二、表示法

### 坐標轉換
- 轉換座標系統基底向量以進行表示。

### 齊次坐標 (Homogeneous Representation)
- 以4D矩陣表示點和向量，便於進行仿射轉換。

---

## 三、仿射轉換

### 基本仿射轉換
1. **平移 (Translation)**
2. **旋轉 (Rotation)**
3. **縮放 (Scaling)**
4. **錯切 (Shear)**

### 特性
- 平移與旋轉為剛體轉換，不改變物體形狀。
- 縮放與錯切為非剛體轉換，會改變物體形狀。

### 注意
- 旋轉具有非交換性。
- 所有旋轉與縮放的基準點預設為原點。

---

## 四、轉換串接

### 固定點旋轉
- 將物體移動到原點後旋轉，再移回原處。

### 實例轉換
- 用於設定物體實例的大小、位置與方向。
- 一般執行順序為：縮放 → 旋轉 → 平移。

---

## 五、OpenGL轉換矩陣

### OpenGL座標系統
- 六個座標系統：
  - 物件、世界、相機、裁切、正規化設備、視窗座標。

### 目前轉換矩陣 (CTM)
- 透過函式設定轉換模式：
  ```c
  glMatrixMode(GL_MODELVIEW);
  glMatrixMode(GL_PROJECTION);
  ```
- 常用轉換函式：
  ```c
  glLoadIdentity();
  glRotatef(angle, x, y, z);
  glTranslatef(dx, dy, dz);
  glScalef(sx, sy, sz);
  ```

### 轉換順序
- OpenGL 使用後乘矩陣，最後指定的轉換先執行。

### OpenGL轉換矩陣使用範例
```c
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(cx, cy, 0.0);
glRotatef(theta, 0.0, 0.0, 1.0);
```

---

## 轉換實例程式

### 固定點旋轉範例
```c
glBegin(GL_POLYGON);
for(int i = 0; i < 4; i++){
  double x = points[i][0];
  double y = points[i][1];
  double px = x * cos(theta) - y * sin(theta) + cx;
  double py = x * sin(theta) + y * cos(theta) + cy;
  glVertex2f(px, py);
}
glEnd();
```

### 多矩形繪製範例
```c
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glPushMatrix();
  glScalef(10.0, 10.0, 1.0);
  drawSquare();
glPopMatrix();
```
