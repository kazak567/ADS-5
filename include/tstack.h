#include <string>
#include <map>
#include "tstack.h"
int checkPr(const char ch) {
    if (ch == '(') return 0;
    else if (ch == ')') return 1;
    else if (ch == '+' || ch == '-') return 2;
    else if (ch == '*' || ch == '/') return 3;
    else throw "Incorrect character";
}
std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack1;
    int i = 0;
    std::string res;
    while (i < inf.length()) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            while (inf[i] >= '0' && inf[i] <= '9') {
                res += inf[i];
                i++;
            }
            res += ' ';
            continue;
        }
        if (checkPr(inf[i]) == 0) {
            stack1.push(inf[i]);
        }
        else if (checkPr(inf[i]) == 1) {
            while (!stack1.isEmpty() && checkPr(stack1.get()) != 0) {
                res += stack1.get();
                res += ' ';
                stack1.pop();
            }
            stack1.pop();
        }
        else if (checkPr(inf[i]) > 1) {
            if (stack1.isEmpty() || checkPr(inf[i]) > checkPr(stack1.get())) {
                stack1.push(inf[i]);
            }
            else {
                while (!stack1.isEmpty() && stack1.get() != '(' &&
                       checkPr(inf[i]) <= checkPr(stack1.get())) {
                    res += stack1.get();
                    res += ' ';
                    stack1.pop();
                }
                stack1.push(inf[i]);
            }
        }
        i++;
    }
    while (!stack1.isEmpty()) {
        res += stack1.get();
        if (stack1.getSize() != 1) res += ' ';
        stack1.pop();
    }
    return res;
}
int eval(const std::string& pref) {
    TStack<int, 100> stack2;
    int res = 0, i = 0;
    while (i < pref.length()) {
        if (pref[i] >= '0' && pref[i] <= '9') {
            std::string num;
            while (pref[i] != ' ') {
                num += pref[i];
                i++;
            }
            i++;
            stack2.push(std::stoi(num));
            continue;
        }
        if (pref[i] == '+') {
            res = stack2.get(); stack2.pop();
            res += stack2.get(); stack2.pop();
            stack2.push(res);
        }
        else if (pref[i] == '-') {
            res = stack2.get(); stack2.pop();
            res = stack2.get() - res; stack2.pop();
            stack2.push(res);
        }
        else if (pref[i] == '*') {
            res = stack2.get(); stack2.pop();
            res *= stack2.get(); stack2.pop();
            stack2.push(res);
        }
        else if (pref[i] == '/') {
            res = stack2.get(); stack2.pop();
            res = stack2.get() / res; stack2.pop();
            stack2.push(res);
        }
        res = 0;
        i += 2;
    }
    return stack2.get();
}
