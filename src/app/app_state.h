#ifndef APP_STATE
#define APP_STATE
#include "../math/vector_2d.h"

/*This class holds all the data for the application. It may be considered as the model in the model view controller design*/
class app_state {
public:
  app_state();
  ~app_state();
  app_state(const app_state&) = delete;
  app_state& operator=(const app_state&) = delete;
private:
  vector_2d<double> top_left_value;

};

#endif
