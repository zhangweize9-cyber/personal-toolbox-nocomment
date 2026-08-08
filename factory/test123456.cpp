#include <iostream>

static int count = 0;

void helloworld(std::string first) { std::cout << "Hi!" << first << std::endl; }

int main() {
  std::cout << "Hello World!" << std::endl;
  helloworld("test passed");
}
