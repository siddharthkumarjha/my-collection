#include <cstdint>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <variant>
#include <vector>

/*
[](auto &arg) { std::cout << arg << '\n'; }


is an expression which yields a function object, if you did something like

auto lambda = [](auto &arg) { std::cout << arg << '\n'; };


it would somewhat similar to doing

struct __lambda1
{
  auto operator()(auto& arg) const { std::cout << arg << '\n'; }
};
auto lambda = __lambda1{};

if you throw in the other lambda that starts looking like

struct __lambda2
{
  auto operator()(const std::string& arg) const {
    std::cout << std::quote(arg) << '\n';
  }
};


so "overloaded" which in that case would be overloaded<__lambda1, __lambda2>
would be kinda equivalent to

struct overloaded_specialization : __lambda1, __lambda2
{
  using __lambda1::operator();
  using __lambda2::operator();
};


so in effect it's sort of like you had

struct overloaded_rewrite
{
  auto operator()(auto& arg) const { std::cout << arg << '\n'; }

  auto operator()(const std::string& arg) const {
    std::cout << std::quote(arg) << '\n';
  }
};

and you make an object instance of that
there's no "returning" the callable to be done anywhere
the visitor is the callable
*/

template <typename T> struct is_string {
  static constexpr bool value = false;
};

template <typename Traits, typename Alloc>
struct is_string<std::basic_string<char, Traits, Alloc>> {
  static constexpr bool value = true;
};

template <typename T> constexpr bool is_string_like() {
  using expr = std::decay_t<std::__remove_cvref_t<T>>;

  if constexpr (std::is_same_v<expr, char *>)
    return true;
  return false;
}

template <typename T> constexpr bool is_string_v = is_string<T>::value;

template <typename T>
concept BasicType =
    std::is_arithmetic_v<T> || is_string_v<T> || is_string_like<T>();

class CommonDataType {
  std::variant<uint64_t, int64_t, double, std::string> m_Data;

  template <class... T> struct overloaded : T... {
    using T::operator()...;
  };
  template <class... T> overloaded(T...) -> overloaded<T...>;

public:
  template <BasicType T> CommonDataType(const T &data) { write(data); }
  CommonDataType() : m_Data(static_cast<uint64_t>(0U)){};

  template <BasicType T> constexpr void write(const T &data) {
    if constexpr (std::is_floating_point_v<T>)
      m_Data = static_cast<double>(data);
    else if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>)
      m_Data = static_cast<uint64_t>(data);
    else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>)
      m_Data = static_cast<int64_t>(data);
    else
      m_Data = data;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const CommonDataType &data) {
    std::visit(overloaded{[](auto &arg) { std::cout << arg << '\n'; },
                          [](const std::string &arg) {
                            std::cout << std::quoted(arg) << '\n';
                          }},
               data.m_Data);
    return os;
  }
};

int main() {
  std::vector<CommonDataType> v = {0, 7L, "String", 8.8, std::string("hi")};

  for (const auto &ref : v) {
    std::cout << ref;
  }
  return 0;
}
