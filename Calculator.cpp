#include <iostream>
using namespace std;

int main() {

    double num1, num2;
    char operation;

    cout << "Leon's Simple Calculator" << endl;

    cout << "Give me a number: ";
    cin >> num1;
    cout << "Enter an operator (+, -, *, /): ";
    cin >> operation;
    cout << "Give me another number: ";
    cin >> num2;

    double result;

    switch(operation) {
        case '+':
            cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
            break;
        case '-':
            cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
            break;
        case '*':
            cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
            break;
        case '/':
            cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
            break;
        default:
            // operator is doesn't match any case constant (+, -, *, /)
            cout << "Error! wrong operator";
            break;
    }
    //cout << "Result: ";// <<// result << endl;
    
    
    return 0;
}
 
