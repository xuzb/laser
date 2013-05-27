#ifndef LASER_FUNCTION_SIMULATOR_H
#define LASER_FUNCTION_SIMULATOR_H

#include "llvm.h"

namespace llvm {
  class Function;
}

namespace laser {
  
class FunctionSimulator {
  const Function *function;
public:
  FunctionSimulator(const Function *f) : function(f) {}
  bool simulate();
};

}

#endif
