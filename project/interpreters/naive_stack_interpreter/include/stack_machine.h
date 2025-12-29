#pragma once

#include "control_flow_graph.h"

class StackMachine
{
public:
   StackMachine( const ControlFlowGraph& cfg );
   int exec();
private:
  ControlFlowGraph mCfg;
};
