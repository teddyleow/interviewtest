#include "triangle.h"


class TriangleServiceTest{
    public:

    //test triangle validity
    void testTriangleValidity(){
        {
            Triangle t(-1,7,5);
            assert(false == t.isValid());
        }
        {
            Triangle t(0,4,9);
            assert(false == t.isValid());
        }
        {
            Triangle t(3,2,5);
            assert(false == t.isValid());
        }
        {
            Triangle t(5,7,5);
            assert(true == t.isValid());
        }
    }
    //test Equilateral
    void testEquilateral(){
        Triangle t(4,4,4);
        assert(EQUILATERAL == _ts.doJudge(t));
    }
    //test Isosceles
    void testIsosceles(){
        Triangle t(4,6,4);
        assert(ISOSCELES == _ts.doJudge(t));
    }
    //test Scalene
    void testScalene(){
        Triangle t(3,5,4);
        assert(SCALENE == _ts.doJudge(t));
    }
    private:
        TriangleService _ts;
};
