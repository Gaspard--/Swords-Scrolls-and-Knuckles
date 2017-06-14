#ifndef VECT_HPP_
# define VECT_HPP_

# include <type_traits>
# include <math.h>
# include "Util.hpp"

template <unsigned int dim, class T>
class Vect
{
private:
  T data[dim];

public:
  template<class Op, class P, class... U, typename std::enable_if<sizeof...(U) < dim>::type * = nullptr>
	   constexpr Vect(Function<T, P, Op> function, U... indices)
    : Vect(function, dim - sizeof...(indices) - 1, indices...)
  {}

  template<class Op, class P, class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(Function<T, P, Op> function, U... indices)
    : Vect(function.apply(indices)...)
  {}

  template<class V>
  constexpr Vect(V const (&other)[dim])
    : Vect(other, dim - 1u)
  {}

  template<class V, class... U, typename std::enable_if<sizeof...(U) < dim - 1>::type * = nullptr>
  constexpr Vect(V const (&other)[dim], unsigned int i, U... indices)
    : Vect(other, dim - sizeof...(indices) - 2u, i, indices...)
  {}

  template<class V, class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(V const (&other)[dim], U... indices)
    : Vect(static_cast<T>(other[indices])...)
  {}

  template<class V>
  constexpr Vect(Vect<dim, V> const &other)
    : Vect(other, dim - 1u)
  {}

  template<class V, class... U, typename std::enable_if<sizeof...(U) < dim - 1>::type * = nullptr>
  constexpr Vect(Vect<dim, V> const &other, unsigned int i, U... indices)
    : Vect(other, dim - sizeof...(indices) - 2u, i, indices...)
  {}

  template<class V, class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(Vect<dim, V> const &other, U... indices)
    : Vect(static_cast<T>(other[indices])...)
  {}

  template<class... U, typename std::enable_if<sizeof...(U) < dim - 1>::type * = nullptr>
  constexpr Vect(Vect<dim - 1, T> const &other, T added, U... indices)
    : Vect(other, added, indices..., dim - sizeof...(indices) - 2)
  {}

  template<class... U, typename std::enable_if<sizeof...(U) == dim - 1>::type * = nullptr>
  constexpr Vect(Vect<dim - 1, T> const &other, T added, U... indices)
    : Vect(other[indices]..., added)
  {}

  template<class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(U &&... ts)
  : data{static_cast<T>(ts)...}
  {}

  constexpr Vect() = default;

  template<class Operation>
  constexpr void applyOnSelf(Operation op)
  {
    for (unsigned int i(0); i != dim; ++i)
      data[i] = op(i);
  }

  constexpr T &operator[](unsigned int index)
  {
    return (data[index]);
  }

  constexpr T const &operator[](unsigned int index) const
  {
    return (data[index]);
  }

  constexpr Vect<dim, T>& operator+=(Vect<dim, T> const &other)
  {
    for (unsigned int i(0); i != dim; ++i)
      data[i] += other[i];
    return (*this);
  }

  constexpr Vect<dim, T>& operator-=(Vect<dim, T> const &other)
  {
    for (unsigned int i(0); i != dim; ++i)
      data[i] -= other[i];
    return (*this);
  }

  constexpr Vect<dim, T>& operator*=(Vect<dim, T> const &other)
  {
    for (unsigned int i(0); i != dim; ++i)
      data[i] *= other[i];
    return (*this);
  }

  constexpr Vect<dim, T>& operator/=(Vect<dim, T> const &other)
  {
    for (unsigned int i(0); i != dim; ++i)
      data[i] /= other[i];
    return (*this);
  }

  template<class U>
  constexpr Vect<dim, T>& operator/=(U const &other)
  {
    for (unsigned int i(0); i != dim; ++i)
      data[i] /= other;
    return (*this);
  }

  constexpr Vect<dim, T>& operator*=(T const &other)
  {
    for (unsigned int i(0); i != dim; ++i)
      data[i] *= other;
    return (*this);
  }


