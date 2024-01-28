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
    char polish[1000] = { 0 };
    int len = strlen(expression);
    int a = 0;
    Stack signs;

    char current_symbol;
current_symbol = cin.peek();
double number = 0;
//cout << current_symbol;    print current symbol
// для стеков создадим свой заголовочный файл?

while (1)// will it stops then the file ends?
{
	if (current_symbol >= '0' && current_symbol <= '9') // read a number
	{
		cin >> number; //		TO DO: reading from the file
		string stNumber = to_string(number); // convert to string; need to work with polish notation
		int number_length = stNumber.length(); 
		int number_iterator = 0;
		while (number_length)
		{
			polish[a++] = stNumber[number_iterator++];
		}
		polish[a++] = ' '; // separate from the next number
		continue;
	}

	if (current_symbol == '(')
	{
		signs.push('(');
		cin.ignore();
	}
	else if (current_symbol == ')')
	{
		while (signs.get_top() != -1000000000 && signs.get_top() != '(')
		{
			polish[a++] = signs.pop();
			polish[a++] = ' ';
		}
		if (signs.get_top() == '(')
		{
			signs.pop();
		}
		cin.ignore();
	}
	else
	{
		int prior = priority(current_symbol); //		TO DO:  в строке: sin; мы считали s, определили приоритет, 
		//запушили и должны пропустить следующие несколько символов, чтобы не пушить просто буквы
		while (!signs.is_empty() && priority(signs.get_top()) >= prior && signs.get_top() != '(')
		{
			polish[a++] = signs.pop();
			polish[a++] = ' ';
		}
		signs.push(current_symbol); // или priority вернет 0, и если (!priority) то символ не пушим

		//супер пупер костыль: для того чтобы различить котангенс, мы можем прочитать строку из файла,
		// заменить все подстроки "cot" на подстроку "C" и перезаписать файл. 
		// или вообще все тригонометрические функции заменить на символы, тогда будет легче с ними работать (пушить в стек с операциями)
		cin.ignore();
	}
}


double res = 0;
Stack nums;
int i = 0;
while (i < a)
{
	if (polish[i] == ' ')
	{
		++i;
		continue;
	}
	if (polish[i] >= '0' && polish[i] <= '9') // positive number
	{
		string numberPolish = "";
		while (polish[i] >= '0' && polish[i] <= '9' || polish[i] == '.')
		{
			numberPolish += polish[i++];
		}
		double num = 0;
		num = stod(numberPolish); // convert from string to double
		nums.push(num);
		continue;
	}
	else if (i + 1 < a && polish[i] == '-' && polish[i + 1] >= '0' && polish[i] <= '9') // negative number
	{
		i++; // skip the current "-". case "-" will be ignored
		string numberPolish = "";
		while (polish[i] >= '0' && polish[i] <= '9' || polish[i] == '.')
		{
			numberPolish += polish[i++];
		}
		double num = 0;
		num = stod(numberPolish);
		num = -1 * num; // make the number negative
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
		double n1 = nums.pop(), n2 = nums.pop(); // n2 - основание, n1 - число 
		res = log(n1) / log(n2); // логарифм по основанию b от числа a == натуральный логарифм (a) / натуральный логарифм (b). 
		//Для вычисления логарифма нужно обработать два числа, log(x) вычисляет натуральный логарифм
		break;
	case '*':
		res = nums.pop() * nums.pop();
		break;
	case '/':
		double n1 = nums.pop(), n2 = nums.pop();
		res = n2 / n1;
		break;

	}
	nums.push(res);
	++i;
}
}

int main()
{
    
    return 0;
}

