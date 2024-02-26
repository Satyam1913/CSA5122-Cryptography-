#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#include <openssl/MD5.h>
#endif

char *str2md5(const char *str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[MD5_DIGEST_LENGTH];
    char *out = (char*)malloc(33); // 32 characters + null terminator

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < MD5_DIGEST_LENGTH; ++n) {
        snprintf(&(out[n*2]), 3, "%02x", (unsigned int)digest[n]);
    }
    out[32] = '\0'; // null-terminate the string

    return out;
}

int main(int argc, char **argv) {
    char *output = str2md5("hello", strlen("hello"));
    printf("%s\n", output);
    free(output);
    return 0;
}

