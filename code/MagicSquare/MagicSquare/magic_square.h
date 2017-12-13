#ifndef MAGIC_SQUARE_H_INCLUDED
#define MAGIC_SQUARE_H_INCLUDED

#include <cstdio>
#include <cstring>

class MagicSquare {
public:
  MagicSquare(int n) : _order(n) {
    _matrix = new int[_order * _order];
    if (_order != 2)
      construct_matrix();
  }

  virtual ~MagicSquare() { delete [] _matrix; _matrix = NULL; }

  void print_matrix() { // 输出八个同构的幻方
    if (_order == 2) return;
    int n = _order;
    int start[] = {0, n-1, n*(n-1), 0, n*n-1, n*(n-1), n-1, n*n-1};
    int step[] = {1, -1, -n, n, -1, +1, +n, -n};
    int change[] = {n, n, 1, 1, -n, -n, -1, -1};

    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = start[i] + change[i] * j, s = 0; s < n
        && 0 <= k && k < _order * _order; k += step[i], ++s)
          printf("%4d ", _matrix[k]);
        printf("\n");
      }
      printf("\n");
    }
  }

  void print() { // 输出对应的幻方
    if (_order == 2) return;
    for (int i = 0; i < _order; ++i) {
      for (int j = 0; j < _order; ++j) {
        printf("%4d ", _matrix[i * _order + j]);
      }
      printf("\n");
    }
  }

private:
  int *_matrix;
  int _order;

  void construct_matrix() {
    if (_order % 2 == 1)
      construct_odd_square();
    else if (_order % 4 == 0)
      construct_doubly_even_square();
    else
      construct_singly_even_square();
  }

  void construct_odd_square() { // 奇数阶幻方的菱形算法, O(n ^ 2)
    memset(_matrix, 0, sizeof(int) * _order * _order);
    for (int i = 1, r = 0, c = (_order >> 1); i <= _order * _order; ++i) {
      _matrix[r * _order + c] = i;
      if (_matrix[((r-1+_order)%_order) * _order + ((c+1)%_order)]) ++r;
      else r = (r-1+_order)%_order, c = (c+1)%_order;
    }
  }

  void construct_doubly_even_square() { // 双偶数阶幻方的对角线算法, O(n ^ 2)
    int n = _order;
    memset(_matrix, 0, sizeof(int) * n * n);
    for (int i = 0; i < n*n; ++i) {
      int r = i / n, c = i%n;
      if (!(r%4 == c%4 || r%4 + c%4 == 3)) _matrix[i] = i + 1;
    }
    for (int j = 0; j < n*n; ++j)
      if (!_matrix[j]) _matrix[j] = n*n - j;
  }

  void construct_singly_even_square() { // 单偶数阶幻方的律克斯算法
    int n = _order;
    memset(_matrix, 0, sizeof(int) * n * n);
    int odd_n = n >> 1;
    for (int i = 1, r = 0, c = (odd_n >> 1); i <= odd_n * odd_n; ++i) {
      if (r <= (odd_n >> 1)) { // L
        int up_left = r * n * 2 + c * 2;
        int num = 1 + (i - 1) * 4;
        _matrix[up_left + 1] = num;
        _matrix[up_left + n] = num + 1;
        _matrix[up_left + n + 1] = num + 2;
        _matrix[up_left] = num + 3;
      }
      else if (r == (odd_n >> 1) + 1) { // U
        int up_left = r * n * 2 + c * 2;
        int num = 1 + (i - 1) * 4;
        _matrix[up_left + 1] = num + 3;
        _matrix[up_left + n] = num + 1;
        _matrix[up_left + n + 1] = num + 2;
        _matrix[up_left] = num;
      }
      else { // X  (r == odd_n - 1)
        int up_left = r * n * 2 + c * 2;
        int num = 1 + (i - 1) * 4;
        _matrix[up_left + 1] = num + 3;
        _matrix[up_left + n] = num + 2;
        _matrix[up_left + n + 1] = num + 1;
        _matrix[up_left] = num;
      }

      if (_matrix[((r-1+odd_n)%odd_n) * 2 * n + ((c+1)%odd_n) * 2]) ++r;
      else r = (r-1+odd_n)%odd_n, c = (c+1)%odd_n;
    }
    int r = odd_n >> 1, c = odd_n >> 1;
    int up_left = r * 2 * n + c * 2;
    int tmp = _matrix[up_left]; _matrix[up_left] = _matrix[up_left + 1]; _matrix[up_left + 1] = tmp;
    up_left += 2 * n;
    tmp = _matrix[up_left]; _matrix[up_left] = _matrix[up_left + 1]; _matrix[up_left + 1] = tmp;
  }
};
#endif // MAGIC_SQUARE_H_INCLUDED
