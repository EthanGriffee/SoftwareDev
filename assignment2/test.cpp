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
    }

    void clear() {
        delete a, b, c, d, arr, arr2, arr3, cout;
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
        cout->t_true(arr->get(2)->equals(b));
        cout->pln("Add at middle works");
        arr->add(d, 3);
        cout->t_true(arr->get(2)->equals(b));
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
        arr->addAll(arr4, 1);
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
        Array* sub3 = arr->subArray(0,3);
        arr4->add(b);
        arr4->add(c);
        arr4->add(d);
        cout->t_true(sub3->equals(arr4));
        cout->pln("2 index subarray works");

        delete sub1, sub3, sub2;
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
        s = (String*) starr->get(0);
        cout->t_true(s->equals(s1));
        starr->remove(s1);
        cout->t_true(starr3->getSize() == 1);
        s = (String*) starr->get(0);
        cout->t_true(s->equals(s2));
        starr4 = (StringArray*) starr->subArray(3,5);
        cout->t_true(starr4->equals(starr2));
        cout->pln("Basic String Array Functions work");
        delete s;
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
    
}