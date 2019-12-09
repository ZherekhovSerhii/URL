#include <iostream>
#include <regex>
#include <string>
#include <vector>

//#include"ConsoleColor.h"
#include "Parser.hpp"

void Parser::parsing() {

  std::smatch m;
  std::regex e(R"((http:\/\/|https:\/\/){1}.[^\" ]*)");

  while (std::regex_search(data, m, e)) {
    const char *begin = m[1].str().c_str();

    if (*(begin + 4) == 's') {
      https_storage.emplace_back(std::move(std::string(m[0])));
      std::cout /*<< green*/ << m[0] /*<< white*/ << std::endl;
    }
    if (*(begin + 4) == ':') {
      http_storage.emplace_back(std::move(std::string(m[0])));
      std::cout /*<< red*/ << m[0] /*<< white*/ << std::endl;
    }
    data = m.suffix().str();
  }
}