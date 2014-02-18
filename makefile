all: install

install: gcc httpclient_curl.c -L/opt/boxen/homebrew/Cellar/json-c/0.11/lib -ljson -I/opt/boxen/homebrew/Cellar/json-c/0.11/include/json-c -o json-client
  #./json-client
