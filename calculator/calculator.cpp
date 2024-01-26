#include <iostream>
#include <cmath>
using namespace std;
class Stack {
    double arr[1000];
    int head, maxsize;
public:
    Stack() : head(0), arr(), maxsize(1000) {};
    void push(double val)
    {
        if (head != maxsize) arr[head++] = val;
    }
    double get_top()
    {
        return (head) ? arr[head - 1] : -1000000000;
    }
    double pop()
    {
        double val = get_top();
        if (val != -1000000000) arr[head--] = 0;
        return val;
    }
    int is_empty()
    {
        return (head) ? 0 : 1;
    }
};

int priority(char sign)
{
    switch (sign)
    {
    case '*':
    case '/':
        return 2;
    case '-':
    case '+':
        return 1;
    }
    return 0;
}
void polish_cow(char* expression)
{
    cout << "Expression:" << endl;
    cout << expression << endl;
    char polish[1000] = { 0 };
    int len = strlen(expression);
    int a = 0;
    Stack signs;
    for (int i = 0; i < len; ++i) {
        if (expression[i] >= '0' && expression[i] <= '9') polish[a++] = expression[i];
        else {
            if (a > 0 && polish[a - 1] != ' ') polish[a++] = ' ';
            if (expression[i] == '(') signs.push('(');
            else if (expression[i] == ')')
            {
                while (signs.get_top() != -1000000000 && signs.get_top() != '(')
                {
                    polish[a++] = signs.pop();
                    polish[a++] = ' ';
                }
                if (signs.get_top() == '(') signs.pop();
            }
            else
            {
                int prior = priority(expression[i]);
                while (!signs.is_empty() && priority(signs.get_top()) >= prior && signs.get_top() != '(')
                {
                    polish[a++] = signs.pop();
                    polish[a++] = ' ';
                }
                signs.push(expression[i]);
            }
        }
    }
    if (a > 0 && polish[a - 1] != ' ') polish[a++] = ' ';
    while (signs.get_top() != -1000000000)
    {
        polish[a++] = signs.pop();
        polish[a++] = ' ';
    }

    cout << "Reverse Polish Notation:" << endl;
    cout << polish << endl;
    int res = 0;
    Stack nums;
    int i = 0;
    while (i < a)
    {
        if (polish[i] == ' ')
        {
            ++i;
            continue;
        }
        if (polish[i] >= '0' && polish[i] <= '9')
        {
            int num = 0;
            while (polish[i] >= '0' && polish[i] <= '9') num = num * 10 + polish[i++] - '0';
            nums.push(num);
            continue;
        }
        switch (polish[i])
        {
        case '+':
            res = nums.pop() + nums.pop();
            break;
        case '-':
            res = -(nums.pop() - nums.pop());
            break;
        case '*':
            res = nums.pop() * nums.pop();
            break;
        case '/':
            int n1 = nums.pop(), n2 = nums.pop();
            res = n2 / n1;
            break;
        }
        nums.push(res);
        ++i;
    }
    cout << "Result:" << endl;
    cout << nums.get_top();
}
int main()
{
    
    return 0;
}

