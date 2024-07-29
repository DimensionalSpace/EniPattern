in vec2 fragTexCoord;

uniform sampler2D texture;

void main() {
    
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    
    float correctedRed = pixel.r * 0.95 + pixel.g * 0.5;
    float correctedGreen = pixel.g * 0.43333 + pixel.b * 0.56667;
    float correctedBlue = pixel.b * 0.525 + pixel.g * 0.475;

    
    gl_FragColor = vec4(correctedRed, correctedGreen, correctedBlue, pixel.a);
}