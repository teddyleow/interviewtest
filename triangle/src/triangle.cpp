#include <stdio.h>
#include <assert.h>
#include "triangle.h"

int main(){

    TriangleService ts;
    {
        Triangle t(4,4,4);
        ts.doJudge(t);
    }
    {
        Triangle t(4,7,4);
        ts.doJudge(t);
    }
    {
        Triangle t(5,7,4);
        ts.doJudge(t);
    }

    return 0;
}
