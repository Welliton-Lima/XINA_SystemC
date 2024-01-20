#ifndef __ARBITER_H__
#define __ARBITER_H__

#include "../SoCINModule.h"
/////////////////////////////////////////////////////////////
/// Interface for Arbiters
/////////////////////////////////////////////////////////////

class IArbiter : public SoCINModule {
protected:
      unsigned short ROUTER_ID, PORT_ID;
      unsigned short nPorts;
public:
    // System interfaces
    sc_in<bool> i_CLK; // Clock
    sc_in<bool> i_RST; // Reset

    sc_in<sc_bv<4>>i_REQ;
    sc_out<sc_bv<4>>o_GNT;

    IArbiter(sc_module_name mn,
             unsigned short nPorts,
             unsigned short ROUTER_ID,
             unsigned short PORT_ID)
        : SoCINModule(mn),
          i_CLK("Arb_i_CLK"),
          i_RST("Arb_i_RST"),
          i_REQ("Arb_i_REQ"),
          o_GNT("Arb_oGRANT"),
          nPorts(nPorts),
          ROUTER_ID(ROUTER_ID),
          PORT_ID(PORT_ID){}

     ModuleType moduleType() const { return SoCINModule::TArbiter; }

    ~IArbiter()=0;
};

/// destructor of abstract class
inline IArbiter::~IArbiter() {}

/////////////////////////////////////////////////////////////
/// End of interface for Arbiters
/////////////////////////////////////////////////////////////


#endif // ARBITER_H
