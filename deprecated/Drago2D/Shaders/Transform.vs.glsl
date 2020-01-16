#version 130

in vec4 iPos;

uniform mat4 uMVP;

void main()
{
    gl_Position = iPos * uMVP;
}