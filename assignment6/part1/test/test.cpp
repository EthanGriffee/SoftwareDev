#include "../src/helper.h"
#include "../src/directory.h"

void testDirectory() {
    Directory* dir  = new Directory();
    StringArray* str_arr = new StringArray();
    str_arr->add(new String("JAMES"));
    StringArray* str_arr2 = new StringArray();
    str_arr2->add(new String("JOKER"));
    dir->checkAddDir(str_arr);
    dir->checkAddDir(str_arr2);
    str_arr->t_true(dir->getSize() == 2);
    IntArray* int_arr = new IntArray();
    str_arr->t_true(dir->getSockets()->equals(int_arr));
    str_arr->OK("Directory OK");
    str_arr->addAll(str_arr2);
    str_arr->t_true(dir->getIps()->equals(str_arr));

}


int main(int argc, char **argv) {
    testDirectory();
}