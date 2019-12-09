#pragma once

class Parser {
public:
  Parser() = default;
  ~Parser() = default;

  std::string data;
  void parsing();

private:
  enum class URL_TYPE { HTTP, HTTPS, NO };

  std::vector<std::string> http_storage;
  std::vector<std::string> https_storage;
};
