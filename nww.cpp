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
        
        quotient.coefficients.insert(quotient.coefficients.begin(), leadingCoefficient);
        
        for (int i = 0; i <= divisorDegree; ++i) {
            remainder.coefficients[remainder.coefficients.size() - i - 1] -= leadingCoefficient * divisor.coefficients[divisorDegree - i];
        }
        
        while (!remainder.coefficients.empty() && remainder.coefficients.back() == 0) {
            remainder.coefficients.pop_back();
        }
    }
    
    return std::make_pair(quotient, remainder);
}

void printPolynomial(Polynomial& poly) {
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

Polynomial multiplyPolynomials(Polynomial a, Polynomial b) {
    Polynomial result;
    result.coefficients.resize(a.coefficients.size() + b.coefficients.size() - 1, 0);
    
    for (int i = 0; i < a.coefficients.size(); ++i) {
        for (int j = 0; j < b.coefficients.size(); ++j) {
            result.coefficients[i + j] += a.coefficients[i] * b.coefficients[j];
        }
    }
    
    return result;
}


Polynomial NWD(Polynomial a, Polynomial b){
    auto divisionResult = dividePolynomials(a, b);
    if (divisionResult.second.coefficients.empty()) {
        return b;
    } else {
        return NWD(b, divisionResult.second);
    }
}

Polynomial NWW(Polynomial a, Polynomial b){
    Polynomial nwd = NWD(a, b);
    Polynomial m = multiplyPolynomials(a, b);

    auto divisionResult = dividePolynomials(m, nwd);

    return divisionResult.first;
}

int main() {
    Polynomial dividend, divisor;
    
    dividend.coefficients = {1, 2, 1};
    divisor.coefficients = {1, 0, 1};
    
    Polynomial result = NWW(dividend, divisor);
    
    std::cout << "NWW: ";
    printPolynomial(result);
    
    return 0;
}
