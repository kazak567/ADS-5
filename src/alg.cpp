// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int getPriority(const char ch) {
  if (ch == '(') {
    return 0;
  } else if (ch == ')') {
    return 1;
  } else if (ch == '+' || ch == '-') {
    return 2;
  } else if (ch == '*' || ch == '/') {
    return 3;
  } else {
    return -1;
  }
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opStack;
  int pos = 0;
  std::string result;

  while (pos < static_cast<int>(inf.size())) {
    if (inf[pos] == ' ') {
      ++pos;
      continue;
    }

    if (inf[pos] >= '0' && inf[pos] <= '9') {
      while (pos < static_cast<int>(inf.size()) &&
             inf[pos] >= '0' && inf[pos] <= '9') {
        result.push_back(inf[pos++]);
      }
      result.push_back(' ');
      continue;
    }

    int priority = getPriority(inf[pos]);
    if (priority == 0) {
      opStack.push(inf[pos]);
    } else if (priority == 1) {
      while (!opStack.isEmpty() && getPriority(opStack.get()) != 0) {
        result.push_back(opStack.get());
        result.push_back(' ');
        opStack.pop();
      }
      if (!opStack.isEmpty()) {
        opStack.pop();
      }
    } else if (priority > 1) {
      if (opStack.isEmpty() || priority > getPriority(opStack.get())) {
        opStack.push(inf[pos]);
      } else {
        while (!opStack.isEmpty() && opStack.get() != '(' &&
               priority <= getPriority(opStack.get())) {
          result.push_back(opStack.get());
          result.push_back(' ');
          opStack.pop();
        }
        opStack.push(inf[pos]);
      }
    }
    ++pos;
  }

  while (!opStack.isEmpty()) {
    result.push_back(opStack.get());
    if (opStack.getSize() != 1) {
      result.push_back(' ');
    }
    opStack.pop();
  }

  return result;
}

int eval(const std::string& post) {
  TStack<int, 100> valStack;
  int pos = 0;

  while (pos < static_cast<int>(post.size())) {
    if (post[pos] == ' ') {
      ++pos;
      continue;
    }

    if (post[pos] >= '0' && post[pos] <= '9') {
      std::string token;
      while (pos < static_cast<int>(post.size()) &&
             post[pos] >= '0' && post[pos] <= '9') {
        token.push_back(post[pos++]);
      }
      valStack.push(std::stoi(token));
      continue;
    }

    char oper = post[pos++];
    int right = valStack.get();
    valStack.pop();
    int left = valStack.get();
    valStack.pop();
    int computed = 0;

    if (oper == '+') {
      computed = left + right;
    } else if (oper == '-') {
      computed = left - right;
    } else if (oper == '*') {
      computed = left * right;
    } else if (oper == '/') {
      computed = left / right;
    }

    valStack.push(computed);
  }

  return valStack.get();
}
