#include "../src/helper.h"
#include "../src/array.h"
#include "../src/message.h"
#include "../src/deserialize_message.h"
#include "../src/deserialize_array.h"

void testSubstring() {
    Sys s;
    char* f = "hell";
    char* f2 = s.substring(f, 1, 1);
    char* f3 = "e";
    s.t_true(*f2 == *f3);
    f2 = s.substring(f, 1, 3);
    f3 = "ell";
    s.t_true(*f2 == *f3);
    s.t_true(*f2 != *f);
    s.OK("Substring OK");
}

void testAckSerialization() {
    Ack* m = new Ack(2, 3);
    MessageDeserializer md; 
    Message* new_mess = md.deserialize(m->serialize());
    Ack* a = dynamic_cast <Ack*> (new_mess);
    m->t_true(m->equals(a));
    m->OK("Ack OK");
}



void testStatusSerialization() {
    Status* m = new Status(new String("test"), 2, 3);
    MessageDeserializer md; 
    Message* new_mess = md.deserialize(m->serialize());
    Status* a = dynamic_cast <Status*> (new_mess);
    m->t_true(m->equals(a));
    m->OK("Status OK");
}

void testStringSerialization() {
    String* hi = new String("hello");
    StringDeserializer st; 
    String* new_string = st.deserialize(hi->serialize());
    hi->t_true(hi->equals(new_string));
    hi->OK("String OK");
}

void testArraySerialization() {
    Array* arr = new Array();
    arr->add(new String("jack"));
    arr->add(new String("jill"));
    arr->add(new String("hill"));
    ArrayDeserializer ad; 
    Array* new_array = ad.deserialize(arr->serialize());
    arr->t_true(new_array->equals(arr));
    arr->OK("Array OK");
}

void testStringArraySerialization() {
    StringArray* arr = new StringArray();
    arr->add(new String("jack"));
    arr->add(new String("jill"));
    arr->add(new String("hill"));
    StringArrayDeserializer sad; 
    StringArray* new_array = sad.deserialize(arr->serialize());
    arr->t_true(new_array->equals(arr));
    arr->OK("String Array OK");
}

void testDirSerialization() {

    StringArray* arr = new StringArray();
    arr->add(new String("jack"));
    arr->add(new String("jill"));
    arr->add(new String("hill"));
    Directory direc(arr);
    Dir* m = new Dir(direc, 5, 6);
    MessageDeserializer md; 
    Message* message = md.deserialize(m->serialize());
    Dir* m2 = dynamic_cast <Dir*> (message);
    arr->OK("Dir OK");
}

void testRegisterSerialization() {
    sockaddr_in reg_addr;

    reg_addr.sin_family = AF_INET;
    reg_addr.sin_port = htons(8080);
    assert(inet_pton(AF_INET, "127.0.0.1", &reg_addr.sin_addr)>0);

    Register* m = new Register(reg_addr, 1, 1);
    MessageDeserializer md; 
    Message* message = md.deserialize(m->serialize());
    Register* m2 = dynamic_cast <Register*> (message);
    m->t_true(ntohs(m2->getSockAddr().sin_port) == 8080);
    m->OK("Reg OK");
}


int main(int argc, char **argv) {
    testSubstring();
    testAckSerialization();
    testStatusSerialization();
    testStringSerialization();
    testArraySerialization();
    testStringArraySerialization();
    testDirSerialization();
    testRegisterSerialization();
}