#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <exception>
#include <string>

namespace mini_catch {
struct TestRegistry {
    std::vector<std::pair<std::string, std::function<void()>>> tests;
    void add(const std::string& name, std::function<void()> func) {
        tests.push_back({name, func});
    }
    int run() {
        int failures = 0;
        for (auto& t : tests) {
            try {
                t.second();
                std::cout << "[PASSED] " << t.first << "\n";
            } catch (const std::exception& e) {
                std::cout << "[FAILED] " << t.first << " - " << e.what() << "\n";
                ++failures;
            } catch (...) {
                std::cout << "[FAILED] " << t.first << " - unknown error\n";
                ++failures;
            }
        }
        return failures;
    }
};

inline TestRegistry& registry() {
    static TestRegistry inst;
    return inst;
}

struct AutoReg {
    AutoReg(const std::string& name, std::function<void()> func) {
        registry().add(name, func);
    }
};

struct TestFailure : public std::exception {
    const char* what() const noexcept override { return "requirement failed"; }
};
} // namespace mini_catch

#define TEST_CASE(name) \
    void test_##name(); \
    static mini_catch::AutoReg reg_##name(#name, test_##name); \
    void test_##name()

#define REQUIRE(cond) \
    do { if (!(cond)) throw mini_catch::TestFailure(); } while (false)

#ifdef CATCH_CONFIG_MAIN
int main() {
    return mini_catch::registry().run();
}
#endif
