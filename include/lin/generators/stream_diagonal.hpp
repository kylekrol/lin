// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/stream_diagonal.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_GENERATORS_STREAM_DIAGONAL_HPP_
#define LIN_GENERATORS_STREAM_DIAGONAL_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

template <class E>
class StreamDiagonal : public Stream<StreamDiagonal<E>> {
  static_assert(conjunction<is_matrix<StreamDiagonal<E>>, is_square<StreamDiagonal<E>>>::value,
      "StreamDiagonal must have square, matrix traits");
  static_assert(is_vector<E>::value,
      "Backing type for a StreamDiagonal must have vector traits");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<StreamDiagonal<E>> Traits;

 private:
  Stream<E> const &_stream;

 protected:
  using Stream<StreamDiagonal<E>>::derived;

 public:
  using Stream<StreamDiagonal<E>>::size;
  using Stream<StreamDiagonal<E>>::eval;

  constexpr StreamDiagonal() = delete;
  constexpr StreamDiagonal(StreamDiagonal<E> const &) = default;
  constexpr StreamDiagonal(StreamDiagonal<E> &&) = default;
  constexpr StreamDiagonal<E> &operator=(StreamDiagonal<E> const &) = default;
  constexpr StreamDiagonal<E> &operator=(StreamDiagonal<E> &&) = default;

  constexpr StreamDiagonal(Stream<E> const &stream)
  : _stream(stream) { }

  constexpr size_t rows() const {
    return _stream.size();
  }

  constexpr size_t cols() const {
    return _stream.size();
  }

  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    LIN_ASSERT(0 <= i && i <= rows());
    LIN_ASSERT(0 <= j && j <= cols());

    return i == j ? _stream(i) : typename Traits::elem_t(0);
  }

  constexpr typename Traits::elem_t operator()(size_t i) const {
    LIN_ASSERT(0 <= i && i <= size());

    return (*this)(i / cols(), i % cols());
  }
};

template <class E>
struct _elem<StreamDiagonal<E>> {
  typedef _elem_t<E> type;
};

template <class E>
struct _dims<StreamDiagonal<E>> {
  static constexpr size_t rows = _vector_dims<E>::length;
  static constexpr size_t cols = _vector_dims<E>::length;
  static constexpr size_t max_rows = _vector_dims<E>::max_length;
  static constexpr size_t max_cols = _vector_dims<E>::max_length;
};
}  // namespace internal
}  // namespace lin

#endif
