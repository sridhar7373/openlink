#include "identity.hpp"

#include <algorithm>
#include <fstream>
#include <sodium.h>

namespace openlink
{

    Identity::Identity(const char *path)
    {
        if (!Load(path))
        {
            Generate();
            Save(path);
        }
    }

    const IdentityId &Identity::GetId() const
    {
        return id;
    }

    bool Identity::Generate()
    {
        if (crypto_sign_keypair(public_key.data(), private_key.data()) != 0)
        {
            return false;
        }

        std::array<std::uint8_t, crypto_hash_sha256_BYTES> hash;
        crypto_hash_sha256(hash.data(), public_key.data(), public_key.size());
        std::copy_n(hash.begin(), id.size(), id.begin());

        return true;
    }

    bool Identity::Save(const char *path) const
    {
        std::ofstream file(path, std::ios::binary);

        if (!file)
        {
            return false;
        }

        file.write(reinterpret_cast<const char *>(private_key.data()), private_key.size());

        return file.good();
    }

    bool Identity::Load(const char *path)
    {
        std::ifstream file(path, std::ios::binary);

        if (!file)
        {
            return false;
        }

        file.read(reinterpret_cast<char *>(private_key.data()), private_key.size());

        if (!file || file.gcount() != static_cast<std::streamsize>(private_key.size()))
        {
            return false;
        }

        if (crypto_sign_ed25519_sk_to_pk(public_key.data(), private_key.data()) != 0)
        {
            return false;
        }

        std::array<std::uint8_t, crypto_hash_sha256_BYTES> hash;
        crypto_hash_sha256(hash.data(), public_key.data(), public_key.size());
        std::copy_n(hash.begin(), id.size(), id.begin());

        return true;
    }

}