/***********************************************
 Geometry shader to convert lines into triangle strips
 Memo Akten
 www.memo.tv

************************************************/

#version 120
#extension GL_EXT_geometry_shader4 : enable

uniform int iterations;
uniform vec3 handleA;
uniform vec3 handleB;


void main() {
    vec3 anchorA = gl_PositionIn[0].xyz;
	vec3 anchorB = gl_PositionIn[1].xyz;
    vec4 colorA = gl_FrontColorIn[0];
    vec4 colorB = gl_FrontColorIn[1];

    float detail = iterations - 1.0;
    for (int i =0 ; i<60; i++ ) {
        float percent = i/detail;
        float inversePercent = 1.0 - percent;
        float b0 = inversePercent*inversePercent*inversePercent;
        float b1 = 3.0*percent*inversePercent*inversePercent;
        float b2 = 3.0*percent*percent*inversePercent;
        float b3 = percent*percent*percent;
        
        vec3 position = b0*anchorA + b1*handleA + b2*handleB + b3*anchorB;
        gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0);
        
        vec4 c = vec4(colorA.r*inversePercent + colorB.r*percent, colorA.g*inversePercent + colorB.g*percent, colorA.b*inversePercent + colorB.b*percent, colorA.a*inversePercent + colorB.a*percent);
        gl_FrontColor = c;
        EmitVertex();

    }
    

}