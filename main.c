#include "arbre.h"
#include "Hashmap.h"
#include "listechainee.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {
    HashMap* map = createHashmap();

    addHM(map, "antoine", 12);
    addHM(map, "aude", 14);
    addHM(map, "maman", 57);
    addHM(map, "mathou", 89);
    addHM(map, "guillaume", 102);

    printf("Hashmap debut\n");
    display(map);
    printf("\n");

    printf("Size Hashmap : %d\n", sizeHM(map));
    printf("\n");

    int* res = getHM(map, "aude");
    if (res != NULL) {
        printf("Value of aude : %d\n", *res);
    } else {
        printf("The key 'aude' is not in the Hashmap\n");
    }
    printf("\n");

    printf("Removing the key 'antoine' from the Hashmap\n");
    removeHM(map, "antoine");
    printf("\n");

    printf("Update the value for the key 'maman'\n");
    updateHM(map, "maman", 1);
    printf("\n");

    printf("Final state of the Hashmap\n");
    display(map);
    printf("\n");

    printf("Size Hashmap : %d\n", sizeHM(map));
    printf("\n");
    freeHashMap(map);

    return 0;
}
