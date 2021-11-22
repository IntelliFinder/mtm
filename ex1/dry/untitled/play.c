#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* stringDuplicator(char* s, int times);


int main() {
    char* s = "H";
    int times = 3;
    char* out = stringDuplicator( s, times );
    puts( out );
    free( out );

    /*char* str1="Sample string";
    char* str2= malloc( 40 );
    assert(str2);
    printf("Address of str2 = %p\n",  str2  );
    char* str3= malloc( 40 );
    assert(str3);
    strcpy (str2,str1);
    puts( str2 );
    str2 = str2 + strlen( str1 );
    printf("Address of str2 = %p\n",  str2  );
    strcpy (str2,str1);
    str2 -= strlen(str1);
    printf("Address of str2 = %p\n",  str2  );
    strcpy (str3,"copy successful");
    printf ("str1: %s\nstr2: %s\nstr3: %s\n",str1,str2,str3);
    free(str1);
    free(str2);
    free(str3);*/

    return 0;

}

char* stringDuplicator(char* s, int times) {
    assert(s);
    assert(times > 0);
    int LEN = strlen(s);
    char* out = malloc(LEN*times );
    assert(out);
    for (int i = 0; i < times; i++){
        out+=LEN;
        //printf("Address of out = %p\n",  out  );
        //puts( out );
        strcat(out, s);
    }
    out -= (times-1)*strlen(s);

    return out;
}
