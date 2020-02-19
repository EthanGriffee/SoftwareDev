#pragma once

#include "string.h"
#include "object.h"
#include "array.h"
#include "helper.h"
#include "map.h"
#include "dataframe.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <mutex>

class ModifiedDataFrame : public DataFrame {

    void pmap_helper1_(Rower& r) {
        for (int i = 0; i < nrows() / 2; i++) {
            r.accept(*row_arr_->get(i));
        }
    }

    void pmap_helper2_(Rower& r) {
        for (int i = nrows() / 2; i < nrows(); i++) {
            r.accept(*row_arr_->get(i));
        }
    }

  /** This method clones the Rower and executes the map in parallel. Join is
  * used at the end to merge the results. */
    void pmap(Rower& r) {
        Rower* r2 = static_cast<Rower*>(r.clone());

        t1.join();
        t2.join();
        r.join_delete(r2);
    
    }
};

class DataFrameThreadOne: public Thread {
  public:
    ModifiedDataFrame* dataframe;
    Rower r;

    DataFrameThreadOne(ModifiedDataFrame* mod, Rower& r) {
      dataframe = mod;
      this.r = r;
    } 

    void run() {
      for (int i = 0; i < nrows() / 2; i++) {
            r.accept(ModifiedDataFrame->);
        }

    }
    

}