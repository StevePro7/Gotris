#ifndef GOTRIS_GLOBALDEFINITIONS_H_H
#define GOTRIS_GLOBALDEFINITIONS_H_H
#define MAX_PIECES_ACTIVE 10

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char color;
} piece;

typedef struct {
    unsigned char x;
    unsigned char y;
    unsigned char color00;
    unsigned char color01;
    unsigned char color10;
    unsigned char color11;
} square;
#endif //GOTRIS_GLOBALDEFINITIONS_H_H