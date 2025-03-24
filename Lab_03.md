## 課程大綱
1. 簡介
2. 事件驅動輸入程式設計
3. 圖形使用者介面：選單
4. 互動程式動畫

---

## 一、簡介

### 互動基本範例
Ivan Sutherland 提出 (MIT, 1963)：
1. 使用者看見物件
2. 使用輸入裝置（滑鼠、觸控筆）點選物件
3. 物件產生變化（移動、旋轉）
4. 返回第一步

### 輸入模式
- 請求模式(Request)：觸發才回傳
- 取樣模式(Sample)：立即回傳
- 事件模式(Event)：事件隨時觸發，事件存放在事件佇列

---

## 二、事件驅動輸入程式設計

### Callback 機制
- 基於事件模式
- 常用 callback 函數：
  - Display Callback
  - Mouse Callback
  - Keyboard Callback
  - Window Resizing Callback
  - Idle Callback

### 常用函式
- **glutPostRedisplay()**：要求重繪
- **glFlush()**：確保資料送入視窗緩衝區

### Callback 函數原型
- Mouse Callback
  ```c
  void mouse(GLint button, GLint state, GLint x, GLint y)
  ```

- Keyboard Callback
  ```c
  void keyboard(unsigned char key, GLint x, GLint y)
  ```

- Window Resizing Callback
  ```c
  void reshape(int w, int h)
  ```

### Callback 函式的啟用與關閉
- 動態設定 Callback 函式，例如停止旋轉動畫：
```c
glutIdleFunc(NULL);
```

---

## 三、圖形使用者介面：選單

### GLUT 選單設計
- 可建立主選單與子選單
- 以階層式方式操作

#### 範例：
```c
int sub_menu = glutCreateMenu(mySubMenu);
glutAddMenuEntry("Increase Square Size", 2);
glutAddMenuEntry("Decrease Square Size", 3);

glutCreateMenu(myMenu);
glutAddMenuEntry("Quit", 1);
glutAddSubMenu("Resize", sub_menu);
glutAttachMenu(GLUT_RIGHT_BUTTON);
```

---

## 四、互動程式動畫

### 動畫原理
- 透過連續播放圖片 (約24幀/秒) 製作動畫

### 雙緩衝區(Double Buffering)
- 前緩衝區：顯示用
- 後緩衝區：繪製用
- 確保畫面流暢，不會顯示部分完成的畫面

#### 雙緩衝程式範例
```c
int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  return 0;
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  glutSwapBuffers();
}
```
