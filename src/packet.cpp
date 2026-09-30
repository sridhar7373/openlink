#include "packet.hpp"

namespace openlink
{

    Packets Packet::Encode(const Message &message)
    {
        const auto &source = message.GetSource();
        const auto &destination = message.GetDestination();
        const auto &payload = message.GetData();

        constexpr std::size_t header_size = 37;
        constexpr std::size_t max_payload_size =
            OPENLINK_MAX_PACKET_SIZE - header_size;

        Packets packets;

        std::size_t offset = 0;
        std::uint8_t fragment = 0;

        while (offset < payload.size())
        {
            const std::size_t remaining = payload.size() - offset;
            const std::size_t payload_size = remaining < max_payload_size ? remaining : max_payload_size;

            PacketData packet;
            packet.reserve(header_size + payload_size);

            packet.push_back(OPENLINK_PACKET_VERSION);
            packet.push_back(static_cast<std::uint8_t>(message.GetType()));

            packet.insert(packet.end(), source.begin(), source.end());
            packet.insert(packet.end(), destination.begin(), destination.end());

            packet.push_back(fragment);

            const bool more = offset + payload_size < payload.size();
            packet.push_back(more ? PACKET_FLAG_MORE : 0);

            packet.push_back(static_cast<std::uint8_t>(payload_size));

            packet.insert(packet.end(), payload.begin() + offset, payload.begin() + offset + payload_size);

            packets.push_back(std::move(packet));

            offset += payload_size;
            ++fragment;
        }

        return packets;
    }

    bool Packet::Decode(const Packets &packets, Message &message)
    {
        constexpr std::size_t header_size = 37;

        if (packets.empty())
        {
            return false;
        }

        IdentityId source;
        IdentityId destination;
        MessageType type;

        std::vector<std::uint8_t> payload;

        for (std::size_t i = 0; i < packets.size(); ++i)
        {
            const auto &packet = packets[i];

            if (packet.size() < header_size)
            {
                return false;
            }

            std::size_t offset = 0;

            if (packet[offset++] != OPENLINK_PACKET_VERSION)
            {
                return false;
            }

            const auto packet_type =
                static_cast<MessageType>(packet[offset++]);

            if (i == 0)
            {
                type = packet_type;
            }
            else if (packet_type != type)
            {
                return false;
            }

            IdentityId packet_source;

            for (auto &byte : packet_source)
            {
                byte = packet[offset++];
            }

            IdentityId packet_destination;

            for (auto &byte : packet_destination)
            {
                byte = packet[offset++];
            }

            if (i == 0)
            {
                source = packet_source;
                destination = packet_destination;
            }
            else if (
                packet_source != source ||
                packet_destination != destination)
            {
                return false;
            }

            const std::uint8_t fragment = packet[offset++];

            if (fragment != i)
            {
                return false;
            }

            const std::uint8_t flags = packet[offset++];
            const std::uint8_t payload_size = packet[offset++];

            if (packet.size() != offset + payload_size)
            {
                return false;
            }

            payload.insert(payload.end(), packet.begin() + offset, packet.end());

            const bool more = (flags & PACKET_FLAG_MORE) != 0;

            if (i + 1 < packets.size() && !more)
            {
                return false;
            }

            if (i + 1 == packets.size() && more)
            {
                return false;
            }
        }

        message = Message(type, source, destination, payload);

        return true;
    }

}