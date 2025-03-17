# GC_project

## Platform

- Architecture: X86

## Installation Instructions

1. Install the following five environment files:

   - `glut.dll`
   - `glut.h`
   - `glut.lib`
   - `glut32.dll`
   - `glut32.lib`

2. Ensure these files are placed in the appropriate system directories:

   - `.dll` files should be placed in `C:\Windows\System32\` (for 32-bit applications) or `C:\Windows\SysWOW64\` (for 64-bit applications).
   - `.lib` files should be placed in the `lib` directory of the development tools.
   - `.h` files should be placed in the `include` directory of the development tools.

3. Verify that the `Library Path` and `Include Path` in the development environment are correctly set so the compiler can locate the corresponding libraries and header files.

## Introduction to OpenGL

OpenGL (Open Graphics Library) is a hardware-independent graphics API that provides over 700 functions for rendering 2D and 3D graphics.

### Core OpenGL Libraries

- `GL`: OpenGL Core Library
- `GLU`: OpenGL Utility Library, which provides basic geometric object creation
- `GLUT`: OpenGL Utility Toolkit, which handles window management and interaction functionality

### OpenGL Development Environment Setup

1. Download and extract the OpenGL library.
2. Create a Visual Studio Win32 Console Application project.
3. Place all relevant files into the project directory.
4. Set the platform to `x86`.

