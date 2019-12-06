#pragma once

class Site {
public:
  Site(URL);
  ~Site();

  const char *getURL();

  void search_for_inner_urls();
  void print_inner_urls();

  std::string data;

private:
  URL_TYPE check_url_type(const char *);
  const char *search_for_end_of_url(const char *);
  void parcing(const char *);

  URL url;
  std::vector<URL *> storage;
};
