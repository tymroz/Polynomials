#include <iostream>
#include <vector>

struct Polynomial {
    std::vector<double> coefficients;
};

std::pair<Polynomial, Polynomial> dividePolynomials(Polynomial dividend, Polynomial divisor) {
    Polynomial quotient;
    Polynomial remainder = dividend;
    
    int divisorDegree = divisor.coefficients.size() - 1;
    
    while (remainder.coefficients.size() >= divisor.coefficients.size()) {
        double leadingCoefficient = remainder.coefficients.back() / divisor.coefficients.back();
        //std::cout <<leadingCoefficient<<std::endl;

        quotient.coefficients.insert(quotient.coefficients.begin(), leadingCoefficient);
        
        for (int i = 0; i <= divisorDegree; ++i) {
            remainder.coefficients[remainder.coefficients.size() - i - 1] -= leadingCoefficient * divisor.coefficients[divisorDegree - i];
            //std::cout <<"for"<<std::endl;
        }
        
        while (!remainder.coefficients.empty() && remainder.coefficients.back() == 0) {
            remainder.coefficients.pop_back();
            //std::cout <<"while"<<std::endl;
        }
    }
    
    return std::make_pair(quotient, remainder);
}

void printPolynomial(const Polynomial& poly) {
    int degree = poly.coefficients.size() - 1;
    for (int i = degree; i >= 0; --i) {
        if (poly.coefficients[i] != 0) {
            std::cout << poly.coefficients[i] << "x^" << i;
            if (i != 0) {
                std::cout << " + ";
            }
        }
    }
    std::cout << std::endl;
}

int main() {
    Polynomial dividend, divisor;
    
    dividend.coefficients = {1, 2, 1};
    divisor.coefficients = {1, -2, -2};
    
    auto result = dividePolynomials(dividend, divisor);
    
    std::cout << "Quotient: ";
    printPolynomial(result.first);
    
    std::cout << "Remainder: ";
    printPolynomial(result.second);
    
    return 0;
}
