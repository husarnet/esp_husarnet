# Husarnet for ESP-IDF

![Husarnet logo](images/logo.svg)

Husarnet is a Peer-to-Peer VPN to connect your laptops, servers and microcontrollers over the Internet with zero configuration.

This library provides both C and C++ API. More information is available in the [API documentation](https://husarnet.com/docs/library-api/).

For a quick start with Husarnet Client, take a look at the webserver example in the `examples` directory or run:
```
idf.py create-project-from-example "husarnet/esp_husarnet:husarnet-web-server"
```

Also see the [Dashboard Guide](https://husarnet.com/docs/dashboard-manual/) for more information on how to enroll and control your device.

-------------

For more generic information please have a look at the [Husarnet Docs](https://husarnet.com/docs/).

Typical issues preventing Peer-to-Peer connection (thus enjoing a low-latency) and their workarounds are described in the [Troubleshooting Guide](https://husarnet.com/docs/troubleshooting-guide/).

If you need help and/or have questions regarding Husarnet, feel welcome to post on [Husarnet Community Forums](https://community.husarnet.com). Please, do not use GitHub Issues in this repository for reporting general usage problems and requests. Use the Issues only for technical questions and concerns regarding Husarnet Client building and development.

## Features

- **Low Latency** - thanks to Peer-to-Peer connection between devices. After establishing a connection, Husarnet infrastructure (Husarnet Base Servers) is used only as a failover proxy if P2P connection is not possible.
- **Zero Configuration** - after installing Husarnet Client, you can add new devices to a group with a single command `husarnet join <YOUR_JOINCODE> mydevname` on Linux. See [the docs](https://husarnet.com/docs) for other platforms.
- **Low Reconfiguration Time** - in case of a network topology change (eg. transition between two Wi-Fi hotspots), Husarnet needs usually 1 - 3 seconds to reestablish Peer-to-Peer connection.
- **Lightweight** - it works not only on popular OSes (currently only Windows and Linux version is released, MacOS, Android coming soon) but even on ESP32 microcontrollers. That means you can P2P access your things without IoT server at all!
- **Secure & Private** - packets never leave connected devices unencrypted, Perfect Forward Secrecy (PFC) enabled by default.

Husarnet, in it's core, is **one big, automatically routed, IPv6 network**. Running Husarnet daemon creates a virtual network interface (by default named `hnet0`) with an unique Husarnet IPv6 address and associated `fc94::/16` route. If you choose to disable the permission system, any node can reach your node using IPv6 `fc94:...` address, but if you choose to leave it enabled, we've prepared an extensive permissions system for you. You can have multiple virtual islands/groups, your devices can access multiple groups or you can even share access to those groups with other users!

The nodes are identified by their 112-bit **IPv6 addresses, that are based on the public keys of the node**. All connections are also authenticated by the IPv6 address. This property makes it possible to establish connection authenticity without any trusted third party, basing only on the IPv6 address! The connections are also always encrypted.

**Cryptography:** Husarnet uses X25519 from libsodium for key exchange, with ephemeral Curve25519 keys for forward secrecy. The hash of initial public key is validated to match the IPv6 address. The packets are encrypted using libsodium's ChaCha20-Poly1305 secretbox construction with a random 192-bit nonce.

**Runtime safety:** Husarnet is written in C++ using modern memory-safe constructs.

**Husarnet Dashboard:** Husarnet Dashboard is a web application that allows users to fully configure how they use Husarnet, including adding and removing networks, adding and removing devices, associationg devices with networks and more.

## License

Husarnet is dual-licensed:

- **GNU Public License** - for derivative projects - eg. exposing a generic VPN functionality.
- **Mozilla Public License** - for projects where you link Husarnet Client code with different project type than mentioned above - eg. using Husarnet Client SDK in ESP32 IoT project.

See LICENSE.txt for details.
