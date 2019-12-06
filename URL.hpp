#pragma once

class URL {
public:
  URL(uint16_t L, std::string, URL_TYPE);
  ~URL() = default;

  const char *getAddress();
  void print();

private:
  uint16_t level;
  std::string address;
  URL_TYPE type;
};
