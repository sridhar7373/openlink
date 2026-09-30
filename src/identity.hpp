#pragma once

#include <cstdint>
#include <array>

namespace openlink
{

using PublicKey = std::array<std::uint8_t, 32>;
using PrivateKey = std::array<std::uint8_t, 64>;
using IdentityId = std::array<std::uint8_t, 16>;

class Identity
{
public:
    Identity(const char *path);

    const IdentityId& GetId() const;

    bool Generate();
    bool Save(const char* path) const;
    bool Load(const char* path);

private:
    PublicKey public_key;
    PrivateKey private_key;
    IdentityId id;
};

}