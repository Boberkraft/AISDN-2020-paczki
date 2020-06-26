#include <iostream>

int PARCELS[32];


static char IN_BUFFER[1024 * 1024 * 170];
static const char* in_pos = IN_BUFFER;

static char OUT_BUFFER[1024 * 1024 * 50];
static char* out_pos = OUT_BUFFER;

static short int temp_get_int = 0;
int get_int()
{
    temp_get_int = 0;

    while (*in_pos == ' ' || *in_pos == '\n') {
        ++in_pos;
    }

    while (*in_pos >= '0' && *in_pos <= '9') {
        temp_get_int *= 10;
        temp_get_int += *in_pos - '0';
        ++in_pos;
    }

    return temp_get_int;
}

int calculate(int size, int index, int weight, int profit, int max_weight) {
    int best_profit = profit;

    if (weight > max_weight) {
        return -999;
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
    int how_many_parcels, max_weight, sum_weight, sum_cost, wynik;
    sum_weight = 0;
    sum_cost = -20;
    how_many_parcels = get_int();

    for (int i = 0; i < how_many_parcels; i++) {
        // Wypłaty za przedmioty Pi.
        PARCELS[i] = get_int();
    }
    for (int i = 0; i < how_many_parcels + 0; i++) {
        // Wagi przedmiotów Wi.
        PARCELS[15 + i] = get_int();
        sum_weight += PARCELS[15 + i];
    }
    for (int i = 0; i < how_many_parcels; i++) {
        if (PARCELS[15 + i] > 100) {
            PARCELS[i] -= 5;
        }
        if (PARCELS[i] > 0) {
            sum_cost += PARCELS[i];
        }
    }
    max_weight = get_int();

    wynik = 0;

    if (max_weight > sum_weight) {
        wynik = sum_cost;
    }
    else {
        wynik = calculate(how_many_parcels, 0, 0, -20, max_weight);
    }

    if (wynik < 0) {
        wynik = 0;
    }

    out_pos += snprintf(out_pos, 10000, "%d", wynik);
    *out_pos = '\n';
    out_pos++;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    fread(IN_BUFFER, sizeof(IN_BUFFER), 1, stdin);

    int how_many_cars = get_int();

    for (int i = 0; i < how_many_cars; i++) {
        process_car();
    }

    *out_pos = '\0';
    printf("%s", OUT_BUFFER);

    return 0;
}
