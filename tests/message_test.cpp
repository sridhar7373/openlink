#include "../src/identity.hpp"
#include "../src/message.hpp"
#include "../src/packet.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    openlink::Identity source("source.key");
    openlink::Identity destination("destination.key");

    std::string text = "OpenLink is an experimental protocol designed to provide "
                       "simple communication between devices and services. It should "
                       "work across different transports such as UDP, TCP, Wi-Fi, "
                       "Bluetooth, serial connections, LoRa, and other networks. "
                       "The application should only need to create a message while "
                       "OpenLink handles packet creation, fragmentation, transport, "
                       "and reassembly internally.";

    std::vector<std::uint8_t> data(text.begin(), text.end());

    openlink::Message message(openlink::MessageType::DATA, source.GetId(), destination.GetId(), data);

    openlink::Packets packets = openlink::Packet::Encode(message);

    std::cout << "Message: " << text << "\n";
    std::cout << "Payload size: " << data.size() << " bytes\n";

    std::cout << "Packets: " << packets.size() << "\n";

    for (std::size_t i = 0; i < packets.size(); ++i)
    {
        std::cout << "Packet " << i << ": " << packets[i].size() << " bytes\n";
    }

    openlink::Message decoded_message(openlink::MessageType::DATA, source.GetId(), destination.GetId(), {});

    if (!openlink::Packet::Decode(packets, decoded_message))
    {
        std::cout << "Failed to decode packets.\n";
        return 1;
    }

    std::string decoded_text(decoded_message.GetData().begin(), decoded_message.GetData().end());
    std::cout << "Decoded message: "<< decoded_text << "\n";

    std::cout << "Decoded size: " << decoded_message.GetData().size() << " bytes\n";

    return 0;
}