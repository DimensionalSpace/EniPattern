uniform sampler2D texture;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    float averageColor = (pixel.r + pixel.g + pixel.b) / 3.0;
    gl_FragColor = vec4(averageColor, averageColor, averageColor, 1.0);
}