  constexpr Vect<dim, T>& operator^=(Vect<dim, T> const &other)
  {
    for (unsigned int i(0); i != dim; ++i)
      data[i] ^= other[i];
    return (*this);
  }

  /**
   * This is not operator== because that one should operate component-wise
   */
  constexpr bool equals(Vect<dim, T> const& other) const
  {
    for (unsigned int i = 0; i < dim; i++)
      if (data[i] != other[i])
	  return false;
    return true;
  }

  template<class Op>
  constexpr static Vect<dim, T> applyOp(Op const op)
  {
    return Vect<dim, T>(Function<T, unsigned int, Op>(op));
  }

  template<class Op>
  constexpr Vect<dim, T> map(Op const op) const
  {
    return applyOp([op, this](unsigned int i) {
	return (op(data[i]));
      });
  }

  template<class Op, class U>
  constexpr Vect<dim, T> applyOpPerComponent(Op op, const Vect<dim, U>& other) const
  {
    return applyOp([this, other, op](unsigned int i) {
	return op((*this)[i], other[i]);
      });
  }

  template<class U>
  constexpr Vect<dim, T> operator+(Vect<dim, U> const &other) const
  {
    return Vect<dim, T>(*this) += other;
  }

  constexpr Vect<dim, T> operator*(Vect<dim, T> const &other) const
  {
    return Vect<dim, T>(*this) *= other;
  }

  constexpr Vect<dim, T> operator*(T const &other) const
  {
    return Vect<dim, T>(*this) *= other;
  }

  constexpr Vect<dim, T> operator/(Vect<dim, T> const &other) const
  {
    return Vect<dim, T>(*this) /= other;
  }

  template<class U>
  constexpr Vect<dim, T> operator/(U const &other) const
  {
    return Vect<dim, T>(*this) /= other;
  }

  constexpr Vect<dim, T> operator%(Vect<dim, T> const &other) const
  {
    return Vect<dim, T>(*this) %= other;
  }

  constexpr Vect<dim, T> operator-(Vect<dim, T> const &other) const
  {
    return Vect<dim, T>(*this) -= other;
  }

  constexpr Vect<dim, T> operator-(void) const
  {
    return map([](T t){return (-t);});
  }

private:


public:
  constexpr T sum(void) const
  {
    T result(0);

    for (unsigned int i = 0; i < dim; ++i)
      result += data[i];
    return (result);
  }
  
  constexpr T scalar(Vect<dim, T> const &other) const
  {
    return ((*this * other).sum());
  }

  constexpr T length2() const
  {
    return (this->scalar(*this));
  }

  constexpr Vect<dim, T> normalized() const
  {
    return length2() > 0 ? ((*this) / std::sqrt(length2())) : *this;
  }

  constexpr bool all() const
  {
    unsigned int i(0);

    for (; i != dim && data[i]; ++i)
    return (i == dim);
  }

  template<class L>
  static void forEach(Vect<dim, T> begin, Vect<dim, T> end, L l)
  {
    Vect<dim, T> index(begin);

    for (index[0] = begin[0]; index[0] < end[0]; ++index[0])
      for (index[1] = begin[1]; index[1] < end[1]; ++index[1])
	l(index);
  }

  template<unsigned int n = dim, typename std::enable_if<(n >= 1)>::type * = nullptr>
  constexpr T const &x() const
  {
    return data[0];
  }

  template<unsigned int n = dim, typename std::enable_if<(n >= 2)>::type * = nullptr>
  constexpr T const &y() const
  {
    return data[1];
  }
};

#include <ostream>

template<unsigned int dim, class T>
std::ostream &operator<<(std::ostream &out, Vect<dim, T> vect)
{
  out << "(";
  for (unsigned int i(0); i != dim - 1; ++i)
    out << vect[i] << ", ";
  out << vect[dim - 1] << ")";
  return out;
}

#endif // VECT_HPP_
