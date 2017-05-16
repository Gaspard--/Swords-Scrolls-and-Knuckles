## Basic stuff

- NO FILE HEADERS
- header guards are expected in .hpp
- MACROS should not be abused. (should only be used for plateforme specific stuff)

## General naming:

- Naming is important: functions should do what is said on the Tin.

- No name preceded by an underscore.

- Class names in PascalCase.

- Variable & function names in camelCase.

- Macros, constexpr variables & template parameters in UPPER_CASE.

- File naming in CamelCase.

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
### Please indent your code.

Indenting levels should be 2 spaces wide.

This part may be controversial:
Tabs are 8 spaces (Rational: because terminals tend to display them like that).
Only indent with tabs if your code remains readable in such an environnment.

The exact indentation does not matter. It is only important that the code is readable.

## About the code itself

- Please be nice to ___miss Cache___. (✿◕‿◕✿)

### RAII
Rational: robustness

- Please adopt strict RAII: no `new`s should be alone. Use `std::unique_ptr`, `std::shared_ptr` or something.
- Avoid explicit ressource handling. (encapsulate as much as possible)
- Functions which have to be paired, should be maintained as objects.
- Pointers are discouraged.

Exceptions to these rules may be granted to this rule if interacting with a cubbersome API, however then exceptions should remain local.

### Compile-time over Run-time
Rational: speed and robustness

- Templating is encouraged, as well as `constexpr` usage, however careful: we have to handle more compilers than gcc.
- __Anything that can be `constexpr` should be. Anything that can be `const` should be.__
- Use of the _Standart Template Library_ over home-made loops is encouraged.
- Avoid useless checks. Code should be verified compile-time, not run-time.

### Virtual inheritence

- Virtual inheritence must be justified.
- __`dynamique_cast` and any other form of _Run-Time Type Information_ IS FORBIDDEN.__

### Classes

- Use struct if all your members are public.
- Use `static_cast` when casting classes.

#### Constructors:

- Be clear if your object is movable or copiable or none of both.
- Use the default and delete keyword when possible.
- Don't forget to qualify constructors as `constexpr` when possible when using them.
- Use the copy-and-swap idiom when appropriate. Use swap in move operator=.

#### Operators:

- Operators should be logical, `c = a + b` and `c = a; c += b` should have the same result.
- Think about operator precedence when overloading.
- Define `@` from `@=` (i.e. `+` from `+=`) to avoid code duplication.

```
constexpr T &T::operator@=(T const &other);

constexpr T operator@(T const &a, T const &b)
{
  return T(a) += b;
}
```

### Casting

- Use C-style casts when converting primitive types.
- Use a `static_cast` if a classe is involved,
- Other casts are strongly discouraged, except `dynamique_cast` which is forbidden.

## NOTE: this guide is incomplete, and may change in the future. 
