//
//  main.c
//  ChiBingo
//
//  Created by Randy Ekl on 4/25/19.
//  UPDATED for Protospiel Chicago 2021 on August 5, 2021
//  Copyright © 2019-2021 Clever Playing Cards and Randy L. Ekl. All rights reserved.
//
//  UPDATED for Protospiel Madison 2021 on Nov 16, 2021
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NumberOfCards 250

int noMechanics = 13;
int sectionsPerMechanism[50] =
{
    2,2,1,1,2,2,1,2,2,2,2,2,2
};

char mechanics[50][5][30] =             // 50 mechanisms, 5 sections per mechanism, 30 characters per section
{
    {"Worker","Placement"},
    {"Card / Dice","Drafting"},
    {"Area Control"},
    {"Trick-Trump"},
    {"Simultaneous","Action"},
    {"Pick Up &","Deliver"},
    {"Roll & Write"},
    {"Action","Selection"},
    {"Social", "Deduction"},
    {"Set", "Collection"},
    {"Unique", "Mechanic"},
    {"Press your", "Luck"},
    {"Auction /", "Bidding"}
};

int noThemes = 14;
int sectionsPerTheme[50] =
{
    1,1,1,1,1, 1,1,1,1,1, 1,1,2,2
};

char themes[50][5][30] =
{
    {"War Game"},
    {"Abstract"},
    {"Animals"},
    {"Space"},
    {"Aliens"},
    
    {"Zombies"},
    {"Historical"},
    {"Nautical"},
    {"Educational"},
    {"Trains"},
    
    {"Fantasy"},
    {"Economics"},
    {"Unique", "Theme"},
    {"Location-", "based"}
};

int noStyles = 8;
int sectionsPerStyle[50] =
{
    1,1,1,1,2, 2,1,1
};
char styles[50][5][30] =
{
    {"Cooperative"},
    {"Party"},
    {"Dexterity"},
    {"Take That"},
    {"Light /","Filler"},
    
    {"Heavy /","Complex"},
    {"Trivia"},
    {"Euro"}
};

int noComponents = 15;
int sectionsPerComponent[50] =
{
    1,1,1,2,2, 2,1,2,2,2, 1,2,2,2,1
};

char components[50][5][30] =
{
    {"Dice"},
    {"Cards"},
    {"Cubes"},
    {"(Actual)","Meeples"},
    {"Acrylic","Pieces"},
    
    {"Homemade","Pieces"},
    {"Tiles"},
    {"Wooden","Pieces"},
    {"Player","Mat"},
    {"Reference","Card"},
    
    {"Score Track"},
    {"Color Blind","Friendly"},
    {"Unique","Component"},
    {"Standees /","Pawns"},
    {"Game Board"}
};

int noDesChar = 3;
int sectionsPerDesChar[50] =
{
    2,2,2
};

char desChar[50][5][30] =
{
    {"New-to-you","Designer"},
    {"In-State","Designer"},
    {"Out-of-State","Designer"}
};

int noPlayers = 5;
char playerCounts[50][30] =
{
    "Solo",
    "2 Players",
    "3 Players",
    "4 Players",
    "5+ Players"
};


