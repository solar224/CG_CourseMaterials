# GC\_project

## 方案平台

- 平台架構：X86

## 使用須知

1. 安裝以下五個環境檔案：

   - `glut.dll`
   - `glut.h`
   - `glut.lib`
   - `glut32.dll`
   - `glut32.lib`

2. 確保這些檔案放置在對應的系統目錄：

   - `.dll` 檔案應放入 `C:\Windows\System32\`（對於 32 位元應用程式）或 `C:\Windows\SysWOW64\`（對於 64 位元應用程式）。
   - `.lib` 檔案應放入開發工具的 `lib` 目錄。
   - `.h` 檔案應放入開發工具的 `include` 目錄。

3. 確認開發環境的 `Library Path` 和 `Include Path` 正確設定，以便編譯器能夠找到對應的函式庫與標頭檔案。

## OpenGL 介紹

OpenGL（Open Graphics Library）是一個硬體無關的圖形 API，提供超過 700 個函數，可用於 2D 和 3D 圖形繪製。

### OpenGL 核心函式庫

- `GL`：OpenGL 核心函式庫
- `GLU`：OpenGL 輔助函式庫，提供基礎幾何物件建立
- `GLUT`：OpenGL 公用工具函式庫，負責視窗管理與互動功能

### OpenGL 開發環境設定步驟

1. 下載並解壓 OpenGL 函式庫。
2. 建立 Visual Studio Win32 Console Application 專案。
3. 將所有相關檔案放入專案目錄。
4. 設定平台為 `x86`。

## OpenGL 基本函式

### 視窗管理

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

### 繪圖函式

```cpp
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
```

### 視窗設定

```cpp
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}
```

## 其他注意事項

- 若在執行時出現 `glut.dll` 找不到的錯誤，可嘗試手動將該檔案放置於專案執行目錄。
- 若使用 Visual Studio，請確認專案設定已正確鏈接 `glut.lib` 和 `glut32.lib`。
- 建議使用 `glViewport(x, y, width, height);` 來調整視口，避免畫面變形。

