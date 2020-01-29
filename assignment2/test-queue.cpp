//lang:Cpp
#include <iostream>
#include <assert.h>
#include "object.h"
#include "queue.h"

void println(const char* value) {
  std::cout << value << std::endl;
}

void test_object() {
  println("---- Testing Object ----");
  Object* o1 = new Object();
  assert(o1->equals(o1));
  Object* o2 = new Object();
  assert(!o2->equals(o1));
  assert(o2->hash() != 0);
  assert(o2->hash() != o1->hash());
  delete o1;
  delete o2;
  println("---- Object Passed ----");
}

void test_string() {
  println("---- Testing String ----");
  String* s0 = new String();
  String* s1 = new String("Hello");
  assert(s1->equals(s1));

  String* s01 = s0->concat(*s1);
  assert(s01->equals(s1));
  String* s2 = new String(*s01);
  assert(s1->equals(s2));

  assert(s1->length() == 5);
  String x0("ll");
  String x1("$");

  assert(s1->find(x0) == 2);
  assert(s1->find(x1) > s1->length());

  String* sub1 = new String("He");
  assert(s1->substring(0, s1->length())->equals(s1));
  assert(s1->substring(0, 2)->equals(sub1));

  assert(s1->char_at(4) == 'o');
  assert(s1->hash() == s01->hash());

  delete s1;
  delete s0;
  delete s01;
  delete s2;
  delete sub1;

  println("---- String Passed ----");
}

void test_queue() {
  println("---- Testing Queue ----");
  Queue* q0 = new Queue();
  Object* o = new Object();
  Object* p = new Object();
  Object* q = new Object();
  q0->enqueue(o);
  q0->enqueue(p);
  assert(q0->dequeue()->equals(o));
  q0->enqueue(q);
  assert(q0->dequeue()->equals(p));
  q0->enqueue(p);
  q0->enqueue(o);
  assert(!q0->is_empty());
  assert(q0->size() == 3);

  Queue* q1 = new Queue();
  String* a = new String("A");
  String* b = new String("B");
  String* c = new String("C");

  q1->enqueue(a);
  q1->enqueue(b);
  q1->enqueue(c);

  assert(!q1->is_empty());
  assert(q1->size() == 3);

  assert(q1->peek()->equals(a));
  assert(q1->dequeue()->equals(a));
  assert(q1->size() == 2);

  Queue* q2 = new Queue();
  q2->enqueue(b);
  q2->enqueue(c);

  assert(q1->equals(q2));
  assert(q1->hash() == q2->hash());

  Queue *q3 = new Queue(*q2);
  assert(q1->equals(q3));
  q3->clear();

  assert(q3->size() == 0);
  assert(q3->is_empty());

  delete a;
  delete q0;
  delete q1;
  delete q2;
  delete q3;
  println("---- Queue Passed ----");
}

int main() {
  test_object();
  test_string();
  test_queue();
}
