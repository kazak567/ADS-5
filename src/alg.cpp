// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int getPriority(const char ch) {
  if (ch == '(') return 0;
  else if (ch == ')') return 1;
  else if (ch == '+' || ch == '-') return 2;
  else if (ch == '*' || ch == '/') return 3;
  else throw "Incorrect character";
}
std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opStack;
  int idx = 0;
  std::string output;

  while (idx < static_cast<int>(inf.length())) {
    if (inf[idx] >= '0' && inf[idx] <= '9') {
      while (idx < static_cast<int>(inf.length()) &&
             inf[idx] >= '0' && inf[idx] <= '9') {
        output += inf[idx++];
      }
      output += ' ';
      continue;
    }
    int pr = getPriority(inf[idx]);
    if (pr == 0) {
      opStack.push(inf[idx]);
    } else if (pr == 1) {
      while (!opStack.isEmpty() && getPriority(opStack.top()) != 0) {
        output += opStack.top(); output += ' ';
        opStack.pop();
      }
      if (!opStack.isEmpty()) opStack.pop();
    } else if (pr > 1) {
      if (opStack.isEmpty() || pr > getPriority(opStack.top())) {
        opStack.push(inf[idx]);
      } else {
        while (!opStack.isEmpty() && opStack.top() != '(' &&
               pr <= getPriority(opStack.top())) {
          output += opStack.top(); output += ' ';
          opStack.pop();
        }
        opStack.push(inf[idx]);
      }
    }
    ++idx;
  }
  while (!opStack.isEmpty()) {
    output += opStack.top();
    if (opStack.getSize() != 1) output += ' ';
    opStack.pop();
  }
  return output;
}
int eval(const std::string& post) {
  TStack<int, 100> valStack;
  int idx = 0;
  while (idx < static_cast<int>(post.length())) {
    if (post[idx] >= '0' && post[idx] <= '9') {
      std::string token;
      while (idx < static_cast<int>(post.length()) && post[idx] != ' ') {
        token += post[idx++];
      }
      ++idx;
      valStack.push(std::stoi(token));
      continue;
    }
    char op = post[idx];
    int rhs = valStack.top(); valStack.pop();
    int lhs = valStack.top(); valStack.pop();
    int result = 0;
    if (op == '+') result = lhs + rhs;
    else if (op == '-') result = lhs - rhs;
    else if (op == '*') result = lhs * rhs;
    else if (op == '/') result = lhs / rhs;
    valStack.push(result);
    ++idx;
  }
  return valStack.top();
}
