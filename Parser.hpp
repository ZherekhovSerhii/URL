#pragma once

class Parser {
public:
  Parser() = default;
  ~Parser();

  CURL *curl = nullptr;
  CURLcode code;
  std::string data;

  void init(std::string url);
  void load(std::string url);
  void parsing();

private:
  enum class URL_TYPE { HTTP, HTTPS, NO };

  std::vector<std::string> https_storage;
  std::vector<std::string> http_storage;
  std::vector<std::string> loaded_storage;
};
