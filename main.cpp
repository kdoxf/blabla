#include <cstddef>
#include <iostream>
#include <new>

namespace abdullaeva
{
  const int ERR_INPUT = 1;
  const int ERR_MEMORY = 2;

  void release(int ** a, std::size_t filled)
  {
    for (std::size_t i = 0; i < filled; ++i)
    {
      delete[] a[i];
    }
    delete[] a;
  }

  int ** allocRows(std::size_t rows, std::size_t cols)
  {
    int ** a = new (std::nothrow) int *[rows];
    if (!a)
    {
      return nullptr;
    }
    for (std::size_t i = 0; i < rows; ++i)
    {
      a[i] = new (std::nothrow) int[cols];
      if (!a[i])
      {
        release(a, i);
        return nullptr;
      }
    }
    return a;
  }

  bool readDims(std::size_t & rows, std::size_t & cols)
  {
    long long r = 0;
    long long c = 0;
    if (!(std::cin >> r >> c) || r < 0 || c < 0)
    {
      return false;
    }
    rows = static_cast< std::size_t >(r);
    cols = static_cast< std::size_t >(c);
    return true;
  }

  bool readValues(int ** a, std::size_t rows, std::size_t cols)
  {
    for (std::size_t i = 0; i < rows; ++i)
    {
      for (std::size_t j = 0; j < cols; ++j)
      {
        if (!(std::cin >> a[i][j]))
        {
          return false;
        }
      }
    }
    return true;
  }

  std::size_t rowLength(std::size_t i, std::size_t n1, std::size_t m1, std::size_t n2, std::size_t m2)
  {
    return (i < n1 ? m1 : 0) + (i < n2 ? m2 : 0);
  }

  std::size_t maxOf(std::size_t a, std::size_t b)
  {
    return a > b ? a : b;
  }

  void print(const int * const * a, std::size_t n1, std::size_t m1, std::size_t n2, std::size_t m2)
  {
    const std::size_t n = maxOf(n1, n2);
    for (std::size_t i = 0; i < n; ++i)
    {
      const std::size_t len = rowLength(i, n1, m1, n2, m2);
      for (std::size_t j = 0; j < len; ++j)
      {
        std::cout << (j ? " " : "") << a[i][j];
      }
      std::cout << '\n';
    }
  }
}

int ** concat_rows(const int * const * lhs, std::size_t n1, std::size_t m1,
    const int * const * rhs, std::size_t n2, std::size_t m2)
{
  const std::size_t n = abdullaeva::maxOf(n1, n2);
  int ** res = new (std::nothrow) int *[n];
  if (!res)
  {
    return nullptr;
  }
  for (std::size_t i = 0; i < n; ++i)
  {
    const std::size_t len = abdullaeva::rowLength(i, n1, m1, n2, m2);
    res[i] = new (std::nothrow) int[len];
    if (!res[i])
    {
      abdullaeva::release(res, i);
      return nullptr;
    }
    std::size_t pos = 0;
    if (i < n1)
    {
      for (std::size_t j = 0; j < m1; ++j)
      {
        res[i][pos++] = lhs[i][j];
      }
    }
    if (i < n2)
    {
      for (std::size_t j = 0; j < m2; ++j)
      {
        res[i][pos++] = rhs[i][j];
      }
    }
  }
  return res;
}

int main()
{
  using namespace abdullaeva;

  std::size_t n1 = 0, m1 = 0;
  if (!readDims(n1, m1))
  {
    std::cerr << "Input error\n";
    return ERR_INPUT;
  }
  int ** a = allocRows(n1, m1);
  if (!a)
  {
    std::cerr << "Out of memory\n";
    return ERR_MEMORY;
  }
  if (!readValues(a, n1, m1))
  {
    std::cerr << "Input error\n";
    release(a, n1);
    return ERR_INPUT;
  }

  std::size_t n2 = 0, m2 = 0;
  if (!readDims(n2, m2))
  {
    std::cerr << "Input error\n";
    release(a, n1);
    return ERR_INPUT;
  }
  int ** b = allocRows(n2, m2);
  if (!b)
  {
    std::cerr << "Out of memory\n";
    release(a, n1);
    return ERR_MEMORY;
  }
  if (!readValues(b, n2, m2))
  {
    std::cerr << "Input error\n";
    release(b, n2);
    release(a, n1);
    return ERR_INPUT;
  }

  int ** res = concat_rows(a, n1, m1, b, n2, m2);
  if (!res)
  {
    std::cerr << "Out of memory\n";
    release(b, n2);
    release(a, n1);
    return ERR_MEMORY;
  }

  print(res, n1, m1, n2, m2);

  release(res, maxOf(n1, n2));
  release(b, n2);
  release(a, n1);
  return 0;
}
