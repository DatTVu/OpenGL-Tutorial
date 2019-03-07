precision mediump float;

uniform samplerCube u_samplerCubeMap;
uniform vec3 u_camPos; 
varying vec3 v_posW;
varying vec3 v_normW;
void main()
{
    vec3 toEye = u_camPosition - v_posW;
    vec3 reflectDir = reflect(normalize(-toEye), normalize(v_normW));  // reflect() in non linear
    gl_FragColor = textureCube(u_s_texture,reflectDir);
}