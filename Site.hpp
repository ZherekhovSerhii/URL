#pragma once

class Site {
public:
  Site(URL U, std::string D = "") : url(U), data(D) {}

  ~Site() {
    for (URL *url : storage) {
      url->~URL();
      delete url;
    }
  }

  const char *getURL();

  void search_for_inner_urls();

  std::string data;

private:
  URL url;
  std::vector<URL *> storage;
};
