#include <string.h>
#include <emscripten/emscripten.h>

int EMSCRIPTEN_KEEPALIVE getLen(char* str) {
  
  size_t len = strlen(str);

  return len;
}
