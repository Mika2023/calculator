#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;


class Stack
{
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
    case 's':
    case 'c'://как котангенс считать?..
    case 't':
    case 'l':
        return 4;
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '-':
    case '+':
        return 1;
    }
    return 0;
}

void polish_cow(char* expression)//эта функция принимает строку с выражением (не надо) и преобразует в польскую нотацию (строку)
{//надо заменить входную строку на чтение с потока ввода
//может, польская нотация не нужна в виде строки именно...
    char polish[1000] = { 0 };
    int len = strlen(expression);
    int a = 0, f = 1;//флаг для унарного минуса (когда надо считать отрицательное число): 1 - минус унарный, 0 - обычный
    Stack signs;
    for (int i = 0; i < len; ++i) {
        if (expression[i] >= '0' && expression[i] <= '9' || expression[i]=='-' && f || expression[i] == 'e' || expression[i] == 'E' || expression[i]=='p' || expression[i]=='P')
        {
          double number = 0;
          if (expression[i] == 'e' || expression[i] == 'E') number = exp(1);
          else if (expression[i] == 'p' || expression[i] == 'P') number = M_PI;
          //это число либо е, либо пи, либо вводимое пользователем
          polish[a++] = expression[i];
          f = 0;
        }
        else {
            if (a > 0 && polish[a - 1] != ' ') polish[a++] = ' ';
            if (expression[i] == '(')
            {
              signs.push('(');
              f = 1;
            }
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
        case '^':
            res = pow(nums.pop(), nums.pop());
            break;
          case 's':
              res = sin(nums.pop());
              break;
          case 'c':
              res = cos(nums.pop());
              break;
          case 't':
              res = tan(nums.pop());
              break;
          case 'l':
              res = log(nums.pop());
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
    cout << nums.get_top();
}

int main()
{
    
    return 0;
}

