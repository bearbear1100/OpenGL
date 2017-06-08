#version 330 core
layout (location = 0) in vec3 position; // 位置變數在 0 
layout (location = 1) in vec3 color;  // 顏色變數在 1

out vec3 vertexColor; // Fragment Shader 需要輸出顏色

void main()
{
    gl_Position = vec4(position, 1.0);
    vertexColor = color; // 把 vertexColor 設定成從 Vertex Data 取進來的數據
}