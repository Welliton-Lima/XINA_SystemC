#ifndef __FLOW_OUT__
#define __FLOW_OUT__

#include <systemc>

#include "../SoCINModule.h"

//data width and mode
class IFlow_out : public SoCINModule{
public:
    sc_in<bool> i_CLK;
    sc_in<bool> i_RST;

    sc_in<sc_bv<9>> i_DATA;
    sc_out<sc_bv<9>> o_DATA;

    sc_in<bool> i_ROK;
    sc_in<bool> i_ACK;
    sc_out<bool> o_RD;
    sc_out<bool> o_VAL;

        IFlow_out(sc_module_name mn)
        : SoCINModule(mn),
        i_CLK("IFlow_out_i_CLK"),
        i_RST("IFlow_out_i_RST"),
        i_ROK("IFlow_out_i_ROK"),
        i_ACK("IFlow_out_i_ACK"),
        i_DATA("IFlow_out_i_DATA"),
        o_RD("IFlow_out_o_RD"),
        o_VAL("IFlow_out_o_VAL"),
        o_DATA("IFlow_out_o_DATA") {}

  ModuleType moduleType() const { return SoCINModule::TOutputFlowControl; }

  ~IFlow_out() = 0;
};
inline IFlow_out::~IFlow_out(){}

#endif //__FLOW_OUT__
