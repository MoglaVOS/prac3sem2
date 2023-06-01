#include <iostream>
#include <string>
#include <fstream>
#include "stack.h"
using namespace std;
ofstream result("result.txt", std::ios::app);

void output_stack(stack* s) {
    while (!empty(s)) {
        if (result.is_open()) {
            result << s->data << ' ';
        }
        cout << s->data << ' ';
        s = s->tail;
    }
}

bool correction(string& s) {
    stack* par = NULL;
    for (int i = 1; i < s.length() - 1; i++) {
        if (s[i] == ' ' && priority(s[i - 1]) == -1 && priority(s[i + 1]) == -1) return 0;
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') s.erase(i, 1);
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') par = push(par, s[i]);
        else if (s[i] == ')')
            if (!empty(par)) par = pop(par);
            else return 0;
    }
    if (!empty(par)) return 0;
    for (int i = 1; i < s.length() - 1; i++) {
        if (s[i] == '(' && (priority(s[i - 1]) == -1 || s[i - 1] == ')')) {
            s.insert(i, "*");
        }
        else if (s[i] == ')' && (priority(s[i + 1]) == -1 || s[i + 1] == '(')) {
            s.insert(i + 1, "*");
        }
    }
    for (int i = 1; i < s.length(); i++) {
        if (s[i - 1] == '+' && s[i] == '-') s.erase(i - 1, 1);
        else if (s[i - 1] == '-' && s[i] == '-') {
            s.insert(i - 1, "+");
            s.erase(i, 2);
        }
        else if (priority(s[i - 1]) > 0 && priority(s[i]) > 0 && s[i] != '-') return 0;
    }
    for (int i = 0, k = 0; i < s.length(); i++) {
        if (priority(s[i]) > 0) k++;
        if (i == 1 && s[i - 1] != '-' && priority(s[i - 1]) > 0) return 0;
        else if (i == s.length() - 1 && priority(s[i]) > 0 || i == s.length() - 1 && !k) return 0;
    }
    return 1;
}


string reverse_notation(string str) {
    cout << "Скорректированное выражение: " << str << '\n' << "Перевод в обратную польскую нотацию:\n";
    result << str << '\n' << "Перевод в обратную польскую нотацию:\n";
    string n;
    stack* stack = NULL;
    string num = "";
    int k = 1;
    for (int i = 0, flag; i < str.length(); i++) {
        if (str[i] == '-') {
            if (i == 0 && priority(str[i + 1]) == -1) {
                n += str[i];
                continue;
            }
            else if (priority(str[i - 1]) > 1 && priority(str[i + 1]) == -1) {
                n += str[i];
                continue;
            }
        }
        flag = priority(str[i]);
        if (flag == 0) {
            if (str[i] == '(') {
                if (num != "") {
                    n += num;
                    n += ' ';
                    num = "";
                    cout << k << ". Стэк: ";
                    result << k << ". Стэк: ";
                    output_stack(stack);
                    cout << "\t\tвыходная строка: " << n << "\n";
                    result << "\t\tвыходная строка: " << n << "\n";
                    k++;
                }
                stack = push(stack, str[i]);
                cout << k << ". Стэк: ";
                result << k << ". Стэк: ";
                output_stack(stack);
                cout << "\t\tвыходная строка: " << n << "\n";
                result << "\t\tвыходная строка: " << n << "\n";
                k++;
            }
            else {
                if (num != "") {
                    n += num;
                    n += ' ';
                    num = "";
                    cout << k << ". Стэк: ";
                    result << k << ". Стэк: ";
                    output_stack(stack);
                    cout << "\t\tвыходная строка: " << n << "\n";
                    result << "\t\tвыходная строка: " << n << "\n";
                    k++;
                }
                while (!empty(stack)) {
                    if (top(stack) != '(') {
                        n += top(stack);
                        stack = pop(stack);
                        n += ' ';
                    }
                    else {
                        stack = pop(stack);
                        break;
                    }
                }
                cout << k << ". Стэк: ";
                result << k << ". Стэк: ";
                output_stack(stack);
                cout << "\t\tвыходная строка: " << n << "\n";
                result << "\t\tвыходная строка: " << n << "\n";
                k++;
            }
        }
        else if (flag == 1) {
            if (num != "") {
                n += num;
                n += ' ';
                num = "";
                cout << k << ". Стэк: ";
                result << k << ". Стэк: ";
                output_stack(stack);
                cout << "\t\tвыходная строка: " << n << "\n";
                result << "\t\tвыходная строка: " << n << "\n";
                k++;
            }
            if (empty(stack) || priority(top(stack)) < flag) {
                stack = push(stack, str[i]);
            }
            else {
                while (!empty(stack) && priority(top(stack)) >= flag) {
                    n += top(stack);
                    stack = pop(stack);
                    n += ' ';
                }
                stack = push(stack, str[i]);
            }
            cout << k << ". Стэк: ";
            result << k << ". Стэк: ";
            output_stack(stack);
            cout << "\t\tвыходная строка: " << n << "\n";
            result << "\t\tвыходная строка: " << n << "\n";
            k++;
        }
        else if (flag == 2) {
            if (num != "") {
                n += num;
                n += ' ';
                num = "";
                cout << k << ". Стэк: ";
                result << k << ". Стэк: ";
                output_stack(stack);
                cout << "\t\tвыходная строка: " << n << "\n";
                result << "\t\tвыходная строка: " << n << "\n";
                k++;
            }
            if (empty(stack) || priority(top(stack)) < flag) {
                stack = push(stack, str[i]);
            }
            else {
                while (!empty(stack) && priority(top(stack)) >= flag) {
                    n += top(stack);
                    stack = pop(stack);
                    n += ' ';
                }
                stack = push(stack, str[i]);
            }
            cout << k << ". Стэк: ";
            result << k << ". Стэк: ";
            output_stack(stack);
            cout << "\t\tвыходная строка: " << n << "\n";
            result << "\t\tвыходная строка: " << n << "\n";
            k++;
        }
        else num += str[i];
    }
    if (num != "") {
        n += num;
        n += ' ';
        cout << k << ". Стэк: ";
        result << k << ". Стэк: ";
        output_stack(stack);
        cout << "\t\tвыходная строка: " << n << "\n";
        result << "\t\tвыходная строка: " << n << "\n";
        k++;
    }
    while (!empty(stack)) {
        n += top(stack);
        stack = pop(stack);
        n += ' ';
    }
    cout << k << ". Стэк: ";
    result << k << ". Стэк: ";
    output_stack(stack);
    cout << "\t\tвыходная строка: " << n << "\n";
    result << "\t\tвыходная строка: " << n << "\n";
    return n;
}

