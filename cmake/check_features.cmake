include(CheckCXXSourceCompiles)

# C++23 deducing this
check_cxx_source_compiles("
struct X {
    void f(this X& self) {}
};
int main() {
    X x; x.f();
    return 0;
}"    HAS_DEDUCING_THIS)

# std::format
check_cxx_source_compiles("
#include <format>
#include <string>
int main() {
    std::string s = std::format(\"Hello {}!\", 123);
    return 0;
}"    HAS_STD_FORMAT)

# std::expected
check_cxx_source_compiles("
#include <expected>
#include <string>
std::expected<int, std::string> func(bool ok) {
    if (ok) return 42;
    return std::unexpected(\"error\");
}
int main() {
    auto e = func(true);
    return e.value_or(-1);
}"    HAS_STD_EXPECTED)

message(STATUS "HAS_DEDUCING_THIS = ${HAS_DEDUCING_THIS}")
message(STATUS "HAS_STD_FORMAT    = ${HAS_STD_FORMAT}")
message(STATUS "HAS_STD_EXPECTED  = ${HAS_STD_EXPECTED}")
