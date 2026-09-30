#include "message.hpp"

namespace openlink
{

    Message::Message(MessageType type, const IdentityId &source, const IdentityId &destination, const std::vector<std::uint8_t> &data)
    : type(type), source(source), destination(destination), data(data)
    {
    }

    MessageType Message::GetType() const
    {
        return type;
    }

    const IdentityId &Message::GetSource() const
    {
        return source;
    }

    const IdentityId &Message::GetDestination() const
    {
        return destination;
    }

    const std::vector<std::uint8_t> &Message::GetData() const
    {
        return data;
    }

}