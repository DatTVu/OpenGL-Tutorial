attribute vec3 a_posL;
attribute vec3 a_normal;
attribute vec3 a_binormal;
attribute vec3 a_tangent;
attribute vec2 a_texCoord;

uniform mat4 u_WVP;
varying vec2 textCoord;
varying vec4 tempPos;

void main()
{
vec4 posL = vec4(a_posL, 1.0) ;
gl_Position = u_WVP* posL;
textCoord = a_texCoord;
tempPos = vec4(a_posL.xyz, 1.0);
}
   