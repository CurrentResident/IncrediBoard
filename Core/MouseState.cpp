#include <cmath>

#include "MouseState.h"

const MouseStateType::VectorType MouseStateType::s_mouseUnitVectors[3][3] =           // [row][col]
{
    { { std::cos(M_PI * 0.75), std::sin(M_PI * 0.75) }, {  0l,  1l }, { std::cos(M_PI * 0.25), std::sin(M_PI * 0.25) } },
    { {                   -1l,                    0l }, {  0l,  0l }, {                    1l,                    0l } },
    { { std::cos(M_PI * 1.25), std::sin(M_PI * 1.25) }, {  0l, -1l }, { std::cos(M_PI * 1.75), std::sin(M_PI * 1.75) } }
};

