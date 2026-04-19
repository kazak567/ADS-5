// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <iostream>
template <typename T, int kMaxSize>
class TStack {
 private:
  T buffer_[kMaxSize];
  int stackTop_;

 public:
  TStack() : stackTop_(-1) {}

  int getSize() const {
    return stackTop_ + 1;
  }
  bool isEmpty() const {
    return stackTop_ == -1;
  }
  void push(const T& value) {
    if (stackTop_ < kMaxSize - 1) {
      buffer_[++stackTop_] = value;
    } else {
      throw "Stack overflow";
    }
  }
  T get() const {
    if (stackTop_ >= 0) {
      return buffer_[stackTop_];
    } else {
      throw "Stack underflow";
    }
  }
  void pop() {
    if (stackTop_ >= 0) {
      --stackTop_;
    } else {
      throw "Stack underflow";
    }
  }
};
#endif  // INCLUDE_TSTACK_H_
