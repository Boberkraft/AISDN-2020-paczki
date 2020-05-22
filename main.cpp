◀  
Login: 182619


Tab: WS Cmt 
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114


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
