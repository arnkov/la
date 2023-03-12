#include <glad/glad.h>
#include <stdbool.h>

void laSetupTexture(GLuint* texture);
void laDeleteTexture(GLuint* texture);
void laTexFromImage(GLuint* texture, const char* path, int format, bool flip);
void laBindTexture(GLuint* texture, int slot);
void laUnbindTexture();
