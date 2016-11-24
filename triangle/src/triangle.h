#include <stdio.h>
#include <assert.h>

/**
* @file triangle.h
* @brief use "Chain of Responsibility" pattern 
*        benefit:
*        1. easy to extend another triangle type judgement;
*        2. when we do not know what type it is ,we just put it on the chain, so that
*        we can get an easy way to handle it.
*
* @author liuyuan
* @version 1.0
* @date 2016-11-23
*/

enum TriangleType{
    INVALID,
    EQUILATERAL,
    ISOSCELES,
    SCALENE,
    UNKNOWN
};

class Triangle{
    public:
        Triangle(int len_a, int len_b, int len_c):_len_a(len_a), _len_b(len_b), _len_c(len_c){}
        bool isValid(){
            if( ( _len_a + _len_b <= _len_c ) || ( _len_a + _len_c <= _len_b ) || ( _len_b + _len_c <= _len_a ) ){
                return false;
            }
            return true;
        }
    public:
        int _len_a;
        int _len_b;
        int _len_c;
};

class Handler{
    public:
        Handler():_successor(NULL){}
        void setSuccessor(Handler & hd){
            _successor = &hd;
        }
       virtual TriangleType handle(Triangle & t) = 0;
    public:
        Handler * _successor;
};


class Equilateral:public Handler{
    public:
        TriangleType handle(Triangle & t){
            if(!t.isValid()){
                return INVALID;
            }
            if(t._len_a == t._len_b && t._len_b == t._len_c){
                return EQUILATERAL;
            }

            if(NULL != _successor){
                return _successor->handle(t);
            }
            return UNKNOWN;

        }
};

class Isosceles:public Handler{
    public:
        TriangleType handle(Triangle & t){
            if(t._len_a == t._len_b || t._len_b == t._len_c || t._len_a == t._len_c){
                return ISOSCELES;
            }

            if(NULL != _successor){
                return _successor->handle(t);
            }
            return UNKNOWN;
        }
        
};

class Scalene:public Handler{
    public:
        TriangleType handle(Triangle & t){
            if(t._len_a != t._len_b && t._len_b != t._len_c && t._len_a != t._len_c){
                return SCALENE;
            }

            if(NULL != _successor){
                return _successor->handle(t);
            }
            return UNKNOWN;

        }
};

class TriangleService{
    public:
        TriangleService(){
            _e.setSuccessor(_i);
            _i.setSuccessor(_s);
        }
        TriangleType doJudge(Triangle &t){
            return _e.handle(t);
        }
    private:
        Equilateral _e;
        Isosceles _i;
        Scalene _s;
};
