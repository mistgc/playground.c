#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace DS {

template <class T> class Stack {
public:
  virtual ~Stack() {}
  virtual void push(const T) = 0;
  virtual T pop() = 0;
  virtual bool is_empty() const = 0;
  virtual int size() const = 0;
  virtual T peek() const = 0;
};

template <class T> class LinkStackWithoutHead : public Stack<T> {
private:
  class Node {
  public:
    T data;
    Node *next;

  public:
    Node(T _data) : data(_data), next(nullptr) {}
  };
  Node *top;

public:
  LinkStackWithoutHead() : top(nullptr) {}
  ~LinkStackWithoutHead() {}
  void push(const T);
  T pop();
  bool is_empty() const;
  int size() const;
  T peek() const;
};

template <typename T> void LinkStackWithoutHead<T>::push(const T element) {
  if (this->top == nullptr) {
    this->top = new LinkStackWithoutHead<T>::Node(element);
  } else {
    auto *p = new LinkStackWithoutHead<T>::Node(element);
    p->next = this->top;
    this->top = p;
  }
}

template <typename T> T LinkStackWithoutHead<T>::pop() {
  if (this->top == nullptr)
    throw std::runtime_error("stack is empty");

  T res = this->top->data;
  this->top = this->top->next;

  return res;
}

template <typename T> int LinkStackWithoutHead<T>::size() const {
  int res = 0;
  auto p = this->top;
  while (p != nullptr) {
    res++;
    p = p->next;
  }

  return res;
}

template <typename T> bool LinkStackWithoutHead<T>::is_empty() const {
  if (this->top == nullptr)
    return true;
  else
    return false;
}

template <typename T> T LinkStackWithoutHead<T>::peek() const {
  if (this->top == nullptr)
    throw std::runtime_error("stack is empty");

  return this->top->data;
}

class StackCalculator {
private:
  Stack<char> *_operator;
  Stack<float> *result;
  std::unordered_map<char, float> operator_table;
  std::optional<std::string> expression;
  int expr_offset;
  int expr_size;

public:
  StackCalculator(std::string expr)
      : expression(std::optional<std::string>{expr}), expr_offset(0),
        expr_size(expr.size()) {

    StackCalculator();
  }

  StackCalculator() : expr_offset(0) {
    this->_operator = new LinkStackWithoutHead<char>();
    this->result = new LinkStackWithoutHead<float>();

    /*
     * operator   weight
     *    +          1
     *    -          1
     *    *          1
     *    /          1
     *    (        0xfff
     *    )        0xfff
     */
    this->operator_table.insert(std::pair<char, float>('-', 1));
    this->operator_table.insert(std::pair<char, float>('+', 1));
    this->operator_table.insert(std::pair<char, float>('*', 2));
    this->operator_table.insert(std::pair<char, float>('/', 2));
    this->operator_table.insert(std::pair<char, float>('(', 0xfff));
    this->operator_table.insert(std::pair<char, float>(')', 0xfff));
  }

  StackCalculator(StackCalculator &&) = delete;
  StackCalculator(const StackCalculator &) = delete;

  float calculate();
  float calculate(std::string expr);
};

} // namespace DS
