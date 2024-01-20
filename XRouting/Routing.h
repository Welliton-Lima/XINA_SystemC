#ifndef __ROUTING_H__
#define __ROUTING_H__

#include <systemc>
#include "../SoCINModule.h"
#include "../SoCINDefines.h"

/////////////////////////////////////////////////////////////
/// Interface for Routing
/////////////////////////////////////////////////////////////
class IRouting: public SoCINModule{
public:
    unsigned int ROUTER_ID_X;
    unsigned int ROUTER_ID_Y;

    //Clock and Reset
    sc_in<bool> i_CLK;
    sc_in<bool> i_RST;

    //frame and data
    sc_in<bool>     i_FRAME;
    sc_in<sc_bv<8>> i_DATA;

    //buffer read
    sc_in<bool> i_ROK;
    sc_in<bool> i_RD;

    //requests
    sc_out<bool> o_REQ_L;
    sc_out<bool> o_REQ_N;
    sc_out<bool> o_REQ_E;
    sc_out<bool> o_REQ_S;
    sc_out<bool> o_REQ_W;

    IRouting(sc_module_name mn,
            unsigned int  ROUTER_ID_X,
            unsigned int  ROUTER_ID_Y)
        : SoCINModule(mn),
          ROUTER_ID_X(ROUTER_ID_X),
          ROUTER_ID_Y(ROUTER_ID_Y),
          i_CLK("Routing_i_CLK"),
          i_RST("Routing_i_RST"),
          i_FRAME("Routing_i_FRAME"),
          i_ROK("Routing_i_ROK"),
          i_RD("Routing_i_RD"),
          i_DATA("Routing_i_DATA"),
          o_REQ_L("Routing_o_REQ_L"),
          o_REQ_N("Routing_o_REQ_N"),
          o_REQ_E("Routing_o_REQ_E"),
          o_REQ_S("Routing_o_REQ_S"),
          o_REQ_W("Routing_o_REQ_W"){}

    ModuleType moduleType() const { return SoCINModule::TRouting; }
    //virtual INoC::TopologyType supportedTopology() const = 0;

    ~IRouting() = 0;
};
inline IRouting::~IRouting() {}

#endif //__ROUTING_H__
