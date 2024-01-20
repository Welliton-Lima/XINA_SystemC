#ifndef __NOC_H__
#define __NOC_H__

#include "../SoCINModule.h"

#include "../XRouter/Router.h"

// // Forward declaration
class IRouter;

class INoC : public SoCINModule {
protected:
    unsigned short numInterfaces;
public:

    enum TopologyType { TT_Non_Orthogonal = 0,
                        TT_Orthogonal2D,
                        TT_Orthogonal3D };

    inline unsigned short getNumberOfInterfaces() const { return this->numInterfaces; }

    // INTERFACE
    // System signals
    sc_in<bool> i_CLK;
    sc_in<bool> i_RST;

    // Routers interface - Local communication ports

        sc_vector<sc_in<sc_bv<9>>>  i_DATA_IN;
        sc_vector<sc_in<bool>>      i_VALID_IN;
        sc_vector<sc_out<bool>>     o_RETURN_IN;
        sc_vector<sc_out<sc_bv<9>>> o_DATA_OUT;
        sc_vector<sc_out<bool>>     o_VALID_OUT;
        sc_vector<sc_in<bool>>      i_RETURN_OUT;

    // Internal units
//         std::vector<vector<IRouter *>> u_ROUTER; // ATTENTION: Initialize the vector size (use resize) or use
                                     // append|insert for the routers instantiated

//     virtual TopologyType topologyType() const = 0; // Identify the NoC topology type

    INoC(sc_module_name mn,unsigned short nInterfaces);

    ModuleType moduleType() const { return SoCINModule::TNoC; }

    ~INoC() = 0;
};

inline INoC::~INoC(){}

inline INoC::INoC(sc_module_name mn, unsigned short nInterfaces)
    : SoCINModule(mn), numInterfaces(nInterfaces),
      i_CLK("INoC_iCLK"),
      i_RST("INoC_iRST"),
      i_DATA_IN("INoC_iDATA_IN",nInterfaces),
      i_VALID_IN("INoC_iVALID_IN",nInterfaces),
      o_RETURN_IN("INoC_oRETURN_IN",nInterfaces),
      o_DATA_OUT("INoC_oDATA_OUT",nInterfaces),
      o_VALID_OUT("INoC_oVALID_OUT",nInterfaces),
      i_RETURN_OUT("INoC_iRETURN_OUT",nInterfaces)
{}

#endif // __NOC_H__
