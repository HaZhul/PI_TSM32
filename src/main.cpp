////////////////////////////////////////////////////////
///////      Podstawowa konfiguracja
////////////////////////////////////////////////////////
#include "obiekt.cpp"
#include "regulator.cpp"
#include <list>
#define BUFFERSYNC
#define WIN_PLOT
#define NazwaPlikuDanych "Data/TMSLABoutputData.csv"
#define CSV_NAGLOWEK "Wsp. x,Wsp. y1,Wsp. y2\n"
#define CSV_DANE "%i,%i,%i\n",Tim, y[0], y[1]

////////////////////////////////////////////////////////

#include "main.h"

#ifdef TMSLAB_WIN
#include "stdio.h"
#endif

unsigned long *ekran;
#ifdef TMSLAB_WIN
unsigned short int *textEkran;
extern int (*PartialRefresh)();
char credits[43] = "-               DEMO DISC                -";
long Timer2IsrPeriod = 1;
#ifdef WIN_PLOT
FILE *outputCSV = 0;
#endif
#endif

int Tim = 0;
int Czas = 0;
int i = 1;
unsigned int preScale = 0;
volatile char EnableRefresh = 0;

R_P_LCD_TMSLAB LCD;
R_P_KEYBOARD_TMSLAB KEYBOARD;
R_P_LEDBAR_TMSLAB LEDBAR;

#define MaxObj 200
int dx[MaxObj];
int dy[MaxObj];
int s[MaxObj];
int x[MaxObj];
int y[MaxObj];

unsigned char Bufor[] = "Pzad:100";
unsigned char Bufor2[] = "Pakt:   ";
unsigned char Bufor3[] = "Kp:5.0";
unsigned char Bufor4[] = "Ti:1.0";
unsigned char Bufor5[] = "Czas:   ";
unsigned char Pomoc[] = "   ";
unsigned char wykres[] = "Pakt";
bool paktChar = true;
bool uChar = false;
bool eChar = false;

int Pzad = 90;
int aktualne = 50;
float Y = 0;
int Y_int = 0;
float K = 5;
float Pi = 1;
int U = 0;

square woda(22, 92, 96, 26);
square graph(140, 60, 90, 60);
square akwarium(20, 20, 100, 100);
Obiekt obiekt(1, 30);
Regulator regulatorPI(K, Pi, 0, 500);
square pompa(4, 95, 15, 25);
square odplyw(121, 105, 15, 15);
std::list<square> lista_slupkow;
int wysokosci_slupkow[18] = { 0 };

int main()

{

    SetUpPeripherials();

#ifdef TMSLAB_WIN
    LCD.LCD_Init(&ekran, &textEkran);
#ifdef WIN_PLOT
    outputCSV = fopen(NazwaPlikuDanych, "w+");
#endif
#endif
    KEYBOARD.InitKB(100);
    LEDBAR.InitLedBar();
    InitData();
    EnableInterrupts();
    woda.draw_rectangle();



    while (1) {
        EnableRefresh = 1;
        LCD.Synchronize();
        EnableRefresh = 0;

        unsigned char Key = KEYBOARD.GetKey();

        Bufor[5] = (Pzad - (Pzad % 100 - Pzad % 10)) / 100 + '0';
        Bufor[6] = ((Pzad % 100 - Pzad % 10) / 10) + '0';
        Bufor[7] = Pzad % 10 + '0';

        Bufor2[5] = (Y_int - (Y_int % 100 - Y_int % 10)) / 100 + '0';
        Bufor2[6] = ((Y_int % 100 - Y_int % 10) / 10) + '0';
        Bufor2[7] = Y_int % 10 + '0';

        Bufor5[5] = (Czas - (Czas % 100 - Czas % 10)) / 100 + '0';
        Bufor5[6] = ((Czas % 100 - Czas % 10) / 10) + '0';
        Bufor5[7] = Czas % 10 + '0';

        PrintText(textEkran, Bufor, 8, 30, 2);
        PrintText(textEkran, Bufor2, 8, 30, 3);
        PrintText(textEkran, Bufor3, 6, 30, 4);
        PrintText(textEkran, Bufor4, 6, 30, 5);
        PrintText(textEkran, Bufor5, 8, 30, 6);
        PrintText(textEkran, "100", 3, 1, 1);
        PrintText(textEkran, "80", 2, 1, 4);
        PrintText(textEkran, "60", 2, 1, 7);
        PrintText(textEkran, "40", 2, 1, 9);
        PrintText(textEkran, "20", 2, 1, 12);

        if(paktChar)
        {
        	PrintText(textEkran, "Pakt", 4, 21, 6);
        }
        else if(uChar)
        {
            PrintText(textEkran, " U  ", 4, 21, 6);
        }
        else if(eChar)
        {
            PrintText(textEkran, " E  ", 4, 21, 6);
        }
        PrintText(textEkran, "t", 1, 38, 15);
        ClearScreen();
        DrawPixels(Key);


#ifdef TMSLAB_WIN
        if (PartialRefresh())
            return 0;
#ifdef WIN_PLOT
        fflush(outputCSV);
        fflush(stdout);
#endif
#endif

    }
}


