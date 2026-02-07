#include <stdio.h>

int main(void) {
    int prev, curr;
    int state = 0;
    int unstable = 0;

    scanf("%d", &prev);

    while (1) {
        scanf("%d", &curr);
        if (curr == 0)
            break;

        if (curr != prev) {
            int new_state = (curr > prev) ? 1 : -1;

            if (state != 0 && new_state != state) {
                unstable = 1;
                break;
            }

            state = new_state;
        }

        prev = curr;
    }

    printf("%s\n", unstable ? "SIM" : "NAO");
    return 0;
}
