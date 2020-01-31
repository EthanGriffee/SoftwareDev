#include <stdlib.h>
#include "Object.h"
#include "String.h"
#include "Array.h"
#include "Helper.h"

class TestArrayMethods {
    public:
    Object* a;
    Object* b;
    Object* c;
    Object* d;
    String* s1;
    String* s2;
    String* s3;
    String* s4;
    Array* arr;
    Array* arr2;
    Array* arr3;
    Array* arr4;
    StringArray* starr;
    StringArray* starr2;
    StringArray* starr3;
    StringArray* starr4;
    IntArray* iarr;
    IntArray* iarr2;
    IntArray* iarr3;
    IntArray* iarr4;
    FloatArray* farr; 
    FloatArray* farr2; 
    FloatArray* farr3; 
    FloatArray* farr4; 
    BoolArray* barr;
    BoolArray* barr2;
    BoolArray* barr3;
    BoolArray* barr4;

    Cout* cout;

    void initconditions() {
        a = new Object();
        b = new Object();
        c = new Object();
        d = new Object();
        arr = new Array();
        arr2 = new Array();
        arr3 = new Array();
        arr4 = new Array();
        cout = new Cout();
        s1 = new String("Alpha");
        s2 = new String("Bravo");
        s3 = new String("Charlie");
        s4 = new String("Delta");
        starr = new StringArray();
        starr2 = new StringArray();
        starr3 = new StringArray();
        iarr = new IntArray();
        farr = new FloatArray();
        barr = new BoolArray();
        iarr2 = new IntArray();
        farr2 = new FloatArray();
        barr2 = new BoolArray();
        iarr3 = new IntArray();
        farr3 = new FloatArray();
        barr3 = new BoolArray();
        iarr4 = new IntArray();
        farr4 = new FloatArray();
        barr4 = new BoolArray();

    }

    void clear() {
        delete a;
        delete b;
        delete c;
        delete d;
        delete arr;
        delete arr2;
        delete arr3;
        delete arr4;
        delete cout;
        delete s1;
        delete s2;
        delete s3;
        delete s4;
        delete starr;
        delete starr2;
        delete starr3;
        delete starr4;
        delete iarr;
        delete farr;
        delete barr;
        delete iarr2;
        delete farr2;
        delete barr2;
        delete iarr3;
        delete farr3;
        delete barr3;
        delete iarr4;
        delete farr4;
        delete barr4;
    }


    void testAdd() {
        initconditions();
        cout->t_true(arr->getSize() == 0);
        arr->add(a);
        cout->t_true(arr->get(0)->equals(a));
        cout->t_true(arr->getSize() == 1);
        arr->add(b);
        cout->t_true(arr->getSize() == 2);
        cout->t_true(arr->get(1)->equals(b));
        cout->t_true(arr->get(0)->equals(a));
        cout->t_true(arr->indexOf(a) == 0);
        cout->t_true(arr->indexOf(b) == 1);
        cout->pln("All basic add test works");
        clear();
    }

    void testAddWithIndexing() {
        initconditions();
        cout->t_true(arr->getSize() == 0);
        arr->add(a, 0);
        cout->t_true(arr->get(0)->equals(a));
        cout->t_true(arr->getSize() == 1);
        arr->add(b, 0);
        cout->t_true(arr->getSize() == 2);
        cout->t_true(arr->get(1)->equals(a));
        cout->t_true(arr->get(0)->equals(b));
        cout->pln("Add at beginning works");
        arr->add(c, 1);
        cout->t_true(arr->get(1)->equals(c));
        cout->t_true(arr->get(2)->equals(a));
        cout->pln("Add at middle works");
        arr->add(d, 3);
        cout->t_true(arr->get(2)->equals(a));
        cout->t_true(arr->get(3)->equals(d));
        cout->pln("Add at end works");
        clear();
    }

    void testAddAll() {
        initconditions();
        arr->add(a);
        arr->add(b);
        arr2->addAll(arr);
        cout->t_true(arr->equals(arr2));
        cout->t_true(arr2->getSize()==2);
        cout->pln("Add All works at end");
        arr3->addAll(arr);
        arr3->addAll(arr,0);
        cout->t_true(arr3->get(2)->equals(a));
        cout->t_true(arr3->get(0)->equals(a));
        cout->t_true(arr3->get(1)->equals(b));  
        cout->t_true(arr3->getSize() == 4);    
        cout->pln("Add All works at beginning");
        arr4->add(d);
        arr4->add(d);
        arr->addAll(arr4,1);
        cout->t_true(arr->get(1)->equals(d));
        cout->t_true(arr->get(2)->equals(d));
        cout->t_true(arr->get(3)->equals(b));
        cout->t_true(arr->getSize() == 4);
        cout->pln("Add All works in middle");
    clear();

}

    void testRemoveAndRemoveAll() {
        initconditions();
        arr->add(a);
        arr->add(a);
        arr->add(b, 1);
        cout->t_true(arr->getSize() == 3);
        arr->remove(a);
        cout->t_true(arr->getSize() == 2);
        cout->t_true(arr->get(0)->equals(b));
        cout->pln("Singular remove works");
        arr->add(b);
        arr->add(b);
        cout->t_true(arr->getSize() == 4);
        arr->removeAll(b);
        cout->t_true(arr->getSize() == 1);
        cout->t_true(arr->get(0)->equals(a));
        cout->pln("Remove all works");
        clear();

    }

