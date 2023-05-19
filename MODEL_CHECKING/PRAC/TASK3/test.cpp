#include "dpll.hpp"

void CNFSpec(const std::string &filename, const bool expected)
{
    model::dpll::Solver solver(filename);
    // auto start = std::chrono::high_resolution_clock::now();
    bool result = solver.solve();
    if (result != expected)
    {
        std::cout << "CNFSpec failed for " << filename << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        std::cout << "Got: " << result << std::endl;
        exit(1);
    }
    // auto end = std::chrono::high_resolution_clock::now();
    // std::cout << "CNFSpec for " << filename << " took "
    //           << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0
    //           << " seconds" << std::endl
    //           << std::endl;
}

void Test(const std::string &dir, const bool expected)
{
    auto start = std::chrono::high_resolution_clock::now();
    if (std::filesystem::exists(dir))
    {
        if (!std::filesystem::is_directory(dir))
        {
            CNFSpec(dir, expected);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Test for " << dir << " took "
                      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0
                      << " seconds" << std::endl
                      << std::endl;
            return;
        }
        for (const auto &entry : std::filesystem::directory_iterator(dir))
        {
            if (entry.is_directory())
            {
                Test(entry.path(), expected);
            }
            else
            {
                CNFSpec(entry.path(), expected);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Test for " << dir << " took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0
              << " seconds" << std::endl
              << std::endl;
}
int main(int argc, char const *argv[])
{
    // Test("tests/sat", true);
    // Test("tests/unsat", false);
    Test("tests/sat/uf50-218", true);
    Test("tests/sat/aim", true);
    Test("tests/unsat/aim", false);
    Test("tests/unsat/UUF50.218.1000", false);
    Test("tests/unsat/pigeon-hole", false);
    Test("tests/sat/hanoi4.cnf", true);

    return 0;
}
