#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <ostream>
#include <vector>

namespace DS {

class String {
private:
  char *m_Buffer;
  size_t m_Size;

public:
  static const int npos = -1;

public:
  String(const char *string) {
    m_Size = strlen(string);
    m_Buffer = new char[m_Size + 1];
    memcpy(m_Buffer, string, m_Size);
    m_Buffer[m_Size] = 0; // add terminator '\0'
  }

  String(const String &other) : m_Size(other.m_Size) {
    m_Buffer = new char[m_Size + 1];
    memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
  }

  String(String &&other) {
    m_Buffer = other.m_Buffer;
    m_Size = other.m_Size;

    other.m_Buffer = nullptr;
    other.m_Size = 0;
  }

  ~String() { delete[] m_Buffer; }

  template <class SizeType> char &operator[](SizeType index) {
    return m_Buffer[index];
  }

  template <class SizeType> const char &operator[](SizeType index) const {
    return m_Buffer[index];
  }

  friend std::ostream &operator<<(std::ostream &stream, const String string) {
    stream << string.m_Buffer;
    return stream;
  }

  template <class T> int find(const T &);

  size_t size() const { return m_Size; }

  const char *cstr() { return m_Buffer; }

  template <class T> static std::vector<int> generate_next(const T &pattern) {
    int size = pattern.size();
    std::vector<int> next(size, -1);
    int i = 0, j = -1;
    next[0] = -1;

    while (i < size) {
      if (j == -1 || pattern[i] == pattern[j])
        next[++i] = ++j;
      else
        j = next[j];
    }

    return next;
  }
};

template <class T> int String::find(const T &ss) {
  auto next = generate_next(ss);
  int size = ss.size();
  int i = 0, j = 0;

  while (i < (int)m_Size && j < size) {
    if (j == -1 || m_Buffer[i] == ss[j]) {
      i++;
      j++;
    } else {
      j = next[j];
    }
  }

  if (j >= size)
    return i - size;
  else
    return String::npos; // const size_t npos = -1;
}

} // namespace DS
