#include "Site.hpp"
#include "URL.hpp"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

const char *Site::getURL() { return url.getAddress(); }

void Site::search_for_inner_urls() {
  /*std::cout << "\n!!!!!!!!!!!!!!!!!!\n";

  std::string str = "https://www.discogs.com";
  std::cmatch res;
  std::regex rx("(https)");

  if (std::regex_match(data.c_str(), res, rx))
          std::cout << "true\n";

  for (size_t i = 0; i < res.size(); ++i) {
          std::cout << i << ": " << res[i] << std::endl;
  }*/
}