// OGL_TEST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define GTT(x) glm::to_string(x)

int main()
{
    using glm::normalize;
    using glm::vec3;

    vec3 xAxis = normalize(vec3(1, 0, 0));
    vec3 yAxis = normalize(vec3(0, 1, 0));
    vec3 zAxis = normalize(vec3(0, 0, 1));

    std::cout << "xAxis: " << GTT(xAxis) 
        << ", yAxis: " << GTT(yAxis) 
        << "zAxis: " << GTT(zAxis)
        << std::endl;

    std::cout << "angle btw xAxis and yAxi: " 
        << glm::degrees(glm::angle(xAxis, yAxis)) << std::endl;

    vec3 vector1 = normalize(vec3(0.5f, 0.5f, 0.f));
    std::cout << "angle btw vector1 and xAxis: " 
        << glm::degrees(glm::angle(vector1, xAxis)) << std::endl;

    while (true)
    {
        float x, y;
        vec3 vectort1, vectort2;
        std::cout << "\nvec1 x, y: ";
        std::cin >> x >> y;
        vectort1 = normalize(vec3(x, y, 0.0f));
        std::cout << "\nvectort1: " << GTT(vectort1);
        std::cout << "\nvec1 x, y: ";
        std::cin >> x >> y;
        vectort2 = normalize(vec3(x, y, 0.0f));

        std::cout << " vectort2: " << GTT(vectort2)
            << "\nangle btw vector1 and xAxis: " 
            << glm::degrees(glm::angle(vectort1, vectort2)) << std::endl;
    }

    std::cin.get();
    std::exit(EXIT_SUCCESS);
}

