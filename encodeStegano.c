/**
 *
 * @file encodeStegano.c
 *
 * @brief This file represents the -encodeStegano function of the program.
 *
 * @author Christos Kasoulides
 * @version 1.0
 * @since 20/11/20
 *
 */

#include "encodeStegano.h"
#include <stdlib.h>
#include <stdio.h>


static int checkImageCompatibility(IMAGE *x, IMAGE *y) {
    if ((x->iheader->biHeight != y->iheader->biHeight) || (x->iheader->biWidth != y->iheader->biWidth))
        return EXIT_FAILURE;


    return EXIT_SUCCESS;
}

static byte getBitMask(int noOfBits){
    switch (noOfBits){

        case 1:
            return 0b10000000;

        case 3:
            return 0b11100000;

        case 4:
            return 0b11110000;


        default:
        printf("\nThe number of bits entered is not within the limit of bits that can be encoded!\n");
        exit(EXIT_FAILURE);
    }
}

void encodeStegano(int noOfbits, IMAGE *cover, IMAGE *secret) {


    if (checkImageCompatibility(cover, secret) == EXIT_FAILURE) {
        printf("\nGiven images are not compatible!\n");
        exit(EXIT_FAILURE);

    }
    int cnt = 0;
    byte copy = getBitMask(noOfbits);

    for (int i = 0; i < cover->iheader->biHeight; i++) {

        for (int j = 0; j < cover->iheader->biWidth; j++) {

            byte maskR = ((secret->data[cnt].r) & copy) >> (8-noOfbits);
            byte maskG = ((secret->data[cnt].g) & copy) >> (8-noOfbits);
            byte maskB = ((secret->data[cnt].b) & copy) >> (8-noOfbits);

            (cover->data[cnt].r) = (((cover->data[cnt].r) >> noOfbits ) << noOfbits)  | maskR;
            (cover->data[cnt].g) = (((cover->data[cnt].g) >> noOfbits ) << noOfbits)  | maskG;
            (cover->data[cnt].b) = (((cover->data[cnt].b) >> noOfbits ) << noOfbits)  | maskB;

            cnt++;
        }

    }



}

#ifdef DEBUGES
int main(int argc, char **argv) {


    int noOfBits = atoi(argv[1]);


    char *coverImageName = argv[2];
    IMAGE *coverImage = readImage(coverImageName);

    char *secretImageName = argv[3];
    IMAGE *secretImage = readImage(secretImageName);

    encodeStegano(noOfBits, coverImage, secretImage);

    saveImage(coverImage, "new-IMG_6865.bmp");

    printf("\nFinished encoding\n");

    return 0;

}
#endif

