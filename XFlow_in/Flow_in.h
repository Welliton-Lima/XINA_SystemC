#ifndef __FLOW_IN__
#define __FLOW_IN__

#include <systemc>
#include "../SoCINModule.h"

//data width and mode
class IFlow_in : public SoCINModule{

public:
    sc_in<bool> i_CLK;
    sc_in<bool> i_RST;

    sc_in<sc_bv<9>>  i_DATA;
    sc_out<sc_bv<9>> o_DATA;

    sc_in<bool>  i_VAL;
    sc_in<bool>  i_WOK;
    sc_out<bool> o_ACK;
    sc_out<bool> o_WR;

    IFlow_in(sc_module_name mn)
            : SoCINModule(mn),
            i_CLK("IFlow_in_i_CLK"),
            i_RST("IFlow_in_i_RST"),
            i_VAL("IFlow_in_i_VAL"),
            i_WOK("IFlow_in_i_WOK"),
            i_DATA("IFlow_in_i_DATA"),
            o_ACK("IFlow_in_o_ACK"),
            o_WR("IFlow_in_o_WR"),
            o_DATA("IFlow_in_o_DATA"){}

  ModuleType moduleType() const { return SoCINModule::TInputFlowControl; }

  ~IFlow_in() = 0;
};

inline IFlow_in::~IFlow_in(){}
#endif //__FLOW_IN__
