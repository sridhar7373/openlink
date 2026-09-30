#include "identity.hpp"
#include <fstream>
#include <sodium.h>

namespace openlink
{

    Identity::Identity()
    {
        crypto_sign_keypair(public_key.data(), private_key.data());
        crypto_hash_sha256(id.data(), public_key.data(), public_key.size());
    }

    const IdentityId &Identity::GetId() const
    {
        return id;
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

        if (!file)
        {
            return false;
        }

        crypto_sign_ed25519_sk_to_pk(public_key.data(), private_key.data());
        crypto_hash_sha256(id.data(), public_key.data(), public_key.size());

        return true;
    }

}