uniform float height;
uniform float width;
uniform float zoom_factor;
uniform int max_iterations;
uniform float k_shift;
uniform float h_shift;

uniform sampler2D texture;

struct ComplexNum
{
    float real;
    float img;
};

float AbsComplex(ComplexNum c)
{
    // use of idenity
    // a + bi == sqrt(a^2 + b^2)
    return sqrt(c.real * c.real + c.img * c.img);
}

void main()
{
    int iter;
    float i = gl_FragCoord.y;
    float j = gl_FragCoord.x;
    // represent complex numbers in 2d vector
    ComplexNum point = ComplexNum(j / width * zoom_factor - h_shift,
                                  i / height * zoom_factor - k_shift);
    ComplexNum c = ComplexNum(0.0, 0.0);
    ComplexNum temp;

    for (iter = 0; AbsComplex(c) < 2.0 && iter < max_iterations; ++iter) {
        // (a+bi)^2 + (c+di)
        // a^2 + 2abi -b^2 + c + di
        // (a^2 - b^2 + c) + (2ab + d)i
        temp = c;
        c.real = (temp.real * temp.real) - (temp.img * temp.img) + point.real;
        c.img = (2.0 * temp.real * temp.img) + point.img;
    }

    if (iter >= max_iterations)
    {
        gl_FragColor = vec4(0, 0, 0, 1.0);
    }
    else
    {
        gl_FragColor = vec4(float(iter)/500., float(iter)/300., float(iter)/30., 1.0);
    }

}