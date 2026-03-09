//
// Created by Oereor on 2026-03-09.
//

/**
 * 这个算法使用了双向链表, 计算加法时的时间复杂度为 O(n), 构造多项式的时间复杂度也为 O(n).
 * 储存多项式的空间复杂度为 O(n), 并只需使用常数的额外空间. 总的空间复杂度是 O(n).
 */

#include <iostream>

/**
 * Assume the polynomial is stored by exponents ascending.
 */
class Polynomial {
public:
    Polynomial();
    ~Polynomial();
    Polynomial operator+(const Polynomial& rhs) const;
    Polynomial operator-(const Polynomial& rhs) const;
    bool operator==(const Polynomial& rhs) const;
    bool operator!=(const Polynomial& rhs) const;
    void appendTerm(double coefficient, int exponent) const;
    static Polynomial fromTerms(int termCount, double coefficients[], int exponents[]);
private:
    struct TermNode {
        double coefficient;
        int exponent;
        TermNode* next;
        TermNode* prev;
        TermNode(const double coefficient, const int exponent, TermNode* prev = nullptr, TermNode* next = nullptr) {
            this->coefficient = coefficient;
            this->exponent = exponent;
            this->prev = prev;
            this->next = next;
        }
    };
    TermNode* head;
    TermNode* tail;
};

Polynomial::Polynomial() {
    head = new TermNode(0, -1);
    tail = new TermNode(0, -1);
    head->next = tail;
    tail->prev = head;
}

Polynomial::~Polynomial() {
    const TermNode* curr = head;
    while (curr != tail) {
        const TermNode* next = curr->next;
        delete curr;
        curr = next;
    }
    delete tail;
}

void Polynomial::appendTerm(const double coefficient, const int exponent) const {
    auto* newTerm = new TermNode(coefficient, exponent, tail->prev, tail);
    tail->prev->next = newTerm;
    tail->prev = newTerm;
}

Polynomial Polynomial::operator+(const Polynomial &rhs) const {
    Polynomial result;
    const TermNode* term1 = this->head->next;
    const TermNode* term2 = rhs.head->next;
    while (term1 != this->tail && term2 != rhs.tail) {
        if (term1->exponent < term2->exponent) {
            result.appendTerm(term1->coefficient, term1->exponent);
            term1 = term1->next;
        }
        else if (term1->exponent > term2->exponent) {
            result.appendTerm(term2->coefficient, term2->exponent);
            term2 = term2->next;
        }
        else {
            result.appendTerm(term1->coefficient + term2->coefficient, term1->exponent);
            term1 = term1->next;
            term2 = term2->next;
        }
    }
    while (term1 != this->tail) {
        result.appendTerm(term1->coefficient, term1->exponent);
        term1 = term1->next;
    }
    while (term2 != rhs.tail) {
        result.appendTerm(term2->coefficient, term2->exponent);
        term2 = term2->next;
    }
    return result;
}

Polynomial Polynomial::operator-(const Polynomial &rhs) const {
    Polynomial result;
    const TermNode* term1 = this->head->next;
    const TermNode* term2 = rhs.head->next;
    while (term1 != this->tail && term2 != rhs.tail) {
        if (term1->exponent < term2->exponent) {
            result.appendTerm(term1->coefficient, term1->exponent);
            term1 = term1->next;
        }
        else if (term1->exponent > term2->exponent) {
            result.appendTerm(-term2->coefficient, term2->exponent);
            term2 = term2->next;
        }
        else {
            result.appendTerm(term1->coefficient - term2->coefficient, term1->exponent);
            term1 = term1->next;
            term2 = term2->next;
        }
    }
    while (term1 != this->tail) {
        result.appendTerm(term1->coefficient, term1->exponent);
        term1 = term1->next;
    }
    while (term2 != rhs.tail) {
        result.appendTerm(-term2->coefficient, term2->exponent);
        term2 = term2->next;
    }
    return result;
}

bool Polynomial::operator==(const Polynomial &rhs) const {
    const TermNode* term1 = this->head->next;
    const TermNode* term2 = rhs.head->next;
    while (term1 != this->tail && term2 != rhs.tail) {
        if (term1->coefficient != term2->coefficient || term1->exponent != term2->exponent) {
            return false;
        }
        term1 = term1->next;
        term2 = term2->next;
    }
    if (term1 != this->tail || term2 != rhs.tail) {
        return false;
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial &rhs) const {
    return !(*this == rhs);
}

Polynomial Polynomial::fromTerms(int termCount, double coefficients[], int exponents[]) {
    Polynomial result;
    for (int i = 0; i < termCount; i++) {
        result.appendTerm(coefficients[i], exponents[i]);
    }
    return result;
}

int main() {
    double coeff1[6] = {1, 2, 3, 4, 5, 6}, coeff2[6] = {6, 5, 4, 3, 2, 1},
        expected_coeff[10] = {1, 6, 2, 5, 3, 4, 4, 3, 7, 7};
    int exp1[6] = {0, 2, 4, 6, 8, 9}, exp2[6] = {1, 3, 5, 7, 8, 9},
    expected_exp[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Polynomial p1 = Polynomial::fromTerms(6, coeff1, exp1),
        p2 = Polynomial::fromTerms(6, coeff2, exp2),
        expected = Polynomial::fromTerms(10, expected_coeff, expected_exp);
    Polynomial p3 = p1 + p2;
    std::cout << (expected == p3) << std::endl;
    return 0;
}