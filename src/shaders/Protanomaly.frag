in vec2 fragTexCoord;

uniform sampler2D texture;

void main() {
    
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    
    float correctedRed = pixel.r * 0.567 + pixel.g * 0.433;
    float correctedGreen = pixel.r * 0.558 + pixel.g * 0.442;
    float correctedBlue = pixel.b * 0.242 + pixel.g * 0.758;

    
    gl_FragColor = vec4(correctedRed, correctedGreen, correctedBlue, pixel.a);
}