    void testSubArray() {
        initconditions();
        arr->add(a);
        arr->add(b);
        arr->add(c);
        arr->add(d);
        Array* sub1 = arr->subArray(1);
        arr2->add(b);
        arr2->add(c);
        arr2->add(d);
        cout->t_true(sub1->equals(arr2));
        cout->pln("1 index subarray works");
        Array* sub2 = arr->subArray(1,3);
        arr3->add(b);
        arr3->add(c);
        cout->t_true(sub2->equals(arr3));
        Array* sub3 = arr->subArray(1,4);
        arr4->add(b);
        arr4->add(c);
        arr4->add(d);
        cout->t_true(sub3->equals(arr4));
        cout->pln("2 index subarray works");

        delete sub1;
        delete sub2;
        delete sub3;
        clear();

    }

    void testBasicStringArray() {
        initconditions();
        starr->add(s1);
        starr->add(s2);
        String * s = (String*) starr->get(1);
        cout->t_true(s->equals(s2));
        starr->add(s3,0);
        s = (String*) starr->get(0);
        cout->t_true(s->equals(s3));
        cout->t_true(starr->getSize() == 3);
        starr2->add(s3);
        starr2->add(s3);
        starr->addAll(starr2);
        cout->t_true(starr->getSize() == 5);
        starr3->add(s3);
        starr3->add(s1);
        starr3->add(s2);
        starr3->add(s3);
        starr3->add(s3);
        cout->t_true(starr->equals(starr3));
        cout->t_true(starr3->getSize() == 5);
        starr3->removeAll(s3);
        cout->t_true(starr3->getSize() == 2);
        s = (String*) starr3->get(0);
        cout->t_true(s->equals(s1));
        starr3->remove(s1);
        cout->t_true(starr3->getSize() == 1);
        s = (String*) starr3->get(0);
        cout->t_true(s->equals(s2));
        starr4 = (StringArray*) starr->subArray(3,5);
        cout->t_true(starr4->equals(starr2));
        cout->pln("Basic String Array Functions work");
        delete s;
        clear();
    }

    void testBasicIntArray() {
        initconditions();
        iarr->add(1);
        iarr->add(2);
        cout->t_true(iarr->get(0) == 1);
        iarr->add(0,0);
        cout->t_true(iarr->get(0) == 0);
        cout->t_true(iarr->getSize() == 3);
        iarr2->add(3);
        iarr2->add(4);
        iarr->addAll(iarr2);
        cout->t_true(iarr->getSize() == 5);
        iarr3->add(0);
        iarr3->add(1);
        iarr3->add(2);
        iarr3->add(3);
        iarr3->add(4);
        cout->t_true(iarr->equals(iarr3));
        cout->t_true(iarr3->getSize() == 5);
        iarr3->removeAll(0);
        cout->t_true(iarr3->getSize() == 4);
        cout->t_true(iarr3->get(0) == 1);
        iarr3->remove(1);
        cout->t_true(iarr3->getSize() == 3);
        cout->t_true(iarr3->get(0) == 2);
        iarr4 = iarr->subArray(2,4);
        cout->t_true(iarr4->equals(iarr3));
        cout->pln("Basic Int Array Functions work");
        clear();
    }

    void testBasicFloatArray() {
        initconditions();
        farr->add(1.1);
        farr->add(2.1);
        cout->t_true(farr->get(0) == 1.1);
        farr->add(0.1,0);
        cout->t_true(farr->get(0) == 0.1);
        cout->t_true(farr->getSize() == 3);
        farr2->add(3.1);
        farr2->add(4.1);
        farr->addAll(farr2);
        cout->t_true(farr->getSize() == 5);
        farr3->add(0.1);
        farr3->add(1.1);
        farr3->add(2.1);
        farr3->add(3.1);
        farr3->add(4.1);
        cout->t_true(farr->equals(farr3));
        cout->t_true(farr3->getSize() == 5);
        farr3->removeAll(0.1);
        cout->t_true(farr3->getSize() == 4);
        cout->t_true(farr3->get(0) == 1.1);
        farr3->remove(1.1);
        cout->t_true(farr3->getSize() == 3);
        cout->t_true(farr3->get(0) == 2.1);
        farr4 = farr->subArray(2,4);
        cout->t_true(farr4->equals(farr3));
        cout->pln("Basic Float Array Functions work");
        clear();
    }
    void testBasicBoolArray() {
        initconditions();
        barr->add(true);
        barr->add(false);
        cout->t_true(barr->get(0) == true);
        barr->add(false,0);
        cout->t_true(barr->get(0) == false);
        cout->t_true(barr->getSize() == 3);
        barr2->add(true);
        barr2->add(false);
        barr->addAll(barr2);
        cout->t_true(barr->getSize() == 5);
        barr3->add(false);
        barr3->add(true);
        barr3->add(false);
        barr3->add(true);
        barr3->add(false);
        cout->t_true(barr->equals(barr3));
        cout->t_true(barr3->getSize() == 5);
        barr3->removeAll(false);
        cout->t_true(barr3->getSize() == 2);
        cout->t_true(barr3->get(0) == true);
        barr3->remove(true);
        cout->t_true(barr3->getSize() == 0);
        cout->pln("Basic Float Array Functions work");
        clear();
    }

};



int main() {
    TestArrayMethods *t = new TestArrayMethods();
    t->testAdd();
    t->testAddWithIndexing();
    t->testAddAll();
    t->testRemoveAndRemoveAll();
    t->testSubArray();
    t->testBasicStringArray();
    t->testBasicIntArray();
    t->testBasicFloatArray();
    t->testBasicBoolArray();
    delete t;
}