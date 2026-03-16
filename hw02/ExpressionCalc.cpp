#include <cmath>
#include <iostream>
#include <vector>

/************** Definitions of a stack ***************/
template <class Type>
class Stack {
public:
    Stack();
    explicit Stack(int capacity);
    [[nodiscard]] int size() const;
    [[nodiscard]] bool isEmpty() const;
    void push(const Type& item);
    Type pop();
    [[nodiscard]] Type peek() const;
    void clear();
    ~Stack();

private:
    static constexpr int DEFAULT_CAPACITY = 4;
    static constexpr double SHRINK_THRESHOLD = 0.25;
    int m_Size;
    int m_Capacity;
    Type* m_Items;

    void resize(int targetCapacity);
    void checkCapacity();
};

template<class Type>
Stack<Type>::Stack() {
    m_Capacity = DEFAULT_CAPACITY;
    m_Items = new Type[m_Capacity];
    m_Size = 0;
}

template<class Type>
Stack<Type>::Stack(const int capacity) {
    m_Items = new Type[capacity];
    m_Capacity = capacity;
    m_Size = 0;
}

template<class Type>
void Stack<Type>::push(const Type &item) {
    checkCapacity();
    m_Items[m_Size] = item;
    m_Size++;
}

template<class Type>
void Stack<Type>::resize(const int targetCapacity) {
    const Type* originalItems = m_Items;
    Type* newItems = new Type[targetCapacity];
    for (int i = 0; i < m_Size; i++) {
        newItems[i] = m_Items[i];
    }
    m_Items = newItems;
    m_Capacity = targetCapacity;
    delete[] originalItems;
}

template<class Type>
Type Stack<Type>::peek() const {
    if (m_Size == 0) {
        throw;
    }
    return m_Items[m_Size - 1];
}

template<class Type>
Type Stack<Type>::pop() {
    if (m_Size == 0) {
        throw;
    }
    Type result = m_Items[m_Size - 1];
    m_Size--;
    checkCapacity();
    return result;
}

template<class Type>
void Stack<Type>::checkCapacity() {
    if (m_Size + 1 >= m_Capacity) {
        resize(2 * m_Capacity);
    }
    else if (m_Capacity >= 2 * DEFAULT_CAPACITY && m_Size / static_cast<double>(m_Capacity) < SHRINK_THRESHOLD) {
        resize(m_Capacity / 2 + 1);
    }
}

template<class Type>
int Stack<Type>::size() const {
    return m_Size;
}

template<class Type>
bool Stack<Type>::isEmpty() const {
    return m_Size == 0;
}

template<class Type>
void Stack<Type>::clear() {
    m_Size = 0;
    const Type* originalItems = m_Items;
    m_Items = new Type[m_Capacity];
    delete[] originalItems;
}

template<class Type>
Stack<Type>::~Stack() {
    delete[] m_Items;
}
/********************** End of stack definition *********************/

class Calculator {
public:
    explicit Calculator(const std::string& expression) {
        scanExpression(expression);
        calcResult = calculate();
    }

    [[nodiscard]] double result() const {
        return calcResult;
    }

private:
    enum TokenType { NUMBER, OPERATOR };

    enum Operator { ADD, SUB, MUL, DIV, POW, OPEN, CLOSE };

    struct Token {
        TokenType type;
        int value;
        Token(const TokenType type, const int value) {
            this->type = type;
            this->value = value;
        }
    };

    std::vector<Token> tokens;
    double calcResult;

    void scanExpression(const std::string& expression) {
        Stack<Operator> operators;
        int i = 0;
        while (i < expression.length()) {
            if (const char curr = expression[i]; curr == ' ') { // skip all whitespaces
                i++;
                continue;
            }
            if (Token nextToken = scanNextToken(i, expression); nextToken.type == NUMBER) { // numbers need no additional process
                tokens.push_back(nextToken);
            }
            else if (nextToken.type == OPERATOR) {
                if (auto op = static_cast<Operator>(nextToken.value); op == OPEN) { // open parentheses are pushed into the stack
                    operators.push(op);
                }
                else if (op == CLOSE) { // pop operators until '(' is popped
                    while (!operators.isEmpty()) {
                        const Operator o = operators.pop();
                        if (o == OPEN) {
                            break;
                        }
                        Token opToken(OPERATOR, o);
                        tokens.push_back(opToken);
                    }
                }
                else {
                    while (!operators.isEmpty() && priority(operators.peek()) >= priority(op)) { // pop operators with higher priority
                        Token highPriorityToken(OPERATOR, operators.pop());
                        tokens.push_back(highPriorityToken);
                    }
                    operators.push(op);
                }
            }
        }
        while (!operators.isEmpty()) { // add remaining operators into token queue
            Token opToken(OPERATOR, operators.pop());
            tokens.push_back(opToken);
        }
    }

    [[nodiscard]] double calculate() const {
        Stack<double> operands;
        for (const Token token : tokens) {
            if (token.type == NUMBER) {
                operands.push(token.value);
            }
            else if (token.type == OPERATOR) {
                if (operands.size() <= 1) {
                    throw;
                }
                const double num2 = operands.pop();
                const double num1 = operands.pop(); // note that the operands are in reversed order
                operands.push(func(static_cast<Operator>(token.value), num1, num2));
            }
        }
        const double result = operands.pop();
        if (!operands.isEmpty()) {
            throw;
        }
        return result;
    }

    static Token scanNextToken(int& index, const std::string& expression) {
        char ch = expression[index];

        if (isDigit(ch)) {
            int num = 0;
            while (index < expression.length()) {
                ch = expression[index];
                if (!isDigit(ch)) {
                    break;
                }
                num = num * 10 + (ch - '0');
                index++;
            }
            const Token result(NUMBER, num);
            return result;
        }

        if (isOperator(ch)) {
            const Token result(OPERATOR, mapToOp(ch));
            index++;
            return result;
        }

        const Token defaultResult(NUMBER, 0);
        return defaultResult;
    }

    static bool isOperator(const char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')';
    }

    static bool isDigit(const char ch) {
        return '0' <= ch && ch <= '9';
    }

    static Operator mapToOp(const char op) {
        switch (op) {
            case '+': return ADD;
            case '-': return SUB;
            case '*': return MUL;
            case '/': return DIV;
            case '^': return POW;
            case '(': return OPEN;
            case ')': return CLOSE;
            default: throw;
        }
    }

    static int priority(const Operator op) {
        switch (op) {
            case ADD:
            case SUB: return 1;
            case MUL:
            case DIV: return 2;
            case POW: return 3;
            default: return 0;
        }
    }

    static double func(const Operator op, const double num1, const double num2) {
        switch (op) {
            case ADD: return num1 + num2;
            case SUB: return num1 - num2;
            case MUL: return num1 * num2;
            case DIV: return num1 / num2;
            case POW: return pow(num1, num2);
            default: return 0;
        }
    }
};

/*********************************** 说明 ***************************************
 * 支持以下运算符: '+', '-', '*', '/', '^'
 * 请统一使用 '(' ')', 不支持其他括号类型
 * 请勿在数字中间添加空格, 否则在扫描时将被截断
 * 可以在数字, 运算符以及括号之间添加任意数量的连续空格, 不影响扫描
 * 仅支持输入32位无符号整数计算, 但计算结果是双精度浮点数
 *******************************************************************************/

int main() {
    const Calculator calc("5    * (7 -2* 3) + 8/    2");
    std::cout << calc.result();
}