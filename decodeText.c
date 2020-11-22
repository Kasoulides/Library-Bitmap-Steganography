//
// Created by leoni on 22/11/2020.
//

#include "decodeText.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*static byte getBit(char *m, int n) {
    byte u;

    if (n <= 8 * strlen(m)) {
        u = (*(m + n / 8) & (0x1 << (7 - (n % 8)))) >> (7 - (n % 8));
        return u;
    } else
        return 0;

}*/

static int *createPermutationFunction(int N, unsigned int systemkey) {

    srand(systemkey);

    int *permutation = (int *)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) { //initializing permutation
        permutation[i] = i;
    }

    for (int k = 0; k < N; k++) { //mixing up permutation
        int i = abs(rand() % N);
        int j = abs(rand() % N);

        int temp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = temp;


    }

    return permutation;
}

char* decodeText(IMAGE* image, int msLength, unsigned int systemkey){
    char* text=(char*)calloc(msLength+1,sizeof(char));
    int o = 0;
    int countBits=0;
    byte b='\0';
    for (int i = 0; i < (1 + msLength) * 8; i++) {
        o = (createPermutationFunction(msLength+1, systemkey)[i/8]);

        switch (o % 3) {
            case 0:
                b |= (image->data[o / 3].r & 0x1);
                b<<=1;
                countBits++;
                break;
            case 1:
                b |= (image->data[o / 3].g & 0x1);
                b<<=1;
                countBits++;
                break;
            default:
                b |= (image->data[o / 3].b & 0x1);
                b<<=1;
                countBits++;
                break;
        }
        if(countBits==8){
            countBits=0;
            strcat(text,&b);
        }
    }
    return text;
}

//#ifdef DEBUGDT
int main(int argc, char **argv) {
    IMAGE *i = readImage(argv[1]);
    int msLength=atoi(argv[2]);
    int systemkey = 123;
    char *text = decodeText(i,msLength,systemkey);
    printf("%s",text);
    return 0;
}
//#endif