attribute vec3 a_posL;
attribute vec2 a_texCoord;
varying vec2 textCoord;
void main()
{
gl_Position = vec4(a_posL, 1.0) ;
textCoord = a_texCoord;
}