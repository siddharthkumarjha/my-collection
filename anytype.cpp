#include <cstdint>
#include <cxxabi.h>
#include <iomanip>
#include <iostream>
#include <memory>
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

template <typename T> std::shared_ptr<char> demangle(void) {
  std::shared_ptr<char> name{
      abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr),
      std::free};
  return name;
}

template <typename T>
[[gnu::always_inline]]
inline std::shared_ptr<char> demangle(T &&) {
  return demangle<T>();
}

template <typename T> struct is_string {
  static constexpr bool value = false;
};

template <typename Traits, typename Alloc>
struct is_string<std::basic_string<char, Traits, Alloc>> {
  static constexpr bool value = true;
};

template <typename T> constexpr bool is_string_like() {
  using expr = std::__remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>;

  if constexpr (std::is_same_v<expr, char>)
    return true;
  return false;
}

template <typename T> constexpr bool is_string_like_v = is_string_like<T>();
template <typename T> constexpr bool is_bool_v = std::is_same_v<T, bool>;
template <typename T> constexpr bool is_string_v = is_string<T>::value;

template <typename T>
concept BasicType = std::is_arithmetic_v<T> || is_string_v<T> ||
                    is_string_like_v<T> || is_bool_v<T>;

template <class... T> struct overloaded : T... {
  using T::operator()...;
};
template <class... T> overloaded(T...) -> overloaded<T...>;

class CommonDataType {
  std::variant<uint64_t, int64_t, double, std::string, bool> m_Data;

public:
  template <BasicType T> CommonDataType(const T &data) { write(data); }
  CommonDataType() : m_Data(static_cast<uint64_t>(0U)){};

  template <BasicType T> constexpr void write(const T &data) {
    if constexpr (is_bool_v<T>)
      m_Data = static_cast<bool>(data);
    else if constexpr (std::is_floating_point_v<T>)
      m_Data = static_cast<double>(data);
    else if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>)
      m_Data = static_cast<uint64_t>(data);
    else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>)
      m_Data = static_cast<int64_t>(data);
    else if constexpr (is_string_like<T>() &&
                       std::is_volatile_v<
                           std::remove_pointer_t<std::decay_t<T>>>)
      m_Data = const_cast<const char *>(data);
    else
      m_Data = data;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const CommonDataType &data) {
    std::visit(overloaded{[](auto &arg) { std::cout << arg << '\n'; },
                          [](const std::string &arg) {
                            std::cout << std::quoted(arg) << '\n';
                          },
                          [](const bool &arg) {
                            std::cout << std::boolalpha << arg
                                      << std::noboolalpha << '\n';
                          }},
               data.m_Data);
    return os;
  }
};

int main() {
  std::vector<CommonDataType> v = {0,   7L, "String", 8.8, std::string("hi"),
                                   true};
  volatile char const c[] = "hello";

  using expr = volatile const char *volatile const;
  std::printf("%s\n%s\n%s\n", demangle<expr>().get(), demangle(c).get(),
              demangle((c + 0)).get());

  v.emplace_back(c);

  for (const auto &ref : v) {
    std::cout << ref;
  }

  return 0;
}
