#version 440 core

layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

void main() {

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.02, -0.02, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.0, -0.04, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}
