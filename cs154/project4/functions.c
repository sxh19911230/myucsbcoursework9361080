#include "functions.h"

struct B {
    int i;
} b;

void *initPredictor(int size, int type) {
    return &b;
}

int access(void *predictor, int PCOfBranch){
    return 0;
}


void update(void *predictor, int PCOfBranch, int result){}

int numAccesses(void *predictor){
    return 1;
}

float hitRate(void *predictor){
    return 2.0;
}
