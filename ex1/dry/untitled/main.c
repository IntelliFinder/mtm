#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* stringDuplicator(const char* s,const int times);

int main() {
    char* s = "Hello";
    int times = 3;
    char* out = stringDuplicator(s,times);
    puts( out );
    free( out );
    return 0;
}

char* stringDuplicator(const char* s,const int times) {
    if(s == NULL){
		return NULL;
	}
    assert(times > 0);
    int length = strlen(s);
    char* out = malloc( ((length * times) + 1) * sizeof(char));
    if(out == NULL){
		return NULL;
	}
    char* back = out;
    for (int i = 0; i < times; i++){
        out = out + length;
        strcpy(out, s);
    }
    return back;
}