#ifdef TMSLAB_WIN
void EnableInterrupts() {
}
void SetUpPeripherials() {
}
void Timer2Isr() {
    if (++preScale == 50) {
        preScale = 0;
        Tim++;
    }
}
#endif

void InitData() {
    for (int a = 0; a < (128 * 8); a++)
        ekran[a] = 0;
    for (int a = 0; a < (40 * 16); a++)
        textEkran[a] = ' ';

}
void ClearScreen() {

    for (int a = 0; a < (128 * 8); a++)
        ekran[a] = 0;
}
void DrawPixels(int Key) {
    if(Czas > 20)
    {
        Pzad = 20;
    }

    akwarium.draw_empty_aquarium();
    if (U > 0) {
        pompa.draw_rectangle();
        odplyw.draw_empty_rectangle();

    } else {
        pompa.draw_empty_rectangle();
        odplyw.draw_rectangle();
    }
    graph.draw_empty_graph();
    if (i == Tim) {
        U = (int) regulatorPI.calculate(Pzad, Y_int);
        Y = obiekt.calculate(U);
        Y_int = (int) Y;
        i++;
        if ((i % 10) == 0) {
            Czas++;
            if (Czas <= 18) {
                square slupek(137 + Czas * 5, 60, 5, 60);
                wysokosci_slupkow[Czas] = (int) (Y_int * 0.6);
                lista_slupkow.push_back(slupek);
            } else {
                Key = KEYBOARD.GetKey();
                if (Key == 0) {
                for (int m = 0; m <= 17; m++) {
                    wysokosci_slupkow[m] = wysokosci_slupkow[m + 1];
                }
                paktChar = true;
                uChar = false;
                eChar = false;
                wysokosci_slupkow[17] = (int) (Y_int * 0.6);
                }
                else if (Key==1) {
                for (int m = 0; m <= 17; m++) {
                     wysokosci_slupkow[m] = wysokosci_slupkow[m + 1];

                }
                paktChar = false;
                uChar = true;
                eChar = false;
                wysokosci_slupkow[17] = (int) (U * 0.12);
                }

                else if (Key == 2) {
                for (int m = 0; m <= 17; m++) {
                     wysokosci_slupkow[m] = wysokosci_slupkow[m + 1];
                }
                wysokosci_slupkow[17] = (int) (abs(Pzad-Y_int));
                paktChar = false;
                uChar = false;
                eChar = true;
                }


            }

        }


    }

    for(int j = 0; j<17; j++)
    {
    std::list<square>::iterator it = lista_slupkow.begin();
    std::advance(it, j);
    square Element = *it;
    Element.changing_water_level(wysokosci_slupkow[j]);
    }


    woda.changing_water_level(Y_int);


}
