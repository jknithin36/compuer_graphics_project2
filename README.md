# Advanced Computer Graphics - Project 2

[Link to Project 1 Repository](https://github.com/jknithin36/compuer_graphics)

## 📚 Overview

In Project 2, I extended the ray tracer by adding a new 3D geometric object with a triangle mesh. This enhancement involved loading an object in `.OBJ` format, integrating it into the scene by replacing a few spheres, and applying geometric transformations and local shading for realistic rendering.

## HOW TO EXECUTE

### Prerequisites

- Ensure you have the necessary libraries installed, including OpenGL and GLUT.
- For macOS, you may need to install Homebrew to install these libraries:

  ```bash
  brew install glew glfw
  ```

Compilation Steps
Open your terminal and navigate to the project directory.

Use the following command to compile the code:

````bash
`g++ -std=c++11 Main.cpp Application.cpp Ray_Tracer.cpp scene/Scene.cpp scene/view_plane.cpp util/RayTracingUtil.cpp util/SceneUtil.cpp primitives/MyObject.cpp primitives/Wall.cpp primitives/Triangle.cpp primitives/Sphere.cpp Imageio/Imageio.cpp common/math3d.cpp scene/Light.cpp -o RayTracer -framework OpenGL -framework GLUT -L/opt/homebrew/opt/glfw/lib -I/opt/homebrew/opt/glfw/include -L/opt/homebrew/opt/glew/lib -I/opt/homebrew/opt/glew/include -lglfw -lGLEW -DGL_SILENCE_DEPRECATION`


After successful compilation, run the program with:
```bash
`./RayTracer`

Execution Screenshot:

![Alt text](./assets/Screenshot%202024-11-08%20at%2011.26.02 AM.png)
![Alt text](./assets/Screenshot%202024-11-08%20at%2011.00.13 AM.png)
````
