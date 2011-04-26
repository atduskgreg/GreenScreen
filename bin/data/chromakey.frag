uniform sampler2D processedImage;

void main() {
  vec2 texCoord = gl_TexCoord[0].st;
  
  vec4 currentPixel = texture2D(processedImage, texCoord);
  

	gl_FragColor = currentPixel;
}
