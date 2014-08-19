#version 440 core

//The resolution of the screen being rendered to
uniform vec2 screen_resolution;

//The position of the vertices of the rectangles (pixel)
in vec2 position;
void main() {
   //gl_PointSize = 3.0;
   gl_Position = vec4(  -1.0 + (position.x/screen_resolution.x*2), -1.0 +(position.y/screen_resolution.y*2), 0.0, 1.0);
}

