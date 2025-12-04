#pragma once

#include "control_flow_graph.h"

class StackMachine
{
public:
   StackMachine( const ControlFlowGraph& cfg );
private:
  ControlFlowGraph mCfg;
};
