#version 300 es
precision mediump float;

uniform sampler2D u_texture;

in vec3 v_normal;
in vec2 v_texCoord;

layout(location = 0) out vec4 fragColor;

void main() {
    if (v_normal.x > 0.0) {
        fragColor = texture(u_texture, v_texCoord);
    } else {
        fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
}
