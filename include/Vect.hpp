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

  template<class V, std::size_t... Indices, typename std::enable_if<!std::is_same<T, V>::value>::type * = nullptr>
  constexpr Vect(Vect<dim, V> const &other,  std::index_sequence<Indices...>)
  : Vect(static_cast<T>(other[Indices])...)
  {}

  template<std::size_t... Indices>
  constexpr Vect(Vect<dim, T> &&other, std::index_sequence<Indices...>)
  : data{std::move(other[Indices])...}
  {}

public:
  template<class V, typename std::enable_if<!std::is_same<T, V>::value>::type * = nullptr>
  constexpr Vect(Vect<dim, V> const &other)
  : Vect(other, std::make_index_sequence<dim>{})
  {}

  template<typename std::enable_if<std::is_move_constructible<T>::value>::type * = nullptr>
  constexpr Vect(Vect<dim, T> &&other)
  : Vect(std::forward<Vect<dim, T>>(other), std::make_index_sequence<dim>{})
  {}

  template<class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(U &&... ts)
  : data{std::forward<U>(ts)...}
  {}

  constexpr Vect() = default;

  constexpr Vect<dim, T> &operator=(Vect<dim, T> other)
  {
    for (std::size_t i(0); i < dim; ++i)
      data[i] = std::move(other[i]);
    return *this;
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

private:
  template<std::size_t... Indexes>
  constexpr Vect<dim, T> minus(std::index_sequence<Indexes...>) const
  {
    return Vect<dim, T>(-data[Indexes]...);
  }

public:
  constexpr Vect<dim, T> operator-(void) const
  {
    return minus(std::make_index_sequence<dim>{});
  }

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

  constexpr T *begin()
  {
    return (data);
  }

  constexpr T *end()
  {
    return (data + dim);
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
