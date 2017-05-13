## Basic stuff

- NO FILE HEADERS
- header guards are expected in .hpp
- MACROS should not be abused. (should only be used for plateforme specific stuff)

## General naming:

No name preceded by an underscore.

Class name in PascalCase.
Variable & function names in camelCase
Macros, constexpr variables & template parameters in UPPER_CASE.
File naming in CamelCase.

## Braces:

Both styles are accepted:
```
a {
}

a
{
}
```
However if the first style makes the code hard to read, it may be rejected.

## Spacing:

Please use spaces adequatelly:
- after a ','
- around binary operators
- no space for unary operators

Spaces on empty lines are tolerated.

## Indenting
Please indent your code.

Indenting levels should be 2 spaces wide.

This part may be controversial:
Tabs are 8 spaces (Rational: because terminals tend to display them like that).
Only indent with tabs if your code remains readable in such an environnment.

The exact indentation does not matter. It is only important that the code is readable.

## About the code itself

Please adopt strict RAII: no _new_s should be alone. Use std::unique_ptr, std::shared_ptr or something.
Avoid explicit ressource handling. (encapsulate as much as possible)
Functions which have to be paired, should be maintained as objects.
(Exceptions may be granted to this rule if interacting with a cubbersome API)

Naming is important: functions should do what is said on the Tin.
Templating is encouraged, as well as constexpr usage, however careful: we have to handle more compilers than gcc.
(Rational: speed and robustness)
Pointers are discouraged.
Use of the standart library over home-made loops is encouraged.
Virtual inheritence must be justified. Please be nice to _miss Cache_.
Avoid useless checks. Code should be verified compile-time, not run-time.
Anything that can be constexpr should be. Anything that can be const should be.
Use struct if all your members are public.

### Constructors:
Be clear if your object is movable or copiable or none of both.
Use the default and delete keyword when possible. Don't forget to qualify as constexpr when possible when using them.
Use the copy-and-swap idiom when appropriate. Use swap in move operator=.

### Operators:

Define `@` from `@=` (i.e. `+` from `+=`) to avoid code duplication.
```
constexpr T &T::operator@=(T const &other);

constexpr T operator@(T const &a, T const &b)
{
  return T(a) += b;
}
```

## NOTE: this guide is incomplete, and may change in the future. 
