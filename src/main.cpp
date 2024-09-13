#include "../headers/includes.hpp"

int main()
{
    auto a = IO::readFile("C:\\Windows\\System32\\calc.exe");
    VM vm;
    vm.init(a);
    auto b = vm.protect(KEY);

    vm.pack();

    return 0;
}