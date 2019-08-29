uniform float height;
uniform float width;
uniform float zoom_factor;
uniform int max_iterations;

float AbsComplex(vec2 c)
{
    // use of idenity
    // a + bi == sqrt(a^2 + b^2)
    return sqrt(c[0] * c[0] + c[1] * c[1]);
}

void main()
{
    // iterating values
    int iter;
    float i = gl_FragCoord[2];
    float j = gl_FragCoord[1];
    // represent complex numbers in 2d vector
    vec2 point, c;


            point = vec2(j / width * zoom_factor - 1.5,
            j / height * zoom_factor -1.2);
            c = vec2(0, 0);

            for (iter = 0; AbsComplex(c) < 2.0 && iter < max_iterations; ++iter) {
                c = c * c + point;
            }

            if (iter >= max_iterations)
            {
                gl_FragColor = vec4(0, 0, 0, 1.0);
            }
            else
            {
                gl_FragColor = vec4((255*iter)/500, (255*iter)/300, (255*iter)/30, 1.0);
            }

}