#ifndef ITERATORS_HPP
# define ITERATORS_HPP

template<class IT, class PROXY_BUILDER>
struct ProxyIterator
{
  using TYPE = ProxyIterator<IT, PROXY_BUILDER>;

  IT it;
  PROXY_BUILDER proxyBuilder;

  constexpr auto &operator++()
  {
    ++it;
    return *this;
  }

  constexpr auto operator*()
  {
    return proxyBuilder(*it);
  }
};

template<class IT, class PROXY_BUILDER>
constexpr auto makeProxyIterator(IT &&it, PROXY_BUILDER &&proxyBuilder)
{
  return ProxyIterator<IT, PROXY_BUILDER>{it, proxyBuilder};
}

#endif
