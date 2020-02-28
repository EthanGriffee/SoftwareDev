#include "helper.h"
#include "array.h"
#include <math.h>
#include "message.h"
#include "deserialize_message.h"
#include "deserialize_array.h"
#include "deserialize_double_array.h"


void printSerial(char* name, char* serial) {
    printf("Serialization of %s - %s\n", name, serial);
}

void printDeserial(char* name, char* serial)  {
    printf("Serialization of Deserialized %s - %s\n", name, serial);
}

void printBoth(char* name, Sys* sys1, Sys* sys2) {
    printSerial(name, sys1->serialize());
    printDeserial(name, sys2->serialize());
}

int main(int argc, char **argv) {
    Ack* m = new Ack(2, 3);
    MessageDeserializer md; 
    Message* new_mess = md.deserialize(m->serialize());
    Ack* a = dynamic_cast <Ack*> (new_mess);
    printBoth("ACK", m, a);
    Status* status = new Status(new String("test"), 2, 3);
    new_mess = md.deserialize(status->serialize());
    Status* status2 = dynamic_cast <Status*> (new_mess);
    String* hi = new String("hello");
    StringDeserializer st; 
    String* new_string = st.deserialize(hi->serialize());
    printBoth("STATUS", status, status2);
    Array* arr = new Array();
    arr->add(new String("jack"));
    arr->add(new DoubleObj(2121.439832832));
    arr->add(new String("hill"));
    ArrayDeserializer ad; 
    Array* new_array = ad.deserialize(arr->serialize());
    printBoth("ARRAY", arr, new_array);
    StringArray* str_arr = new StringArray();
    str_arr->add(new String("jack"));
    str_arr->add(new String("jill"));
    str_arr->add(new String("hill"));
    StringArrayDeserializer sad; 
    StringArray* new_str_array = sad.deserialize(str_arr->serialize());
    printBoth("STRING ARRARY", str_arr, new_str_array);
    Directory direc(str_arr);
    Dir* dir = new Dir(direc, 5, 6);
    Message* message = md.deserialize(dir->serialize());
    Dir* dir2 = dynamic_cast <Dir*> (message);
    printBoth("DIR", dir, dir2);
    sockaddr_in reg_addr;
    reg_addr.sin_family = AF_INET;
    reg_addr.sin_port = htons(8080);
    assert(inet_pton(AF_INET, "127.0.0.1", &reg_addr.sin_addr)>0);
    Register* reg = new Register(reg_addr, 1, 1);
    message = md.deserialize(reg->serialize());
    Register* reg2 = dynamic_cast <Register*> (message);
    printBoth("REG", m, reg2);
    DoubleArray* double_arr = new DoubleArray();
    double_arr->add(241);
    double_arr->add(342.13234);
    double_arr->add(65.32);
    DoubleArrayDeserializer dad; 
    DoubleArray* new_double_array = dad.deserialize(double_arr->serialize());
    printBoth("DOUBLEARRAY", double_arr, new_double_array);
}