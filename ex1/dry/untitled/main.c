#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* stringDuplicator(char* s, int times);

int main() {
    char* s = "Hello";
    int times = 3;
    char* out = stringDuplicator(s,times);
    puts( out );
    free( out );
    return 0;
}

char* stringDuplicator(char* s, int times) {
    assert(s);
    assert(times > 0);
    int LEN = strlen(s);
    char* out = malloc( LEN * times );
    assert(out);
    char* back = out;
    for (int i = 0; i < times; i++){
        out = out + LEN;
        strcpy(out, s);
    }
    return back;
}
