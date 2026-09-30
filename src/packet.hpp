#pragma once

#include "identity.hpp"
#include "message.hpp"

#include <cstdint>
#include <vector>

#define OPENLINK_PACKET_VERSION 1
#define OPENLINK_MAX_PACKET_SIZE 128

#define PACKET_FLAG_MORE 0x01

namespace openlink
{

    using PacketData = std::vector<std::uint8_t>;
    using Packets = std::vector<PacketData>;

    class Packet
    {
    public:
        static Packets Encode(const Message &message);
        static bool Decode(const Packets &packets, Message &message);
    };

}