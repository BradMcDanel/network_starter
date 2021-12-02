#include <iostream>

#include "kissnet.hpp"
namespace kn = kissnet;

int main(int argc, char **argv) {
  // Create a kissnet tcp ipv4 socket
  kn::tcp_socket a_socket(kn::endpoint("0.0.0.0:3000"));
  a_socket.connect();

  auto get_index_request = std::string{"Hello World"};

  // Send request
  a_socket.send(reinterpret_cast<const std::byte *>(get_index_request.c_str()),
                get_index_request.size());

  // Receive data into a buffer
  kn::buffer<4096> static_buffer;

  // Print how much data our OS has for us
  std::cout << "bytes available to read : " << a_socket.bytes_available()
            << '\n';

  // Get the data, and the lengh of data
  const auto [data_size, status_code] = a_socket.recv(static_buffer);

  // To print it as a good old C string, add a null terminator
  if (data_size < static_buffer.size()) {
    static_buffer[data_size] = std::byte{'\0'};
  }

  // Print the raw data as text into the terminal (should display html/css code
  // here)
  std::cout << reinterpret_cast<const char *>(static_buffer.data()) << '\n';

  return 0;
}
