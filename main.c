#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VELICINA 5

int rjesenje[VELICINA][VELICINA];
int ploca[VELICINA][VELICINA];
int hintRed[VELICINA][VELICINA];
int hintStupac[VELICINA][VELICINA];
int redHintCount[VELICINA];
int stupacHintCount[VELICINA];

void resetPloca()
{
    for (int i = 0; i < VELICINA; i++)
        for (int j = 0; j < VELICINA; j++)
            ploca[i][j] = 0;
}

void generirajRjesenje()
{
    srand(time(NULL));
    for (int i = 0; i < VELICINA; i++)
        for (int j = 0; j < VELICINA; j++)
            rjesenje[i][j] = rand() % 2;
}

void generirajHintove() // Hintovi za redove
{
    for (int i = 0; i < VELICINA; i++)
    {
        int count = 0, index = 0;
        for (int j = 0; j < VELICINA; j++)
        {
            if (rjesenje[i][j] == 1)
            {
                count++;
                if (j == VELICINA - 1)
                    hintRed[i][index++] = count;
            }
            else if (count > 0)
            {
                hintRed[i][index++] = count;
                count = 0;
            }
        }
        if (index == 0)
            hintRed[i][index++] = 0;
        redHintCount[i] = index;
    }

    // Hintovi za stupce
    for (int j = 0; j < VELICINA; j++)
    {
        int count = 0, index = 0;
        for (int i = 0; i < VELICINA; i++)
        {
            if (rjesenje[i][j] == 1)
            {
                count++;
                if (i == VELICINA - 1)
                    hintStupac[j][index++] = count;
            }
            else if (count > 0)
            {
                hintStupac[j][index++] = count;
                count = 0;
            }
        }
        if (index == 0)
            hintStupac[j][index++] = 0;
        stupacHintCount[j] = index;
    }
}

void prikaziPlocu()
{
    int maxHintRed = 0, maxHintStupac = 0;
    for (int i = 0; i < VELICINA; i++)
    {
        if (redHintCount[i] > maxHintRed)
            maxHintRed = redHintCount[i];
        if (stupacHintCount[i] > maxHintStupac)
            maxHintStupac = stupacHintCount[i];
    }

    // Prikazivanje hintova uz ploču

    for (int h = 0; h < maxHintStupac; h++)
    {
        for (int k = 0; k < maxHintRed; k++)
            printf("   ");
        for (int j = 0; j < VELICINA; j++)
        {
            int offset = maxHintStupac - stupacHintCount[j];
            if (h < offset)
                printf("   ");
            else
                printf(" %d ", hintStupac[j][h - offset]);
        }
        printf("\n");
    }

    // Prikazivanje brojeva za stupce i ploču

    for (int i = 0; i < VELICINA; i++)
    {
        int offset = maxHintRed - redHintCount[i];
        for (int h = 0; h < offset; h++)
            printf("   ");
        for (int h = 0; h < redHintCount[i]; h++)
            printf(" %d ", hintRed[i][h]);

        for (int j = 0; j < VELICINA; j++)
        {
            if (ploca[i][j] == 1)
                printf(" X ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

void oznaciPolje()
{
    int r, s;
    printf("Unesite redak (0-%d): ", VELICINA - 1);
    scanf("%d", &r);
    printf("Unesite stupac (0-%d): ", VELICINA - 1);
    scanf("%d", &s);
    if (r >= 0 && r < VELICINA && s >= 0 && s < VELICINA)
    {
        if (ploca[r][s] == 1)
        {
            ploca[r][s] = 0;
            printf("Uklonjeno polje (%d,%d).\n", r, s);
        }
        else
        {
            ploca[r][s] = 1;
            printf("Označeno polje (%d,%d).\n", r, s);
        }
    }
    else
    {
        printf("Nevažeće koordinate.\n");
    }
    prikaziPlocu();

    // Automatski prikaži ploču nakon svakog unosa
}

void provjeriRjesenje()
{
    for (int i = 0; i < VELICINA; i++)
        for (int j = 0; j < VELICINA; j++)
            if (ploca[i][j] != rjesenje[i][j])
            {
                printf("❌ Rješenje nije točno.\n");
                return;
            }
    printf("🎉 Bravo! Točno ste riješili Nonogram! 🎉\n");
}

void prikaziPravila()
{
    printf("\n📜 PRAVILA IGRE NONOGRAM 📜\n");
    printf("Cilj igre: označiti sva polja s 'X' prema zadanim brojevima (hintovima).\n");
    printf("\nObjašnjenje hintova:\n");
    printf("- Brojevi uz redove i stupce označuju koliko uzastopnih polja treba biti označeno s 'X'.\n");
    printf("- Više brojeva znači da između blokova mora biti barem jedno prazno polje.\n");
    printf("\nKako igrati:\n");
    printf("1. Pogledaj hintove (brojeve) uz rubove ploče.\n");
    printf("2. Označi (ili ukloni) polja pomoću opcije 2.\n");
    printf("3. Kad misliš da si gotov, koristi opciju 3 za provjeru rješenja.\n");
    printf("\nSretno! 🎯\n");
}

void izbornik()
{
    int izbor;
    do
    {
        printf("\n--- NONOGRAM 5x5 ---\n");
        printf("1. Prikaži ploču\n");
        printf("2. Označi ili ukloni polje\n");
        printf("3. Provjeri rješenje\n");
        printf("4. Nova igra\n");
        printf("5. Izlaz\n");
        printf("6. Pravila igre\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        if (izbor == 1)
        {
            prikaziPlocu();
        }
        else if (izbor == 2)
        {
            oznaciPolje();
        }
        else if (izbor == 3)
        {
            provjeriRjesenje();
        }
        else if (izbor == 4)
        {
            generirajRjesenje();
            generirajHintove();
            resetPloca();
            printf("🎲 Nova igra generirana.\n");
            prikaziPlocu();
        }
        else if (izbor == 5)
        {
            printf("👋 Hvala što ste igrali!\n");
        }
        else if (izbor == 6)
        {
            prikaziPravila();
        }
        else
        {
            printf("Nevažeći izbor.\n");
        }
    } while (izbor != 5);
}

int main()
{
    generirajRjesenje();
    generirajHintove();
    resetPloca();
    izbornik();
    return 0;
}
