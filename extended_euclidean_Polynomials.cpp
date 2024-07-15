#include <iostream>
#include <vector>

struct Polynomial {
    std::vector<double> coefficients;
};

struct Extended_GCD {
    Polynomial f;
    Polynomial g;
    Polynomial A;
    Polynomial B;
    Polynomial gcd;
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
    while(quotient.coefficients.size() <= divisorDegree){
        quotient.coefficients.insert(quotient.coefficients.begin(), 0);
    }
    
    return std::make_pair(quotient, remainder);
}

void printPolynomial(Polynomial& poly) {
    int degree = poly.coefficients.size() - 1;
    bool first = true;
    for (int i = degree; i >= 0; --i) {
        if (poly.coefficients[i] != 0) {
            if (!first && poly.coefficients[i] > 0) {
                std::cout << " + ";
            }
            std::cout << poly.coefficients[i];
            if (i > 0) {
                std::cout << "x^" << i;
            }
            first = false;
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

Polynomial subtractPolynomials(Polynomial a, Polynomial b){
    Polynomial result;
        size_t resultSize = std::max(a.coefficients.size(), b.coefficients.size());
        result.coefficients.resize(resultSize, 0);

        for (size_t i = 0; i < resultSize; ++i) {
            double coefa = (i < a.coefficients.size()) ? a.coefficients[i] : 0;
            double coefb = (i < b.coefficients.size()) ? b.coefficients[i] : 0;
            result.coefficients[i] = coefa - coefb;
        }

        return result;
}

Extended_GCD extendedEuclidean(Polynomial f, Polynomial g){
    Polynomial x{.coefficients = {0}};
    Polynomial y{.coefficients = {1}};
    Polynomial u{.coefficients = {1}};
    Polynomial v{.coefficients = {0}};
    Extended_GCD result;
    result.f = f;
    result.g = g;
    while (!g.coefficients.empty()){
        std::pair<Polynomial, Polynomial> division = dividePolynomials(f, g);
        Polynomial q = division.first;
        Polynomial r = division.second;
        Polynomial m = subtractPolynomials(x, multiplyPolynomials(u, q));
        Polynomial n = subtractPolynomials(y, multiplyPolynomials(v, q));
        f = g;
        g = r;
        x = v;
        y = u;
        u = m;
        v = n;
    }
    result.gcd = f;
    result.A = x;
    result.B = y;

    return result;
}

int main() {
    Polynomial f, g, h, i;

    /*
    przyklad:
    f = 2x^2 + 2x + 2
    g = x^2 + 1x + 1
    NWD(f,g) = x^2 + 1x + 1
    A = 0
    B = 1
     */
    f.coefficients = {2, 2, 2};
    g.coefficients = {1, 1, 1};
    
    std::cout << "f: ";
    printPolynomial(f);
    std::cout << "g: ";
    printPolynomial(g);

    Extended_GCD wynik = extendedEuclidean(f, g);

    std::cout << "NWD: ";
    printPolynomial(wynik.gcd);
    std::cout << "A: ";
    printPolynomial(wynik.A);
    std::cout << "B: ";
    printPolynomial(wynik.B);
    std::cout << std::endl;
   
    /*
    przyklad:
    h = x^2 + x + 1
    i = x + 1
    NWD(f,g) = 1
    A = 1
    B = -x
    */
    h.coefficients = {1, 1, 1};
    i.coefficients = {1, 1};
    
    std::cout << "f: ";
    printPolynomial(h);
    std::cout << "g: ";
    printPolynomial(i);

    Extended_GCD wynik2 = extendedEuclidean(h, i);

    std::cout << "NWD: ";
    printPolynomial(wynik2.gcd);
    std::cout << "A: ";
    printPolynomial(wynik2.A);
    std::cout << "B: ";
    printPolynomial(wynik2.B);
    
    return 0;
}
