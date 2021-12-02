#include <iostream>

#include "kissnet.hpp"
namespace kn = kissnet;

int main() {
  // setup socket
  kn::socket<kissnet::protocol::tcp> server(kn::endpoint("0.0.0.0:3000"));
  server.bind();
  server.listen();

  while (true) {
    auto client = server.accept();

    // Read once in a 1k buffer
    kn::buffer<1024> buff;
    const auto [size, status] = client.recv(buff);

    // Add null terminator, and print as string
    if (size < buff.size()) {
      buff[size] = std::byte{0};
    }

    auto buff_ch = reinterpret_cast<const char *>(buff.data());
    std::cout << buff_ch << '\n';

    // Add some exclamation marks and send a response
    std::string response = std::string(buff_ch) + "!!!";

    client.send(reinterpret_cast<const std::byte *>(response.c_str()),
                response.size());
  }

  return 0;
}