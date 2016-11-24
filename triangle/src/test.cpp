#include "test.h"

int main(){
    TriangleServiceTest tst;
    tst.testTriangleValidity();
    tst.testEquilateral();
    tst.testIsosceles();
    tst.testScalene();
    printf("test done!\n");
    return 0;
}
