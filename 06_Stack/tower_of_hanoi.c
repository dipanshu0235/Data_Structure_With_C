// Tower of Hanoi (Recursion)
#include <stdio.h>

static unsigned long long moves = 0;
static void hanoi(int disks, char source, char auxiliary, char destination) {
    if (disks == 0) return;
    hanoi(disks - 1, source, destination, auxiliary);
    printf("Move disk %d from %c to %c\n", disks, source, destination);
    ++moves;
    hanoi(disks - 1, auxiliary, source, destination);
}
int main(void) {
    int disks;
    printf("Number of disks (0-20): ");
    if (scanf("%d", &disks) != 1 || disks < 0 || disks > 20) {
        puts("Invalid number of disks.");
        return 1;
    }
    hanoi(disks, 'A', 'B', 'C');
    printf("Total moves: %llu\n", moves);
    return 0;
}
