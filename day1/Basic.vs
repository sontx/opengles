attribute vec3 a_position;
attribute vec2 a_uv;

varying vec2 v_uv;

void main()
{
	gl_Position = vec4(a_position, 1.0);
	v_uv = a_uv;
}