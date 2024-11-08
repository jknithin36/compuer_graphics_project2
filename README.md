# compuer_graphics_project2

![Alt text](./assets/Screenshot%202024-11-08%20at%2010.59.38 AM.png)
![Alt text](./assets/Screenshot%202024-11-08%20at%2011.00.13 AM.png)

g++ -std=c++11 Main.cpp Application.cpp Ray_Tracer.cpp scene/Scene.cpp scene/view_plane.cpp util/RayTracingUtil.cpp util/SceneUtil.cpp primitives/MyObject.cpp primitives/Wall.cpp primitives/Triangle.cpp primitives/Sphere.cpp Imageio/Imageio.cpp common/math3d.cpp scene/Light.cpp -o RayTracer -framework OpenGL -framework GLUT -L/opt/homebrew/opt/glfw/lib -I/opt/homebrew/opt/glfw/include -L/opt/homebrew/opt/glew/lib -I/opt/homebrew/opt/glew/include -lglfw -lGLEW -DGL_SILENCE_DEPRECATION

./RayTracer
