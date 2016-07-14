precision mediump float;
//uniform vec3 u_color;
varying vec3 v_color;

void main()
{
	//gl_FragColor = vec4(u_color, 1.0);
	gl_FragColor = vec4(v_color, 1.0);
}
