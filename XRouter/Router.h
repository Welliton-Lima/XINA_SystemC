#ifndef __IROUTER__H__
#define __IROUTER__H__

#include <systemc>
#include "../SoCINModule.h"

#define DATA_WIDTH 8

class IRouter : public SoCINModule{

public:
//------------CLOCK and RESET------------------------//
    sc_in<bool> i_CLK;
    sc_in<bool> i_RST;
//--------------------------------------------------//

//-----------LOCAL CHANNEL INTERFACE----------------//
    sc_in<sc_bv<DATA_WIDTH+1>>  i_IN_DATA_L;
    sc_in<bool>                 i_IN_VAL_L;
    sc_in<bool>                 i_OUT_ACK_L;

    sc_out<sc_bv<DATA_WIDTH+1>> o_OUT_DATA_L;
    sc_out<bool>                o_OUT_VAL_L;
    sc_out<bool>                o_IN_ACK_L;
//--------------------------------------------------//

//----------NORTH CHANNEL INTERFACE-----------------//
    sc_in<sc_bv<DATA_WIDTH+1>>  i_IN_DATA_N;
    sc_in<bool>                 i_IN_VAL_N;
    sc_in<bool>                 i_OUT_ACK_N;

    sc_out<sc_bv<DATA_WIDTH+1>> o_OUT_DATA_N;
    sc_out<bool>                o_OUT_VAL_N;
    sc_out<bool>                o_IN_ACK_N;

//--------------------------------------------------//

//-----------EAST CHANNEL INTERFACE-----------------//
    sc_in<sc_bv<DATA_WIDTH+1>>  i_IN_DATA_E;
    sc_in<bool>                 i_IN_VAL_E;
    sc_in<bool>                 i_OUT_ACK_E;


    sc_out<sc_bv<DATA_WIDTH+1>> o_OUT_DATA_E;
    sc_out<bool>                o_OUT_VAL_E;
    sc_out<bool>                o_IN_ACK_E;
//--------------------------------------------------//

//-----------SOUTH CHANNEL INTERFACE-----------------//
    sc_in<sc_bv<DATA_WIDTH+1>>  i_IN_DATA_S;
    sc_in<bool>                 i_IN_VAL_S;
    sc_in<bool>                 i_OUT_ACK_S;

    sc_out<sc_bv<DATA_WIDTH+1>> o_OUT_DATA_S;
    sc_out<bool>                o_OUT_VAL_S;
    sc_out<bool>                o_IN_ACK_S;
//--------------------------------------------------//

//-----------WEST CHANNEL INTERFACE-----------------//
    sc_in<sc_bv<DATA_WIDTH+1>>  i_IN_DATA_W;
    sc_in<bool>                 i_IN_VAL_W;
    sc_in<bool>                 i_OUT_ACK_W;

    sc_out<sc_bv<DATA_WIDTH+1>> o_OUT_DATA_W;
    sc_out<bool>                o_OUT_VAL_W;
    sc_out<bool>                o_IN_ACK_W;
//--------------------------------------------------//
    //-----------PARAMETERS-----------------------------//
    unsigned int ROUTER_ID_X;
    unsigned int ROUTER_ID_Y;
    int L_ENA;
    int N_ENA;
    int E_ENA;
    int S_ENA;
    int W_ENA;
    bool FLOW_MODE;
    bool ROUTING_MODE;
    bool ARBITER_MODE;
    bool BUFFER_MODE;


//--------------CONSTRUCTOR------------------------//
    IRouter(sc_module_name mn, unsigned int ROUTER_ID_X,
                                unsigned int ROUTER_ID_Y,
                                int L_ENA,
                                int N_ENA,
                                int E_ENA,
                                int S_ENA,
                                int W_ENA,
                                bool FLOW_MODE,
                                bool ROUTING_MODE,
                                bool ARBITER_MODE,
                                bool BUFFER_MODE)
                                :SoCINModule(mn),ROUTER_ID_X(ROUTER_ID_X),ROUTER_ID_Y(ROUTER_ID_Y),L_ENA(L_ENA),N_ENA(N_ENA),E_ENA(E_ENA),S_ENA(S_ENA),W_ENA(W_ENA),
                                FLOW_MODE(FLOW_MODE),ROUTING_MODE(ROUTING_MODE),ARBITER_MODE(ARBITER_MODE),BUFFER_MODE(BUFFER_MODE),
                                i_CLK("IRouter_i_CLK"),
                                i_RST("IRouter_i_RST"),
                                i_IN_DATA_L("IRouter_i_IN_DATA_L"),
                                i_IN_VAL_L("IRouter_i_IN_VAL_L"),
                                i_OUT_ACK_L("IRouter_i_OUT_ACK_L"),
                                o_OUT_DATA_L("IRouter_o_OUT_DATA_L"),
                                o_OUT_VAL_L("IRouter_o_OUT_VAL_L"),
                                o_IN_ACK_L("IRouter_o_IN_ACK_L"),
                                i_IN_DATA_N("IRouter_i_IN_DATA_N"),
                                i_IN_VAL_N("IRouter_i_IN_VAL_N"),
                                i_OUT_ACK_N("IRouter_i_OUT_ACK_N"),
                                o_OUT_DATA_N("IRouter_o_OUT_DATA_N"),
                                o_OUT_VAL_N("IRouter_o_OUT_VAL_N"),
                                o_IN_ACK_N("IRouter_o_IN_ACK_N"),
                                i_IN_DATA_E("IRouter_i_IN_DATA_E"),
                                i_IN_VAL_E("IRouter_i_IN_VAL_E"),
                                i_OUT_ACK_E("IRouter_i_OUT_ACK_E"),
                                o_OUT_DATA_E("IRouter_o_OUT_DATA_E"),
                                o_OUT_VAL_E("IRouter_o_OUT_VAL_E"),
                                o_IN_ACK_E("IRouter_i_o_IN_ACK_E"),
                                i_IN_DATA_S("IRouter_i_IN_DATA_S"),
                                i_IN_VAL_S("IRouter_i_IN_VAL_S"),
                                i_OUT_ACK_S("IRouter_i_OUT_ACK_S"),
                                o_OUT_DATA_S("IRouter_o_OUT_DATA_S"),
                                o_OUT_VAL_S("IRouter_o_OUT_VAL_S"),
                                o_IN_ACK_S("IRouter_o_IN_ACK_S"),
                                i_IN_DATA_W("IRouter_i_IN_DATA_W"),
                                i_IN_VAL_W("IRouter_i_IN_VAL_W"),
                                i_OUT_ACK_W("IRouter_i_OUT_ACK_W"),
                                o_OUT_DATA_W("IRouter_o_OUT_DATA_W"),
                                o_OUT_VAL_W("IRouter_o_OUT_VAL_W"),
                                o_IN_ACK_W("IRouter_o_IN_ACK_W"){}

    ModuleType moduleType() const { return SoCINModule::TRouter; }

    ~IRouter()=0;

};

inline IRouter::~IRouter(){}
#endif //__IROUTER__H__
