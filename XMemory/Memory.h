#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <systemc>

#include "../SoCINModule.h"

/////////////////////////////////////////////////////////////
/// interface for Memory
/////////////////////////////////////////////////////////////
template<int FIFO_DEPTH>
class IMemory : public SoCINModule {

public:

    // System interfaces
    sc_in<bool> i_CLK;
    sc_in<bool> i_RST;

    // read from buffer
    sc_out<bool> o_ROK;
    sc_in<sc_bv<9>> i_DATA;
    sc_in<bool> i_RD;

    //write to buffer
    sc_out<sc_bv<9>> o_DATA;
    sc_in<bool> i_WR;
    sc_out<bool> o_WOK;

    IMemory(sc_module_name mn)
        : SoCINModule(mn),
          i_CLK("Mem_i_CLK"),
          i_RST("Mem_i_RST"),
          i_DATA("Mem_i_DATA"),
          i_RD("Mem_i_RD"),
          i_WR("Mem_i_WR"),
          o_DATA("Mem_o_DATA"),
          o_ROK("Mem_o_ROK"),
          o_WOK("Mem_o_WOK"){}

    ModuleType moduleType() const { return SoCINModule::TArbiter; }

     ~IMemory() = 0;
};

/// destructor of abstract class
template<int FIFO_DEPTH>
inline IMemory<FIFO_DEPTH>::~IMemory(){}


/////////////////////////////////////////////////////////////
/// End of interface for Arbiters
/////////////////////////////////////////////////////////////

#endif // __MEMORY_H__
