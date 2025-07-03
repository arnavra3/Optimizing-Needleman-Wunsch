#include <bits/stdc++.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "helper.h"
using namespace std; //
int main(int argc, char *argv[])
{
    string a, b;
    string c;
    srand(time(NULL));
    c = RandomSeqGen(10000 + 10000);
    a = c.substr(0, 10000);
    b = c.substr(10000, 20000);
    int gap = -2;
    int match = 1;
    int mismatch = -1;
    if (strcmp(argv[1], "-unopt") == 0)
    {
        Needleman_Wunsch(a, b, match, mismatch, gap);
    }
    else if (strcmp(argv[1], "-optv1") == 0)
        Needleman_Wunsch_optv1(a, b, match, mismatch, gap);
    else if (strcmp(argv[1], "-optv2") == 0)
        Needleman_Wunsch_optv2(a, b, match, mismatch, gap);
    else if (strcmp(argv[1], "-optv3") == 0)
        Needleman_Wunsch_optv3(a, b, match, mismatch, gap);
    else if (strcmp(argv[1], "-optv4") == 0)
        Needleman_Wunsch_optv4(a, b, match, mismatch, gap);
    else if (strcmp(argv[1], "-optv5") == 0)
        Needleman_Wunsch_optv5(a, b, match, mismatch, gap);
    else if (strcmp(argv[1], "-optv6") == 0)
        Needleman_Wunsch_optv6(a, b, match, mismatch, gap);
    
    else if (strcmp(argv[1], "-optv7") == 0)
        Needleman_Wunsch_optv7(a, b, match, mismatch, gap);
}