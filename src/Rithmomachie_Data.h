
/*
 *    RITHMOMACHIE - Created by Anderson5091 30/mars/17.
 *
 *    .
 */

#ifndef R_DATA_H
#define R_DATA_H

typedef enum{
    Cercle,
    Triangle,
    Carre,
    Pyramide
} P_TYPE;

typedef enum{
    P_Blanc,
    P_Noir
} P_COLOR;

typedef struct PIECE
{
    P_TYPE Type;
    P_COLOR Color;
     Image;
}PIECE;

typedef struct CASE
{
    PIECE Piece;
    Background;
}CASE;

typedef struct ACTIVITE
{
    int (*Id)(void);
    int (*Init)(void);
    int (*Detruire)(void);
    int (*Actualiser)(void);
    void (*Afficher)(void);
}ACTIVITE;

#endif //R_DATA_H

