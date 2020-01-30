//lang:Cpp
#include <iostream>
#include <assert.h>
#include "object.h"
#include "string.h"
#include "queue.h"

void println(const char* value) {
  std::cout << value << std::endl;
}

void test_queue_constructor_destructor() {
  println("test_queue_constructor pending");
  Queue* q = new Queue();
  assert(q != nullptr);
  delete q;
  println("test_queue_constructor passed");
}

void test_queue_enqueue() {
  println("test_queue_enqueue pending");
  Queue* q = new Queue();
  Object* o = new Object();
  assert(q->size() == 0);
  q->enqueue(o);
  assert(q->size() == 1);
  delete q;
  println("test_queue_enqueue passed");
}

void test_queue_dequeue() {
  println("test_queue_dequeue pending");
  Queue* q = new Queue();
  Object* o = new Object();
  q->enqueue(o);
  assert(q->size() == 1);
  assert(o->equals(q->dequeue()));
  assert(q->size() == 0);
  assert(q->dequeue() == nullptr);
  delete o;
  delete q;
  println("test_queue_dequeue passed");
}

void test_queue_peek() {
  println("test_queue_peek pending");
  Queue* q = new Queue();
  Object* o = new Object();
  q->enqueue(o);
  assert(q->size() == 1);
  assert(o->equals(q->peek())); 
  q->dequeue();
  assert(q->peek() == nullptr);
  delete o;
  delete q;
  println("test_queue_peek passed");
}

void test_queue_size() {
  println("test_queue_size pending");
  Queue* q = new Queue();
  for (uint i = 0; i < 100; i++) {
    assert(q->size() == i);
    q->enqueue(new Object());
  }
  for (uint i = 100; i > 0; i--) {
    assert(q->size() == i);
    delete q->dequeue();
  }
  assert(q->size() == 0);
  delete q;
  println("test_queue_size passed");
}

void test_queue_is_empty() {
  println("test_queue_is_empty pending");
  Queue *q = new Queue();
  assert(q->is_empty());
  q->enqueue(new Object());
  assert(!q->is_empty());
  delete q;
  println("test_queue_is_empty passed");
}

void test_queue_clear() {
  println("test_queue_clear pending");
  Queue *q = new Queue();
  for (uint i = 0; i < 10; i++) {
    q->enqueue(new Object());
  }
  assert(q->size() > 0);
  q->clear();
  assert(q->size() == 0);
  delete q;
  println("test_queue_clear passed");
}

void test_queue_equality() {
  println("test_queue_equality pending");
  Queue* q1 = new Queue();
  Queue* q2 = new Queue();

  assert(q1->equals(q2));
  assert(q1->hash() == q2->hash());

  Object* o1 = new Object();
  q1->enqueue(o1);
  assert(!q1->equals(q2));
  q2->enqueue(o1);
  assert(q1->equals(q2));
  delete q1;
  println("test_queue_equality passed");
}

void test_queue_complex() {
  println("test_queue_complex pending");
  Queue *q = new Queue();
  for (uint i = 0; i < 1000; i++) {
    if (i % 2 == 0) {
      q->enqueue(new Object());
      q->enqueue(new Object());
      q->enqueue(new Object());
    } else {
      delete q->dequeue();
    }
  }
  delete q;
  println("test_queue_complex passed");
}

void test_strqueue_constructor_destructor() {
  println("test_strqueue_constructor pending");
  StrQueue* q = new StrQueue();
  assert(q != nullptr);
  delete q;
  println("test_strqueue_constructor passed");
}

void test_strqueue_enqueue() {
  println("test_strqueue_enqueue pending");
  StrQueue* q = new StrQueue();
  String* s = new String("Hello");
  assert(q->size() == 0);
  q->enqueue(s);
  assert(q->size() == 1);
  delete q;
  println("test_strqueue_enqueue passed");
}

void test_strqueue_dequeue() {
  println("test_strqueue_dequeue pending");
  StrQueue* q = new StrQueue();
  String* s = new String("Testing");
  q->enqueue(s);
  assert(q->size() == 1);
  assert(s->equals(q->dequeue()));
  assert(q->size() == 0);
  assert(q->dequeue() == nullptr);
  delete s;
  delete q;
  println("test_strqueue_dequeue passed");
}

void test_strqueue_peek() {
  println("test_strqueue_peek pending");
  StrQueue* q = new StrQueue();
  String* s = new String("Look ma! No hands");
  q->enqueue(s);
  assert(q->size() == 1);
  assert(s->equals(q->peek())); 
  q->dequeue();
  assert(q->peek() == nullptr);
  delete s;
  delete q;
  println("test_strqueue_peek passed");
}

void test_strqueue_size() {
  println("test_strqueue_size pending");
  StrQueue* q = new StrQueue();
  for (uint i = 0; i < 100; i++) {
    assert(q->size() == i);
    q->enqueue(new String());
  }
  for (uint i = 100; i > 0; i--) {
    assert(q->size() == i);
    delete q->dequeue();
  }
  assert(q->size() == 0);
  delete q;
  println("test_strqueue_size passed");
}

void test_strqueue_is_empty() {
  println("test_strqueue_is_empty pending");
  StrQueue *q = new StrQueue();
  assert(q->is_empty());
  q->enqueue(new String());
  assert(!q->is_empty());
  delete q;
  println("test_strqueue_is_empty passed");
}

void test_strqueue_clear() {
  println("test_strqueue_clear pending");
  StrQueue *q = new StrQueue();
  for (uint i = 0; i < 10; i++) {
    q->enqueue(new String());
  }
  assert(q->size() > 0);
  q->clear();
  assert(q->size() == 0);
  delete q;
  println("test_strqueue_clear passed");
}

void test_strqueue_equality() {
  println("test_strqueue_equality pending");
  StrQueue* q1 = new StrQueue();
  StrQueue* q2 = new StrQueue();

  assert(q1->equals(q2));
  assert(q1->hash() == q2->hash());

  q1->enqueue(new String("Foo"));
  assert(!q1->equals(q2));
  q2->enqueue(new String("Bar"));
  assert(!q1->equals(q2));
  delete q2->dequeue();
  q2->enqueue(new String("Foo"));
  assert(q1->equals(q2));

  delete q1;
  delete q2;
  println("test_strqueue_equality passed");
}

void test_strqueue_complex() {
  println("test_strqueue_complex pending");
  StrQueue *q = new StrQueue();
  for (uint i = 0; i < 1000; i++) {
    if (i % 2 == 0) {
      q->enqueue(new String("Foo"));
      q->enqueue(new String("Bar"));
      q->enqueue(new String("Baz"));
    } else {
      delete q->dequeue();
    }
  }
  delete q;
  println("test_strqueue_complex passed");
}

int main() {
  test_queue_constructor_destructor();
  test_queue_enqueue();
  test_queue_dequeue();
  test_queue_peek();
  test_queue_size();
  test_queue_is_empty();
  test_queue_clear();
  test_queue_equality();
  test_queue_complex();

  test_strqueue_constructor_destructor();
  test_strqueue_enqueue();
  test_strqueue_dequeue();
  test_strqueue_peek();
  test_strqueue_size();
  test_strqueue_is_empty();
  test_strqueue_clear();
  test_strqueue_equality();
  test_strqueue_complex();
}