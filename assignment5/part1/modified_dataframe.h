#pragma once

#include "dataframe.h"
#include "thread.h"
#include "string.h"

class DataFrameThreadOne: public Thread {
  public:
    DataFrame* dataframe;
    Rower* r;

    DataFrameThreadOne(DataFrame* mod, Rower* row) {
      dataframe = mod;
      r = row;
    } 

    virtual void run() {
      for (int i = 0; i < dataframe->nrows() / 2; i++) {
            r->accept(*dataframe->row_arr_->get(i));
        }

    }
};

class DataFrameThreadTwo: public Thread {
  public:
    DataFrame* dataframe;
    Rower* r;

    DataFrameThreadTwo(DataFrame* mod, Rower* row) {
      dataframe = mod;
      r = row;
    } 

    virtual void run() {
      for (int i = dataframe->nrows() / 2; i < dataframe->nrows(); i++) {
            r->accept(*dataframe->row_arr_->get(i));
        }

    }
};


class ModifiedDataFrame : public DataFrame {
    public:

        ModifiedDataFrame(Schema& schema) : DataFrame(schema){ }

        /** This method clones the Rower and executes the map in parallel. Join is
         * used at the end to merge the results. */
        void pmap(Rower& r) {
            Rower* r2 = static_cast<Rower*>(r.clone());
            DataFrameThreadOne t(this, &r);
            DataFrameThreadTwo t2(this, r2);

            t.start();
            t2.start();
            t.join();
            t2.join();
            r.join_delete(r2);
        }
};