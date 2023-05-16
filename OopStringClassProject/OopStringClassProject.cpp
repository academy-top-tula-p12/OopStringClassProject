#include <iostream>
#include "String.h"

int main()
{
    String s1("Hello world");
    /*std::cout << s1.Length() << " " << s1 << "\n";
    s1.Erase(2, 4);
    std::cout << s1.Length() << " " << s1 << "\n";*/
    String s2("***");

    std::cout << s1.Insert(s2, 3); // Hel***lo world
}
