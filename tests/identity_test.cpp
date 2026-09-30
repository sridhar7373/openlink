#include "../src/identity.hpp"

#include <iostream>
#include <iomanip>

int main()
{
    openlink::Identity identity("identity.key");

    std::cout << "Identity ID: ";

    for (const auto byte : identity.GetId())
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    std::cout << "\n";

    return 0;
}