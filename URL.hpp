#pragma once

class URL {
public:
  URL(uint16_t L = 0, std::string A = "", bool S = false)
      : level(L), address(A), safe(S) {}

  ~URL() {}

  const char *getAddress();

private:
  uint16_t level;
  std::string address;
  bool safe;
};