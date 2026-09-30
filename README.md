# OpenLink

OpenLink is an experimental project to explore a simple protocol for communication between devices and services.

The main idea is to make device communication easy to understand and easy to implement.

OpenLink is still in the early stage. We are first studying existing protocols and trying to understand if there is a real need for a new one.

## What are we trying to solve?

There are already many protocols like HTTP, MQTT, CoAP, Gemini and Reticulum.

Each of them solves different problems.

We want to explore if we can create a simple communication model that can work across different types of devices and networks.

For example:

```text
Computer
Phone
Server
Raspberry Pi
ESP32
Other devices
```

And different transports:

```text
Wi-Fi
Ethernet
Internet
UDP
TCP
Bluetooth
Serial
LoRa
Radio
Mesh networks
```

The application should not need to care too much about how the devices are connected.

## Inspiration

OpenLink is inspired by existing protocols and networking projects.

Reticulum is one of the projects that made us interested in this area. It shows how communication can work across different types of networks.

We are also looking at HTTP, CoAP, MQTT and Gemini to understand what ideas we can learn from them.

OpenLink is **not** trying to copy or replace these protocols.

## What we want to explore

* Can the protocol be simple to understand?
* Can it work with different transports?
* Can it work on small devices as well as computers and servers?
* Can it use low bandwidth efficiently?
* Can devices and services be discovered easily?
* Can devices communicate without depending on the normal Internet?
* Can developers implement it without needing to learn a lot of new concepts?

## Current Status

🚧 **Early research and design stage**

Nothing is finalized yet.

Before writing the protocol, we want to study existing solutions and understand what they do well and where there may be room for improvement.

If we find that an existing protocol already solves the problem well, there may be no reason to create OpenLink.

## Contributing

At this stage, ideas and discussions are more useful than code.

You can help by:

* Sharing use cases
* Pointing out existing solutions
* Comparing existing protocols
* Suggesting ideas
* Finding problems with our approach
* Sharing your experience with networking and embedded devices

Feel free to open an issue or start a discussion.

## License

The project is experimental. The license will be decided as the project develops.