int main(int argc, const char * argv[]) {
    
    int noPages, card=0;          // card goes from 0 to 1, inclusive = two cards per page
    int a, b, c, d, e;
    int i, j, k;                      // generic counter
    int cards[5][5];                 // keeps track of which cells are filled in. 0=free, 1=full
    
    int used[100];
    int diag1, diag2;               // count the number of Any Game on each of the diagonals
    
    int open = 0;
    
    FILE * fout;
    
    printf("Hello, World!\n\n");
    
    srand(21);          // increased to 21 on Sept 2, 2021
    
    
    
    noPages = (NumberOfCards+1)/2;
    
    // Open File
    //fout = fopen("///Users/randy/Desktop/Mad-Bingo2021.ps", "w");
    fout = fopen("Mad-Bingo2021.ps", "w");
    
    // Put top matter in file
    fprintf(fout, "%%!PS-Adobe-2.0\n");
    
    fprintf(fout, "%%%%BoundingBox: 0 0 1600 1600\n");
    fprintf(fout, "%%%%Pages: %i\n", noPages);
    fprintf(fout, "%%%%EndComments\n");
    
    
    
    fprintf(fout, "/$F2psDict 200 dict def\n");
    fprintf(fout, "$F2psDict begin\n");
    fprintf(fout, "$F2psDict /mtrx matrix put\n");
    fprintf(fout, "/l {lineto} bind def\n");
    fprintf(fout, "/m {moveto} bind def\n");
    fprintf(fout, "/s {stroke} bind def\n");
    fprintf(fout, "/n {newpath} bind def\n");
    fprintf(fout, "/gs {gsave} bind def\n");
    fprintf(fout, "/gr {grestore} bind def\n");
    fprintf(fout, "/clp {closepath} bind def\n");
    fprintf(fout, "/graycol {dup dup currentrgbcolor 4 -2 roll mul 4 -2 roll mul\n");
    fprintf(fout, "    4 -2 roll mul setrgbcolor} bind def\n");
    fprintf(fout, "/col-1 {} def\n");
    fprintf(fout, "/col0 {0 0 0 setrgbcolor} bind def\n");              // black - Designer Characteristic
    fprintf(fout, "/col1 {0 0 1 setrgbcolor} bind def\n");              // blue - Mechanic
    fprintf(fout, "/col5 {0 .7 0 setrgbcolor} bind def\n");              // green - Number of Players
    fprintf(fout, "/col3 {1 0 0 setrgbcolor} bind def\n");              // Red - Component
    fprintf(fout, "/col4 {.6596 .3618 .7133  setrgbcolor} bind def\n"); // Purple - Theme
    fprintf(fout, "/col7 {.9372 .3921 .8470 setrgbcolor} bind def\n");  // Pink - Component
    fprintf(fout, "/col6 {1 1 0 setrgbcolor} bind def\n");              // yellow - not used
    fprintf(fout, "/col2 {.9176 .6274 .0 setrgbcolor} bind def\n");     // Orange = Designer Name
    fprintf(fout, "/col8 {.6275 .3215 .1765 setrgbcolor} bind def\n");  // brown (sienna) rgb(160,82,45) - Style
    fprintf(fout, "/col9 {.7 .7 .7 setrgbcolor} bind def\n");           // gray - Wild Prototype
    fprintf(fout, "    end\n");
    fprintf(fout, "/$F2psBegin {$F2psDict begin /$F2psEnteredState save def} def\n");
    fprintf(fout, "/$F2psEnd {$F2psEnteredState restore end} def\n");
    fprintf(fout, "%%%%EndProlog\n");
    
    fprintf(fout, "$F2psBegin\n");
    fprintf(fout, "0 setlinecap 0 setlinejoin\n");
    fprintf(fout, "0.96 0.96 scale\n");
    fprintf(fout, "0 16  translate\n");
    fprintf(fout, "1.00 setlinewidth\n");
    
    
    fprintf(fout, "%% Polyline\n");
    fprintf(fout, "/Avenir-Black findfont 18 scalefont setfont newpath 60 %i m 90 rotate () true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+90);               // this is setting the color back to be black
    
    
    /*
     for ( i=0; i<101; i++)      // horizontal lines
    {
        fprintf(fout, "%f setlinewidth\n", ((float)(i%10+1))/10.0   );
        fprintf(fout, "%% Polyline\n");
        fprintf(fout, "0 %i m 612 %i l col1 %f setlinewidth s gs gr\n", 8*i, 8*i, ((float)(i%10+1))/10.0 );     // this is a line
        fprintf(fout, "%f setlinewidth\n", ((float)(i%10+1))/10.0   );
        fprintf(fout, "%% Polyline\n");
        
    }
    
    for ( i=0; i<101; i++)      // vertical lines
    {
        fprintf(fout, "%f 0 m %f 800 l col1 %f setlinewidth s gs gr\n", 6.12*(float)i, 6.12*(float)i, ((float)(i%10+1))/10.0 ) ;     // this is a line
    }
     */
    
    for ( noPages=0; noPages<(NumberOfCards+1)/2; noPages++ )       // odd number of cards produces one extra; i.e. round up
    {
  
        for ( card=0; card<2; card++)
        {
            printf("\nStarting new card\n");
            // put card info in file
            
            fprintf(fout, "%% Polyline\n");
            fprintf(fout, "/Avenir-Black findfont 18 scalefont setfont newpath 60 %i m 90 rotate () true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+90);               // this is setting the color back to be black
            
            fprintf(fout, "120 %i m 120 %i l gs col-1 s gr\n", card*396+10, card*396+385);     // this is a line
            fprintf(fout, "195 %i m 195 %i l gs col-1 s gr\n", card*396+10, card*396+385);     // this is a line
            fprintf(fout, "270 %i m 270 %i l gs col-1 s gr\n", card*396+10, card*396+385);     // this is a line
            fprintf(fout, "345 %i m 345 %i l gs col-1 s gr\n", card*396+10, card*396+385);     // this is a line
            fprintf(fout, "420 %i m 420 %i l gs col-1 s gr\n", card*396+10, card*396+385);     // this is a line
            fprintf(fout, "495 %i m 495 %i l gs col-1 s gr\n", card*396+10, card*396+385);     // this is a line
            
            fprintf(fout, "120 %i m 495 %i l gs col-1 s gr\n", card*396+ 10, card*396+ 10);     // this is a line
            fprintf(fout, "120 %i m 495 %i l gs col-1 s gr\n", card*396+ 85, card*396+ 85);     // this is a line
            fprintf(fout, "120 %i m 495 %i l gs col-1 s gr\n", card*396+160, card*396+160);     // this is a line
            fprintf(fout, "120 %i m 495 %i l gs col-1 s gr\n", card*396+235, card*396+235);     // this is a line
            fprintf(fout, "120 %i m 495 %i l gs col-1 s gr\n", card*396+310, card*396+310);     // this is a line
            fprintf(fout, "120 %i m 495 %i l gs col-1 s gr\n", card*396+385, card*396+385);     // this is a line
            
            
            fprintf(fout, "/Avenir-Black findfont 24 scalefont setfont newpath 60 %i m 90 rotate (Protospiel Mad-Bingo) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+81);               // this is some text
            
            fprintf(fout, "/Avenir-BlackOblique findfont 14 scalefont setfont newpath 30 %i m 90 rotate (2021) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+340);               // this is some text
            
            fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath 80 %i m 90 rotate (Your Name: __________________) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+20);               // this is some text
            fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath 80 %i m 90 rotate (Badge Number: _______) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+230);               // this is some text
            
            fprintf(fout, "/Avenir-Oblique findfont 11 scalefont setfont newpath 100 %i m 90 rotate (Play games, fill in squares, get 5 in a row to WIN!) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+80);               // this is some text
            
            fprintf(fout, "/Avenir-Roman findfont 9 scalefont setfont newpath 520 %i m 90 rotate (For each game you play test for a designer (not you) that matches a square on this) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+15);
            fprintf(fout, "/Avenir-Roman findfont 9 scalefont setfont newpath 530 %i m 90 rotate (Mad-Bingo sheet in) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+15);
            
             fprintf(fout, "/Avenir-Black findfont 9 scalefont setfont newpath 530 %i m 90 rotate (Theme,) true charpath col4 1.0 setlinewidth fill -90 rotate \n", 396*card+96);
             fprintf(fout, "/Avenir-Black findfont 9 scalefont setfont newpath 530 %i m 90 rotate (Mechanic,) true charpath col1 1.0 setlinewidth fill -90 rotate \n", 396*card+129);
             fprintf(fout, "/Avenir-Black findfont 9 scalefont setfont newpath 530 %i m 90 rotate (Genre,) true charpath col8 1.0 setlinewidth fill -90 rotate \n", 396*card+173);
             fprintf(fout, "/Avenir-Black findfont 9 scalefont setfont newpath 530 %i m 90 rotate (Designer Characteristic,) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+203);
             fprintf(fout, "/Avenir-Black findfont 9 scalefont setfont newpath 530 %i m 90 rotate (Component,) true charpath col3 1.0 setlinewidth fill -90 rotate \n", 396*card+306);
            fprintf(fout, "/Avenir-Roman findfont 9 scalefont setfont newpath 530 %i m 90 rotate (or) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+359);
            
             fprintf(fout, "/Avenir-Black findfont 9 scalefont setfont newpath 540 %i m 90 rotate (Player Count,) true charpath col2 1.0 setlinewidth fill -90 rotate \n", 396*card+15);
            fprintf(fout, "/Avenir-Roman findfont 9 scalefont setfont newpath 540 %i m 90 rotate (fill in the game name [GN] and have the designer initial [DI] it.) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+74);
            
            fprintf(fout, "/Avenir-BlackOblique findfont 9 scalefont setfont newpath 560 %i m 90 rotate (** Each game may only be used once even though it may satisfy multiple squares. **) true charpath col1 1.0 setlinewidth fill -90 rotate \n", 396*card+15);
            
            fprintf(fout, "/Avenir-BlackOblique findfont 9 scalefont setfont newpath 572 %i m 90 rotate (** Designers can NOT fill in their own game. **) true charpath col1 1.0 setlinewidth fill -90 rotate \n", 396*card+15);
            
            fprintf(fout, "/Avenir-BlackOblique findfont 9 scalefont setfont newpath 584 %i m 90 rotate (** Limit one prize per player. **) true charpath col1 1.0 setlinewidth fill -90 rotate \n", 396*card+15);
            
            fprintf(fout, "/Avenir-Oblique findfont 9 scalefont setfont newpath 596 %i m 90 rotate ((c) Copyright Clever Playing Cards - 2019-2021) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 396*card+20);
            
            
                    
            
            //////////////// ///////// ///// // clear out card
            for (i=0; i<5; i++)
                for (j=0; j<5; j++)
                    cards[i][j] = 0;        // nothing in any of the squares
            
            // Fill in "Free" spaces first, i.e. "ANY Prototype"
            a = rand()%3+1;     // 1, 2 or 3 (first column is 0)
            e = (((a + rand()%2+1)-1)%3)+1;     // 1, 2, or 3, but not what a was, above
            c = rand()%5;
            while (c==2 || c==a || c==e )
                c = rand()%5;
            b = rand()%5;
            while (b==a || b==c || b==e)
                b = rand()%5;
            d = rand()%5;
            while (d==a || d==b || d==c || d==e)
                d = rand()%5;
            
            //printf("%i, %i, %i, %i, %i\n", a, b, c, d, e);
            
            cards[0][a] = 1;            // mark the square as full
            fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (ANY Game) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 133, 396*card+13+75*a);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 154, 396*card+13+75*a);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 190, 396*card+13+75*a);
        
            cards[1][b] = 1;
            fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (ANY Game) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 133+75, 396*card+13+75*b);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 154+75, 396*card+13+75*b);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 190+75, 396*card+13+75*b);
        
            cards[2][c] = 1;
            fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (ANY Game) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 133+2*75, 396*card+13+75*c);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 154+2*75, 396*card+13+75*c);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 190+2*75, 396*card+13+75*c);
        
            cards[3][d] = 1;
            fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (ANY Game) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 133+3*75, 396*card+13+75*d);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 154+3*75, 396*card+13+75*d);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 190+3*75, 396*card+13+75*d);
        
            cards[4][e] = 1;
            fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (ANY Game) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 133+4*75, 396*card+13+75*e);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 154+4*75, 396*card+13+75*e);
            fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col5 1.0 setlinewidth fill -90 rotate \n", 190+4*75, 396*card+13+75*e);
            
            
            // How many are on one diagonal? How many are on the other diagonal?
            diag1 = cards[0][0] + cards[1][1] + cards[2][2] + cards[3][3] + cards[4][4];
            diag2 = cards[0][4] + cards[1][3] + cards[2][2] + cards[3][1] + cards[4][0];
            if ( diag1 > 1 || diag2 > 1 )
                printf("Number of ANY GAME on the diagonals: %i & %i !!!!!!\n", diag1, diag2);
            
           
                    
            open = 0;       // count how many open cells are on the card
            for (i=0; i<25; i++)
                if ( cards[i/5][i%5] > 0 )
                    open++;
            printf("1: Used Squares is %i\n", open);
            
            open = 0;       // count how many open cells are on the card
            for (i=0; i<25; i++)
                if ( cards[i/5][i%5] > 0 )
                    open++;
            printf("2: Used Squares is %i\n", open);
            
            // Pick 3 DIFFERENT themes
            for (i=0; i<50; i++)
                used[i] = 0;
            for (i=0; i<3; i++)
            {
                a = rand()%noThemes;                // this picked the theme
                while ( used[a] > 0 )
                    a = rand()%noThemes;
                used[a] = 1;
                // and decide which square to put it in!
                j = rand()%25;                      // this is the cell to put it in
                while ( cards[j/5][j%5] > 0 )       // keep looking for an open cell
                    j = rand()%25;
                cards[j/5][j%5] = 1;
                for (k=0; k<sectionsPerTheme[a]; k++)     // this many sections for the game name
                {
                    fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (%s) true charpath col4 1.0 setlinewidth fill -90 rotate \n", 133+(j/5)*75+11*k, 396*card+13+75*(j%5), themes[a][k]);
                }
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col4 1.0 setlinewidth fill -90 rotate \n", 154+(j/5)*75, 396*card+13+75*(j%5));
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col4 1.0 setlinewidth fill -90 rotate \n", 190+(j/5)*75, 396*card+13+75*(j%5));
            }
            printf("Did the Themes\n");
            
            // Pick 4 DIFFERENT mechanics, out of "noMechanics"
            for (i=0; i<50; i++)
                used[i] = 0;
            for (i=0; i<4; i++)
            {
                a = rand()%noMechanics;     // this picked the mechanic
                while ( used[a] > 0 )
                    a = rand()%noMechanics;
                used[a] = 1;
                // and decide which square to put it in!
                j = rand()%25;              // this is the cell to put it in
                while ( cards[j/5][j%5] > 0 )      // keep looking for an open cell
                    j = rand()%25;
                cards[j/5][j%5] = 1;
                for (k=0; k<sectionsPerMechanism[a]; k++)
                {
                    fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (%s) true charpath col1 1.0 setlinewidth fill -90 rotate \n", 133+(j/5)*75+11*k, 396*card+13+75*(j%5), mechanics[a][k]);
                }
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col1 1.0 setlinewidth fill -90 rotate \n", 154+(j/5)*75, 396*card+13+75*(j%5));
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col1 1.0 setlinewidth fill -90 rotate \n", 190+(j/5)*75, 396*card+13+75*(j%5));
            }
            printf("Did the Mechanics\n");
            
            // Pick 4 DIFFERENT Styles
            for (i=0; i<50; i++)
                used[i] = 0;
            for (i=0; i<4; i++)
            {
                a = rand()%noStyles;     // this picked the styles
                while ( used[a] > 0 )
                    a = rand()%noStyles;
                used[a] = 1;
                // and decide which square to put it in!
                j = rand()%25;              // this is the cell to put it in
                while ( cards[j/5][j%5] > 0 )      // keep looking for an open cell
                    j = rand()%25;
                cards[j/5][j%5] = 1;
                
                for (k=0; k<sectionsPerMechanism[a]; k++)
                {
                    fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (%s) true charpath col8 1.0 setlinewidth fill -90 rotate \n", 133+(j/5)*75+11*k, 396*card+13+75*(j%5), styles[a][k]);
                }
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col8 1.0 setlinewidth fill -90 rotate \n", 154+(j/5)*75, 396*card+13+75*(j%5));
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col8 1.0 setlinewidth fill -90 rotate \n", 190+(j/5)*75, 396*card+13+75*(j%5));
            }
            printf("Did the Sytles\n");
            
            // Pick 4 DIFFERENT components
            for (i=0; i<50; i++)
                used[i] = 0;
            for (i=0; i<4; i++)
            {
                a = rand()%noComponents;            // this picked the components
                while ( used[a] > 0 )
                    a = rand()%noComponents;
                used[a] = 1;
                // and decide which square to put it in!
                j = rand()%25;                      // this is the cell to put it in
                while ( cards[j/5][j%5] > 0 )      // keep looking for an open cell
                    j = rand()%25;
                cards[j/5][j%5] = 1;
                for (k=0; k<sectionsPerComponent[a]; k++)
                {
                    fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (%s) true charpath col3 1.0 setlinewidth fill -90 rotate \n", 133+(j/5)*75+11*k, 396*card+13+75*(j%5), components[a][k]);
                }
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col3 1.0 setlinewidth fill -90 rotate \n", 154+(j/5)*75, 396*card+13+75*(j%5));
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col3 1.0 setlinewidth fill -90 rotate \n", 190+(j/5)*75, 396*card+13+75*(j%5));
            }
            printf("Did the Components\n");
            
            // Pick 3 DIFFERENT Player Counts
            for (i=0; i<50; i++)
                used[i] = 0;
            for (i=0; i<3; i++)
            {
                a = rand()%noPlayers;     // this picked the Player Counts
                while ( used[a] > 0 )
                    a = rand()%noPlayers;
                used[a] = 1;
                // and decide which square to put it in!
                j = rand()%25;              // this is the cell to put it in
                while ( cards[j/5][j%5] > 0 )      // keep looking for an open cell
                    j = rand()%25;
                cards[j/5][j%5] = 1;
                fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (%s) true charpath col2 1.0 setlinewidth fill -90 rotate \n", 133+(j/5)*75, 396*card+13+75*(j%5), playerCounts[a]);
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col2 1.0 setlinewidth fill -90 rotate \n", 154+(j/5)*75, 396*card+13+75*(j%5));
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col2 1.0 setlinewidth fill -90 rotate \n", 190+(j/5)*75, 396*card+13+75*(j%5));
            }
            printf("Did the Player Counts\n");
            
            
            // Pick 2 DIFFERENT Designer Characteristic
            for (i=0; i<50; i++)
                used[i] = 0;
            for (i=0; i<2; i++)
            {
                if ( i == 0 )
                    a = 0;
                if ( i > 0 )
                    a = rand()%(noDesChar-1)+1;
                //a = rand()%noDesChar;            // pick this Designer Characteristic
                while ( used[a] > 0 )
                    a = rand()%(noDesChar-1)+1;
                    //a = rand()%noDesChar;
                used[a] = 1;
                
                // and decide which square to put it in!
                j = rand()%25;                      // this is the cell to put it in
                while ( cards[j/5][j%5] > 0 )      // keep looking for an open cell
                    j = rand()%25;
                cards[j/5][j%5] = 1;
                for (k=0; k<sectionsPerDesChar[a]; k++)
                {
                    fprintf(fout, "/Avenir-Black findfont 11 scalefont setfont newpath %i %i m 90 rotate (%s) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 133+(j/5)*75+11*k, 396*card+13+75*(j%5), desChar[a][k]);
                }
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (GN:) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 154+(j/5)*75, 396*card+13+75*(j%5));
                fprintf(fout, "/Avenir-Roman findfont 8 scalefont setfont newpath %i %i m 90 rotate (DI:) true charpath col0 1.0 setlinewidth fill -90 rotate \n", 190+(j/5)*75, 396*card+13+75*(j%5));
            }
            printf("Did the Designer Characteristic\n");
            open = 0;       // count how many open cells are on the card
            for (i=0; i<25; i++)
                if ( cards[i/5][i%5] > 0 )
                    open++;
            printf("5: Used Squares is %i\n", open);
        }
        
        // Put bottom of page matter in file
        fprintf(fout, "showpage\n");
        fprintf(fout, "0.96 0.96 scale\n");
        fprintf(fout, "0 16  translate\n");
        

        printf("Made page %i which are Mad-Bingo cards %i and %i\n", noPages+1, 2*noPages+1, 2*noPages+2);
    }

    // Put bottom matter in file
    fprintf(fout, "$F2psEnd\n");
    
    // Close file
    fclose(fout);
    
    
    
    printf("\n\nAll Done! Open the file:///Users/randy/Desktop/Mad-Bingo2021.ps\n\n");
    
    return 0;
}
