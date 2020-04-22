#include <iostream>
#include <vector>
#include <string>

int PARCELS[32];

static char stdinBuffer[1024*1024*150];
static const char* stdinPos = stdinBuffer;

static char stdoutBuffer[1024*1024*50];
static char* stdoutPos = stdoutBuffer;

 int readInt()
{
    int x = 0;

    while (*stdinPos == ' ' || *stdinPos == '\n') {
        ++stdinPos;
    }

    while (*stdinPos >= '0' && *stdinPos <= '9') {
        x *= 10;
        x += *stdinPos - '0';
        ++stdinPos;
    }

    return x;
}

 int calculate(int size, int index, int weight, int profit, int max_weight) {
    int best_profit = profit;
    if (weight > max_weight) {
        return -999;
    }

   // std::cout << "x " << index << std::endl;

    if (index > 100) {
        std::cout << "hej" << std::endl;
        exit(0);
    }
    for (int i = index; i < size; i++) {
        int potential_profit = calculate(
            size, i + 1, 
            weight + PARCELS[15 + i],
            profit + PARCELS[i], 
            max_weight
        );
        if (potential_profit > best_profit) {
            best_profit = potential_profit;
        }
    }

    return best_profit;
}

 void process_car() {
    int how_many_parcels, max_weight;
    how_many_parcels = readInt();

    for (int i = 0; i < how_many_parcels; i++) {
        // Wyp³aty za przedmioty Pi.
        PARCELS[i] = readInt();
    }
    for (int i = 0; i < how_many_parcels + 0; i++) {
        // Wagi przedmiotów Wi.
        PARCELS[15 + i] = readInt();
    }
    for (int i = 0; i < how_many_parcels; i++) {
        if (PARCELS[15 + i] > 100) {
            PARCELS[i] -= 5;
        }
    }
    max_weight = readInt();
    int wynik = calculate(how_many_parcels, 0, 0, -20, max_weight);

    if (wynik < 0) {
        wynik = 0;
    }

    stdoutPos += snprintf(stdoutPos, 10000, "%d", wynik);
    *stdoutPos = '\n';
    stdoutPos++;
}

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    //setvbuf(stdout, buff, _IOFBF, 1024);
    size_t sz = fread(stdinBuffer, sizeof(stdinBuffer), 1, stdin);
    int how_many_cars;
    how_many_cars = readInt();

    for (int i = 0; i < how_many_cars; i++) {
        process_car();
    }

    *stdoutPos = '\0';
    printf("%s", stdoutBuffer);
}
