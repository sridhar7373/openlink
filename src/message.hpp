#pragma once

#include "identity.hpp"

#include <cstdint>
#include <vector>

namespace openlink
{

enum class MessageType : std::uint8_t
{
    DATA = 0x01
};

class Message
{
public:
    Message(
        MessageType type,
        const IdentityId& source,
        const IdentityId& destination,
        const std::vector<std::uint8_t>& data
    );

    MessageType GetType() const;
    const IdentityId& GetSource() const;
    const IdentityId& GetDestination() const;
    const std::vector<std::uint8_t>& GetData() const;

private:
    MessageType type;
    IdentityId source;
    IdentityId destination;
    std::vector<std::uint8_t> data;
};

}