double calculate(string s) {
    //system(LC_ALL, "RUS");
    string num = "";
    double num_1, num_2;
    stack_i* stack = NULL;
    for (int i = 0, k = 1; i < s.length(); i++) {
        if (priority(s[i]) == -1 && s[i] != ' ') {
            while (s[i] != ' ') {
                num += s[i];
                i++;
            }
            stack = push(stack, stoi(num));
            cout << k << ". Записываем в стэк " << num << '\n';
            result << k << ". Записываем в стэк " << num << '\n';
            k++;
            num = "";
        }
        else if (priority(s[i]) == 1) {
            if (s[i] == '+') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 + num_1);
                cout << k << ". Выносим из стэка " << num_2 << " и " << num_1 << ", складываем и возвращаем в стэк " << num_1 + num_2 << '\n';
                result << k << ". Выносим из стэка " << num_2 << " и " << num_1 << ", складываем и возвращаем в стэк " << num_1 + num_2 << '\n';
                k++;
            }
            if (s[i] == '-' && i < s.length() - 1 && s[i + 1] == ' ') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 - num_1);
                cout << k << ". Выносим из стэка " << num_2 << " и " << num_1 << ", вычитаем и возвращаем в стэк " << num_2 - num_1 << '\n';
                result << k << ". Выносим из стэка " << num_2 << " и " << num_1 << ", вычитаем и возвращаем в стэк " << num_2 - num_1 << '\n';
                k++;
            }
            else if (s[i] == '-' && i < s.length() - 1 && priority(s[i + 1]) == -1) {
                while (s[i] != ' ') {
                    num += s[i];
                    i++;
                }
                stack = push(stack, stoi(num));
                cout << k << ". Записываем в стэк " << num << '\n';
                result << k << ". Записываем в стэк " << num << '\n';
                k++;
                num = "";
            }
        }
        else if (priority(s[i]) == 2) {
            if (s[i] == '*') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 * num_1);
                cout << k << ". Выносим из стэка " << num_2 << " и " << num_1 << ", умножаем и возвращаем в стэк " << num_1 * num_2 << '\n';
                result << k << ". Выносим из стэка " << num_2 << " и " << num_1 << ", умножаем и возвращаем в стэк " << num_1 * num_2 << '\n';
                k++;
            }
            if (s[i] == '/') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 / num_1);
                cout << k << ". Выносим из стэка " << num_2 << " и " << num_1 << ", делим и возвращаем в стэк " << num_2 / num_1 << '\n';
                result << k << ". Выносим из стэка " << num_2 << " и " << num_1 << ", делим и возвращаем в стэк " << num_2 / num_1 << '\n';
                k++;
            }
        }
    }
    cout << "Возвращаем верхний элемент стэка\n";
    result << "Возвращаем верхний элемент стэка\n";
    result << "Ответ: " << top(stack) << "\n";
    return top(stack);
}


int main() {
    int key = 0;
    ofstream ex("examples.txt", std::ios::app);
    key = turnon(key);
    string str, str_out;
    while (true) {
        switch (key) {
            case -1:
                cout << "Invalid input\n";
                cin.clear();
                cin.ignore();
                break;
            case 1:cin.ignore();
                cout << "Введите выражение: ";
                getline(cin, str);
                while (str == "" || !correction(str)) {
                    cout << "Invalid input\n\nВведите выражение: ";
                    getline(cin, str);
                }
                if (ex.is_open()) {
                    ex << str << '\n';
                }
                str_out = reverse_notation(str);
                cout << "Обратная польская нотация: " << str_out << '\n';
                result << "Обратная польская нотация: " << str_out << '\n';
                cout << "Вычисления: \n";
                result << "Вычисления: \n";
                cout << "Ответ: " << calculate(str_out) << "\n\n";
                break;
            case 2:
                return 0;
            default:
                key = 0;
                break;
        }
        key = turnon(key);
    }
    ex.close();
    result.close();
    return 0;
}