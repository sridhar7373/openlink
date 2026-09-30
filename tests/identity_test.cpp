#include "../src/identity.hpp"

#include <iostream>
#include <iomanip>

int main()
{
    openlink::Identity identity;

    if (!identity.Load("identity.key"))
    {
        std::cout << "Failed to load identity.\n";
        return 1;
    }

    std::cout << "Identity ID: ";

    for (const auto byte : identity.GetId())
    {
        std::cout << std::hex << static_cast<int>(byte);
    }

    std::cout << "\n";

    if (identity.Save("identity.key"))
    {
        std::cout << "Identity saved.\n";
    }
    else
    {
        std::cout << "Failed to save identity.\n";
    }

    return 0;
}