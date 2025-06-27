#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

#include "gaussquadrature/gausslegendre.hpp"
#include "gaussquadrature/gausslobatto.hpp"
#include "gaussquadrature/quadrature.hpp"
#include "gaussquadrature/quadrature3.hpp"

using namespace flux;  // NOLINT

using quad = Quadrature;    // NOLINT(readability-identifier-naming)
using quad3 = Quadrature3;  // NOLINT(readability-identifier-naming)

namespace {
double func(double x) { return x * x; }

// x^2 + y^2
double func1(double x, double y) { return x * x + y * y; }

// x * y
double func2(double x, double y) { return x * y; }

// sin(x) * cos(y)
double func3(double x, double y) { return std::sin(x) * std::cos(y); }
}  // namespace

int demo1() {
    std::cout << std::setprecision(15);

    // (1) Gauss-Legendre 3 points
    std::cout << "Using function with Gauss-Legendre 3 points: ";
    double result = quad{quad::Builtin::Legendre3}.intg(
        std::function<double(double)>(func), {.xl = 0, .xr = 1});
    std::cout << "\nInt(x^2,{x,0,1}) = " << result << "\n";

    // (2) Gauss-Lobatto 5 points
    std::cout << "\nUsing function with Gauss-Lobatto 5 points: ";
    result = quad{quad::Builtin::Lobatto5}.intg(
        std::function<double(double)>(func), {.xl = 0, .xr = 1});
    std::cout << "\nInt(x^2,{x,0,1}) = " << result << "\n";

    std::cout << "\nUsing lambda with Gauss-Legendre 5 points: ";
    auto func1 = [](double x) { return std::sin(x); };
    result = quad{}.intg(func1, {.xl = 0, .xr = 1});
    std::cout << "\nInt(sin(x),{x,0,1}) = " << result << "\n";

    std::cout << "\nChange integration interval: ";
    result = quad{}.intg(std::function<double(double)>(func1),
                         {.xl = 0, .xr = 2 * atan(1.0)});
    std::cout << "\nInt(sin(x),{x,0,pi/2}) = " << result << "\n";

    // get points and weights via gausslegendre<N>();
    std::cout << "\nUsing Gauss-Legendre 13 points: ";
    result =
        quad{gausslegendre<13>()}.intg(func1, {.xl = 0, .xr = 2 * atan(1.0)});
    std::cout << "\nInt(sin(x),{x,0,pi/2}) = " << result << "\n";

    // get points and weights via gausslobatto(n);
    std::cout << "\nUsing Gauss-Lobatto 11 points: ";
    result = quad{gausslobatto(11)}.intg(func1, {.xl = 0, .xr = 2 * atan(1.0)});
    std::cout << "\nInt(sin(x),{x,0,pi/2}) = " << result << "\n";

    return 0;
}

int demo2() {
    std::cout << std::setprecision(15);

    quad3::Triangle triangle1{
        .ax = 0.0, .ay = 0.0, .bx = 1.0, .by = 0.0, .cx = 0.0, .cy = 1.0};
    quad3::Triangle triangle2{
        .ax = 0.0, .ay = 0.0, .bx = 2.0, .by = 0.0, .cx = 0.0, .cy = 3.0};

    // (1)
    std::cout << "Using 3 points Gauss Quadrature with func1 (x^2 + y^2): ";
    auto result = quad3{quad3::Builtin::P3}.intg(func1, triangle1);
    std::cout << "\nInt(x^2 + y^2, Triangle) = " << result
              << " (expected 0.166667)\n";

    // (2)
    std::cout << "\nUsing 7 points Gauss Quadrature with func2 (x * y): ";
    result = quad3{}.intg(func2, triangle1);
    std::cout << "\nInt(x * y, Triangle) = " << result
              << " (expected 0.0416667)\n";

    // (3)
    std::cout << "\nUsing 7 points with func3 (sin(x) * "
                 "cos(y)): ";
    result = quad3{quad3::Builtin::P7}.intg(func3, triangle1);
    std::cout << "\nInt(sin(x) * cos(y), Triangle) = " << result
              << " (expected 0.150584)\n";

    // (4)
    std::cout << "\nUsing custom Triangle (0, 0), (2, 0), (0, 3) with func1 "
                 "(x^2 + y^2): ";
    result = quad3{quad3::Builtin::P12}.intg(func1, triangle2);
    std::cout << "\nInt(x^2 + y^2, Custom Triangle) = " << result
              << " (expected 6.5)\n";

    // (5)
    std::cout << "\nUsing 12 points with func3 (sin(x) * cos(y)): ";
    result = quad3{quad3::Builtin::P12}.intg(func3, triangle1);
    std::cout << "\nInt(sin(x) * cos(y), Triangle) = " << result
              << " (expected 0.150584)\n";

    return 0;
}

int main() {
    demo1();
    demo2();

    return 0;
}
