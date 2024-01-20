#ifndef __XINA_ROUTER__H__
#define __XINA_ROUTER__H__

#include <systemc>

#include "Router.h"
#include "../XChannel_in/Channel_in.h"
#include "../XChannel_out/Channel_out.h"
#include "../XCrossbar/crossbar.h"

class XINA_Router : public IRouter{
public:

//--------------------------------CHANNELS IN------------------------------------------------//
    Channel_in  *u_CIN_L;
    Channel_in  *u_CIN_N;
    Channel_in  *u_CIN_E;
    Channel_in  *u_CIN_S;
    Channel_in  *u_CIN_W;

//--------------------------------CHANNELS OUT------------------------------------------------//
    Channel_out  *u_COUT_L;
    Channel_out  *u_COUT_N;
    Channel_out  *u_COUT_E;
    Channel_out  *u_COUT_S;
    Channel_out  *u_COUT_W;

//---------CROSSBAR---------------
    Crossbar *u_Crossbar;

//--------------------------------SIGNALS------------------------------------------------------//

//------------------------------CHANNEL L WIRE---------------------------------------//

    //__________________REQUISITION_____________________________//
        sc_signal<bool>              w_L_REQ_N_XIN;
        sc_signal<bool>              w_L_REQ_E_XIN;
        sc_signal<bool>              w_L_REQ_S_XIN;
        sc_signal<bool>              w_L_REQ_W_XIN;

        sc_signal<bool>              w_L_REQ_N_XOUT;
        sc_signal<bool>              w_L_REQ_E_XOUT;
        sc_signal<bool>              w_L_REQ_S_XOUT;
        sc_signal<bool>              w_L_REQ_W_XOUT;

    //_____________________GRANTS_____________________________//
        sc_signal<bool>              w_L_GNT_N_XIN;
        sc_signal<bool>              w_L_GNT_E_XIN;
        sc_signal<bool>              w_L_GNT_S_XIN;
        sc_signal<bool>              w_L_GNT_W_XIN;

        sc_signal<bool>              w_L_GNT_N_XOUT;
        sc_signal<bool>              w_L_GNT_E_XOUT;
        sc_signal<bool>              w_L_GNT_S_XOUT;
        sc_signal<bool>              w_L_GNT_W_XOUT;

        sc_signal<bool>              w_L_ROK;
        sc_signal<bool>              w_L_RD;
        sc_signal<sc_bv<DATA_WIDTH+1>>   w_L_DATA;

//------------------------//---------------------//---------------------------//

//------------------------------CHANNEL N WIRE---------------------------------------//

    //__________________REQUISITION_____________________________//
        sc_signal<bool>              w_N_REQ_L_XIN;
        sc_signal<bool>              w_N_REQ_E_XIN;
        sc_signal<bool>              w_N_REQ_S_XIN;
        sc_signal<bool>              w_N_REQ_W_XIN;

        sc_signal<bool>              w_N_REQ_L_XOUT;
        sc_signal<bool>              w_N_REQ_E_XOUT;
        sc_signal<bool>              w_N_REQ_S_XOUT;
        sc_signal<bool>              w_N_REQ_W_XOUT;

    //_____________________GRANTS_____________________________//
        sc_signal<bool>              w_N_GNT_L_XIN;
        sc_signal<bool>              w_N_GNT_E_XIN;
        sc_signal<bool>              w_N_GNT_S_XIN;
        sc_signal<bool>              w_N_GNT_W_XIN;

        sc_signal<bool>              w_N_GNT_L_XOUT;
        sc_signal<bool>              w_N_GNT_E_XOUT;
        sc_signal<bool>              w_N_GNT_S_XOUT;
        sc_signal<bool>              w_N_GNT_W_XOUT;

        sc_signal<bool>              w_N_ROK;
        sc_signal<bool>              w_N_RD;
        sc_signal<sc_bv<DATA_WIDTH+1>>   w_N_DATA;

//------------------------//---------------------//---------------------------//

//------------------------------CHANNEL E WIRE---------------------------------------//

    //__________________REQUISITION_____________________________//
        sc_signal<bool>               w_E_REQ_L_XIN;
        sc_signal<bool>               w_E_REQ_N_XIN;
        sc_signal<bool>               w_E_REQ_S_XIN;
        sc_signal<bool>               w_E_REQ_W_XIN;

        sc_signal<bool>               w_E_REQ_L_XOUT;
        sc_signal<bool>               w_E_REQ_N_XOUT;
        sc_signal<bool>               w_E_REQ_S_XOUT;
        sc_signal<bool>               w_E_REQ_W_XOUT;

    //_____________________GRANTS_____________________________//
        sc_signal<bool>               w_E_GNT_L_XIN;
        sc_signal<bool>               w_E_GNT_N_XIN;
        sc_signal<bool>               w_E_GNT_S_XIN;
        sc_signal<bool>               w_E_GNT_W_XIN;

        sc_signal<bool>               w_E_GNT_L_XOUT;
        sc_signal<bool>               w_E_GNT_N_XOUT;
        sc_signal<bool>               w_E_GNT_S_XOUT;
        sc_signal<bool>               w_E_GNT_W_XOUT;

        sc_signal<bool>               w_E_ROK;
        sc_signal<bool>               w_E_RD;
        sc_signal<sc_bv<DATA_WIDTH+1>>    w_E_DATA;

//------------------------//---------------------//---------------------------//

//------------------------------CHANNEL S WIRE---------------------------------------//

    //__________________REQUISITION_____________________________//
        sc_signal<bool>              w_S_REQ_L_XIN;
        sc_signal<bool>              w_S_REQ_N_XIN;
        sc_signal<bool>              w_S_REQ_E_XIN;
        sc_signal<bool>              w_S_REQ_W_XIN;

        sc_signal<bool>              w_S_REQ_L_XOUT;
        sc_signal<bool>              w_s_REQ_N_XOUT;
        sc_signal<bool>              w_S_REQ_E_XOUT;
        sc_signal<bool>              w_S_REQ_W_XOUT;

   //_____________________GRANTS_____________________________//
        sc_signal<bool>              w_S_GNT_L_XIN;
        sc_signal<bool>              w_S_GNT_N_XIN;
        sc_signal<bool>              w_S_GNT_E_XIN;
        sc_signal<bool>              w_S_GNT_W_XIN;

        sc_signal<bool>              w_S_GNT_L_XOUT;
        sc_signal<bool>              w_S_GNT_N_XOUT;
        sc_signal<bool>              w_S_GNT_E_XOUT;
        sc_signal<bool>              w_S_GNT_W_XOUT;

        sc_signal<bool>              w_S_ROK;
        sc_signal<bool>              w_S_RD;
        sc_signal<sc_bv<DATA_WIDTH+1>>   w_S_DATA;


//------------------------//---------------------//---------------------------//

//------------------------------CHANNEL W WIRE---------------------------------------//
        //__________________REQUISITION_____________________________//
        sc_signal<bool>              w_W_REQ_L_XIN;
        sc_signal<bool>              w_W_REQ_N_XIN;
        sc_signal<bool>              w_W_REQ_E_XIN;
        sc_signal<bool>              w_W_REQ_S_XIN;

        sc_signal<bool>              w_W_REQ_L_XOUT;
        sc_signal<bool>              w_W_REQ_N_XOUT;
        sc_signal<bool>              w_W_REQ_E_XOUT;
        sc_signal<bool>              w_W_REQ_S_XOUT;

  //_____________________GRANTS_____________________________//
        sc_signal<bool>              w_W_GNT_L_XIN;
        sc_signal<bool>              w_W_GNT_N_XIN;
        sc_signal<bool>              w_W_GNT_E_XIN;
        sc_signal<bool>              w_W_GNT_S_XIN;

        sc_signal<bool>              w_W_GNT_L_XOUT;
        sc_signal<bool>              w_W_GNT_N_XOUT;
        sc_signal<bool>              w_W_GNT_E_XOUT;
        sc_signal<bool>              w_W_GNT_S_XOUT;

        sc_signal<bool>              w_W_ROK;
        sc_signal<bool>              w_W_RD;
        sc_signal<sc_bv<DATA_WIDTH+1>>   w_W_DATA;

//____________________________TEMP SIGNALS__________________________________________________//
        sc_bv<4> w_IN_GNT_L, w_IN_RD_L, w_IN_ROK_L, w_IN_REQ_L;
        sc_bv<4> w_IN_GNT_N, w_IN_RD_N, w_IN_ROK_N, w_IN_REQ_N;
        sc_bv<4> w_IN_GNT_E, w_IN_RD_E, w_IN_ROK_E, w_IN_REQ_E;
        sc_bv<4> w_IN_GNT_S, w_IN_RD_S, w_IN_ROK_S, w_IN_REQ_S;
        sc_bv<4> w_IN_GNT_W, w_IN_RD_W, w_IN_ROK_W, w_IN_REQ_W;

        sc_signal<bool> OPEN_L, OPEN_N, OPEN_E, OPEN_S, OPEN_W;

        sc_signal<sc_bv<4>> w_i_GNT_L, w_i_RD_L, w_o_GNT_L, w_i_ROK_L, w_i_REQ_L;
        sc_signal<sc_bv<4>> w_i_GNT_N, w_i_RD_N, w_o_GNT_N, w_i_ROK_N, w_i_REQ_N;
        sc_signal<sc_bv<4>> w_i_GNT_S, w_i_RD_S, w_o_GNT_S, w_i_ROK_S, w_i_REQ_S;
        sc_signal<sc_bv<4>> w_i_GNT_E, w_i_RD_E, w_o_GNT_E, w_i_ROK_E, w_i_REQ_E;
        sc_signal<sc_bv<4>> w_i_GNT_W, w_i_RD_W, w_o_GNT_W, w_i_ROK_W, w_i_REQ_W;

        void connections();

        SC_HAS_PROCESS(XINA_Router);
        XINA_Router(sc_module_name mn,unsigned int ROUTER_ID_X,
                                                unsigned int ROUTER_ID_Y,
                                                int L_ENA,
                                                int N_ENA,
                                                int E_ENA,
                                                int S_ENA,
                                                int W_ENA,
                                                bool FLOW_MODE,
                                                bool ROUTING_MODE,
                                                bool ARBITER_MODE,
                                                bool BUFFER_MODE);

        const char* moduleName() const { return "XINA_Router"; }

    ~XINA_Router();

};

//--------CONSTRUCTOR--------//

inline XINA_Router::XINA_Router(sc_module_name mn, unsigned int ROUTER_ID_X,
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
                                        :IRouter(mn, ROUTER_ID_X,ROUTER_ID_Y,L_ENA,N_ENA,E_ENA,S_ENA,W_ENA,FLOW_MODE,ROUTING_MODE,ARBITER_MODE,BUFFER_MODE)
{
        SC_METHOD(connections);
        sensitive <<i_CLK<< i_RST <<
                        w_N_GNT_L_XIN <<
                        w_E_GNT_L_XIN <<
                        w_S_GNT_L_XIN <<
                        w_W_GNT_L_XIN <<

                        w_L_RD <<
                        w_N_RD <<
                        w_E_RD <<
                        w_S_RD <<
                        w_W_RD <<

                        w_N_REQ_L_XOUT <<
                        w_E_REQ_L_XOUT <<
                        w_S_REQ_L_XOUT <<
                        w_W_REQ_L_XOUT <<

                        w_L_ROK <<
                        w_N_ROK <<
                        w_E_ROK <<
                        w_S_ROK <<
                        w_W_ROK <<

                        w_L_GNT_N_XOUT <<
                        w_L_GNT_E_XOUT <<
                        w_L_GNT_S_XOUT <<
                        w_L_GNT_W_XOUT <<

                        //---------------Siganls North channel----------------------------//
                        w_L_GNT_N_XIN <<
                        w_E_GNT_N_XIN <<
                        w_S_GNT_N_XIN <<
                        w_W_GNT_N_XIN <<

                        w_L_REQ_N_XOUT <<
                        w_E_REQ_N_XOUT <<
                        w_s_REQ_N_XOUT <<
                        w_W_REQ_N_XOUT <<

                        w_N_GNT_L_XOUT <<
                        w_N_GNT_E_XOUT <<
                        w_N_GNT_S_XOUT <<
                        w_N_GNT_W_XOUT <<

                        //---------------Siganls East channel----------------------------//
                        w_L_GNT_E_XIN <<
                        w_N_GNT_E_XIN <<
                        w_S_GNT_E_XIN <<
                        w_W_GNT_E_XIN <<

                        w_L_REQ_E_XOUT <<
                        w_N_REQ_E_XOUT <<
                        w_S_REQ_E_XOUT <<
                        w_W_REQ_E_XOUT <<

                        w_E_GNT_L_XOUT <<
                        w_E_GNT_N_XOUT <<
                        w_E_GNT_S_XOUT <<
                        w_E_GNT_W_XOUT <<


                        //---------------Siganls South channel----------------------------//
                        w_L_GNT_S_XIN <<
                        w_N_GNT_S_XIN <<
                        w_E_GNT_S_XIN <<
                        w_W_GNT_S_XIN <<

                        w_L_REQ_S_XOUT <<
                        w_N_REQ_S_XOUT <<
                        w_E_REQ_S_XOUT <<
                        w_W_REQ_S_XOUT <<

                        w_S_GNT_L_XOUT <<
                        w_S_GNT_N_XOUT <<
                        w_S_GNT_E_XOUT <<
                        w_S_GNT_W_XOUT <<

                        //---------------Siganls West channel----------------------------//
                        w_L_GNT_W_XIN <<
                        w_N_GNT_W_XIN <<
                        w_E_GNT_W_XIN <<
                        w_S_GNT_W_XIN <<

                        w_L_REQ_W_XOUT <<
                        w_N_REQ_W_XOUT <<
                        w_E_REQ_W_XOUT <<
                        w_S_REQ_W_XOUT <<

                        w_W_GNT_L_XOUT <<
                        w_W_GNT_N_XOUT <<
                        w_W_GNT_E_XOUT <<
                        w_W_GNT_S_XOUT;


//----------------LOCAL-------------------------------------------------------------------------------------------
        //---------LOCAL IN--------------------------------------------------------------------------
        u_CIN_L = new Channel_in ("u_CIN_L",L_ENA,FLOW_MODE,ROUTING_MODE,BUFFER_MODE,ROUTER_ID_X,ROUTER_ID_Y);

        u_CIN_L->i_CLK   (i_CLK);
        u_CIN_L->i_RST   (i_RST);
        u_CIN_L->i_DATA  (i_IN_DATA_L);
        u_CIN_L->i_VAL   (i_IN_VAL_L);
        u_CIN_L->o_ACK   (o_IN_ACK_L);
        u_CIN_L->o_L_REQ (OPEN_L);
        u_CIN_L->o_N_REQ (w_L_REQ_N_XIN);
        u_CIN_L->o_E_REQ (w_L_REQ_E_XIN);
        u_CIN_L->o_S_REQ (w_L_REQ_S_XIN);
        u_CIN_L->o_W_REQ (w_L_REQ_W_XIN);
        u_CIN_L->i_GNT   (w_i_GNT_L);
        u_CIN_L->o_ROK   (w_L_ROK);
        u_CIN_L->i_RD    (w_i_RD_L);
        u_CIN_L->o_DATA  (w_L_DATA);


        //---------LOCAL OUT--------------------------------------------------------------------------
        u_COUT_L = new Channel_out("u_COUT_L",L_ENA,FLOW_MODE,ARBITER_MODE);

        u_COUT_L->i_CLK(i_CLK);
        u_COUT_L->i_RST(i_RST);
        u_COUT_L->o_DATA(o_OUT_DATA_L);
        u_COUT_L->o_VAL(o_OUT_VAL_L);
        u_COUT_L->i_ACK(i_OUT_ACK_L);
        u_COUT_L->i_REQ(w_i_REQ_L);
        u_COUT_L->o_GNT(w_o_GNT_L);
        u_COUT_L->i_ROK(w_i_ROK_L);
        u_COUT_L->o_RD(w_L_RD);
        u_COUT_L->i_DATA3(w_N_DATA);
        u_COUT_L->i_DATA2(w_E_DATA);
        u_COUT_L->i_DATA1(w_S_DATA);
        u_COUT_L->i_DATA0(w_W_DATA);

//----------------NORTH-------------------------------------------------------------------------------------------
        //---------NORTH IN-----------------------------------------//
        u_CIN_N = new Channel_in ("u_CIN_N",N_ENA,FLOW_MODE,ROUTING_MODE,BUFFER_MODE,ROUTER_ID_X,ROUTER_ID_Y);

        u_CIN_N->i_CLK(i_CLK);
        u_CIN_N->i_RST(i_RST);
        u_CIN_N->i_DATA(i_IN_DATA_N);
        u_CIN_N->i_VAL(i_IN_VAL_N);
        u_CIN_N->o_ACK(o_IN_ACK_N);
        u_CIN_N->o_L_REQ(w_N_REQ_L_XIN);
        u_CIN_N->o_N_REQ(OPEN_N);
        u_CIN_N->o_E_REQ(w_N_REQ_E_XIN);
        u_CIN_N->o_S_REQ(w_N_REQ_S_XIN);
        u_CIN_N->o_W_REQ(w_N_REQ_W_XIN);
        u_CIN_N->i_GNT(w_i_GNT_N);
        u_CIN_N->o_ROK(w_N_ROK);
        u_CIN_N->i_RD(w_i_RD_N);
        u_CIN_N->o_DATA(w_N_DATA);

        //---------NORTH OUT-------------------------------------//
        u_COUT_N = new Channel_out("u_COUT_N",N_ENA,FLOW_MODE,ARBITER_MODE);

        u_COUT_N->i_CLK(i_CLK);
        u_COUT_N->i_RST(i_RST);
        u_COUT_N->o_DATA(o_OUT_DATA_N);
        u_COUT_N->o_VAL(o_OUT_VAL_N);
        u_COUT_N->i_ACK(i_OUT_ACK_N);
        u_COUT_N->i_REQ(w_i_REQ_N);
        u_COUT_N->o_GNT(w_o_GNT_N);
        u_COUT_N->i_ROK(w_i_ROK_N);
        u_COUT_N->o_RD(w_N_RD);
        u_COUT_N->i_DATA3(w_L_DATA);
        u_COUT_N->i_DATA2(w_E_DATA);
        u_COUT_N->i_DATA1(w_S_DATA);
        u_COUT_N->i_DATA0(w_W_DATA);

//----------------EAST-------------------------------------------------------------------------------------------
        //---------EAST IN--------------------------------------------------------------------------
        u_CIN_E = new Channel_in("u_CIN_E",E_ENA,FLOW_MODE,ROUTING_MODE,BUFFER_MODE,ROUTER_ID_X,ROUTER_ID_Y);

        u_CIN_E->i_CLK(i_CLK);
        u_CIN_E->i_RST(i_RST);
        u_CIN_E->i_DATA(i_IN_DATA_E);
        u_CIN_E->i_VAL(i_IN_VAL_E);
        u_CIN_E->o_ACK(o_IN_ACK_E);
        u_CIN_E->o_L_REQ(w_E_REQ_L_XIN);
        u_CIN_E->o_N_REQ(w_E_REQ_N_XIN);
        u_CIN_E->o_E_REQ(OPEN_E);
        u_CIN_E->o_S_REQ(w_E_REQ_S_XIN);
        u_CIN_E->o_W_REQ(w_E_REQ_W_XIN);
        u_CIN_E->i_GNT(w_i_GNT_E);
        u_CIN_E->i_RD(w_i_RD_E);
        u_CIN_E->o_ROK(w_E_ROK);
        u_CIN_E->o_DATA(w_E_DATA);

        //---------EAST OUT--------------------------------------------------------------------------
        u_COUT_E = new Channel_out("u_COUT_E",E_ENA,FLOW_MODE,ARBITER_MODE);

        u_COUT_E->i_CLK(i_CLK);
        u_COUT_E->i_RST(i_RST);
        u_COUT_E->o_DATA(o_OUT_DATA_E);
        u_COUT_E->o_VAL(o_OUT_VAL_E);
        u_COUT_E->i_ACK(i_OUT_ACK_E);
        u_COUT_E->i_REQ(w_i_REQ_E);
        u_COUT_E->o_GNT(w_o_GNT_E);
        u_COUT_E->i_ROK(w_i_ROK_E);
        u_COUT_E->o_RD(w_E_RD);
        u_COUT_E->i_DATA3(w_L_DATA);
        u_COUT_E->i_DATA2(w_N_DATA);
        u_COUT_E->i_DATA1(w_S_DATA);
        u_COUT_E->i_DATA0(w_W_DATA);

//----------------SOUTH-------------------------------------------------------------------------------------------
        //---------SOUTH IN--------------------------------------------------------------------------
        u_CIN_S = new Channel_in("u_CIN_S",S_ENA,FLOW_MODE,ROUTING_MODE,BUFFER_MODE,ROUTER_ID_X,ROUTER_ID_Y);

        u_CIN_S->i_CLK(i_CLK);
        u_CIN_S->i_RST(i_RST);
        u_CIN_S->i_DATA(i_IN_DATA_S);
        u_CIN_S->i_VAL(i_IN_VAL_S);
        u_CIN_S->o_ACK(o_IN_ACK_S);
        u_CIN_S->o_L_REQ(w_S_REQ_L_XIN);
        u_CIN_S->o_N_REQ(w_S_REQ_N_XIN);
        u_CIN_S->o_E_REQ(w_S_REQ_E_XIN);
        u_CIN_S->o_S_REQ(OPEN_S);
        u_CIN_S->o_W_REQ(w_S_REQ_W_XIN);
        u_CIN_S->i_GNT(w_i_GNT_S);
        u_CIN_S->i_RD(w_i_RD_S);
        u_CIN_S->o_ROK(w_S_ROK);
        u_CIN_S->o_DATA(w_S_DATA);

        //---------SOUTH OUT--------------------------------------------------------------------------
        u_COUT_S = new  Channel_out("u_COUT_S",S_ENA,FLOW_MODE,ARBITER_MODE);

        u_COUT_S->i_CLK(i_CLK);
        u_COUT_S->i_RST(i_RST);
        u_COUT_S->o_DATA(o_OUT_DATA_S);
        u_COUT_S->o_VAL(o_OUT_VAL_S);
        u_COUT_S->i_ACK(i_OUT_ACK_S);
        u_COUT_S->i_REQ(w_i_REQ_S);
        u_COUT_S->o_GNT(w_o_GNT_S);
        u_COUT_S->i_ROK(w_i_ROK_S);
        u_COUT_S->o_RD(w_S_RD);
        u_COUT_S->i_DATA3(w_L_DATA);
        u_COUT_S->i_DATA2(w_N_DATA);
        u_COUT_S->i_DATA1(w_E_DATA);
        u_COUT_S->i_DATA0(w_W_DATA);

//----------------WEST-------------------------------------------------------------------------------------------
        //---------WEST IN--------------------------------------------------------------------------

        u_CIN_W = new Channel_in("u_CIN_W",W_ENA,FLOW_MODE,ROUTING_MODE,BUFFER_MODE,ROUTER_ID_X,ROUTER_ID_Y);

        u_CIN_W->i_CLK(i_CLK);
        u_CIN_W->i_RST(i_RST);
        u_CIN_W->i_DATA(i_IN_DATA_W);
        u_CIN_W->i_VAL(i_IN_VAL_W);
        u_CIN_W->o_ACK(o_IN_ACK_W);
        u_CIN_W->o_L_REQ(w_W_REQ_L_XIN);
        u_CIN_W->o_N_REQ(w_W_REQ_N_XIN);
        u_CIN_W->o_E_REQ(w_W_REQ_E_XIN);
        u_CIN_W->o_S_REQ(w_W_REQ_S_XIN);
        u_CIN_W->o_W_REQ(OPEN_W);
        u_CIN_W->i_GNT(w_i_GNT_W);
        u_CIN_W->o_ROK(w_W_ROK);
        u_CIN_W->i_RD(w_i_RD_W);
        u_CIN_W->o_DATA(w_W_DATA);

        //---------WEST OUT--------------------------------------------------------------------------
        u_COUT_W = new Channel_out("u_COUT_W",W_ENA,FLOW_MODE,ARBITER_MODE);

        u_COUT_W->i_CLK(i_CLK);
        u_COUT_W->i_RST(i_RST);
        u_COUT_W->o_DATA(o_OUT_DATA_W);
        u_COUT_W->o_VAL(o_OUT_VAL_W);
        u_COUT_W->i_ACK(i_OUT_ACK_W);
        u_COUT_W->i_REQ(w_i_REQ_W);
        u_COUT_W->o_GNT(w_o_GNT_W);
        u_COUT_W->o_RD(w_W_RD);
        u_COUT_W->i_ROK(w_i_ROK_W);
        u_COUT_W->i_DATA3(w_L_DATA);
        u_COUT_W->i_DATA2(w_N_DATA);
        u_COUT_W->i_DATA1(w_E_DATA);
        u_COUT_W->i_DATA0(w_S_DATA);

//----------------CROSSBAR----------------------------------------------------------------------------//

        u_Crossbar = new Crossbar("u_Crossbar");

//______________________________REQUISITION____________________________________________//

    //-----------LOCAL IN -----------------------//
        u_Crossbar->i_L_REQ_N(w_L_REQ_N_XIN);
        u_Crossbar->i_L_REQ_E(w_L_REQ_E_XIN);
        u_Crossbar->i_L_REQ_S(w_L_REQ_S_XIN);
        u_Crossbar->i_L_REQ_W(w_L_REQ_W_XIN);

    //------------LOCAL OUT-----------------------//
        u_Crossbar->o_L_REQ_N(w_L_REQ_N_XOUT);
        u_Crossbar->o_L_REQ_E(w_L_REQ_E_XOUT);
        u_Crossbar->o_L_REQ_S(w_L_REQ_S_XOUT);
        u_Crossbar->o_L_REQ_W(w_L_REQ_W_XOUT);

//-----------------------------------------------------------//
     //---------------NORTH IN---------------------//
        u_Crossbar->i_N_REQ_L(w_N_REQ_L_XIN);
        u_Crossbar->i_N_REQ_E(w_N_REQ_E_XIN);
        u_Crossbar->i_N_REQ_S(w_N_REQ_S_XIN);
        u_Crossbar->i_N_REQ_W(w_N_REQ_W_XIN);

     //--------------NORTH OUT---------------------//
        u_Crossbar->o_N_REQ_L(w_N_REQ_L_XOUT);
        u_Crossbar->o_N_REQ_E(w_N_REQ_E_XOUT);
        u_Crossbar->o_N_REQ_S(w_N_REQ_S_XOUT);
        u_Crossbar->o_N_REQ_W(w_N_REQ_W_XOUT);

//-----------------------------------------------------------//

        //--------EAST IN-----------------------
        u_Crossbar->i_E_REQ_L(w_E_REQ_L_XIN);
        u_Crossbar->i_E_REQ_N(w_E_REQ_N_XIN);
        u_Crossbar->i_E_REQ_S(w_E_REQ_S_XIN);
        u_Crossbar->i_E_REQ_W(w_E_REQ_W_XIN);

        //--------EAST OUT---------------------
        u_Crossbar->o_E_REQ_L(w_E_REQ_L_XOUT);
        u_Crossbar->o_E_REQ_N(w_E_REQ_N_XOUT);
        u_Crossbar->o_E_REQ_S(w_E_REQ_S_XOUT);
        u_Crossbar->o_E_REQ_W(w_E_REQ_W_XOUT);

//-----------------------------------------------------------//
        //--------SOUTH IN---------------------
        u_Crossbar->i_S_REQ_L(w_S_REQ_L_XIN);
        u_Crossbar->i_S_REQ_N(w_S_REQ_N_XIN);
        u_Crossbar->i_S_REQ_E(w_S_REQ_E_XIN);
        u_Crossbar->i_S_REQ_W(w_S_REQ_W_XIN);

        //-------WEST OUT----------------------
        u_Crossbar->o_S_REQ_L(w_S_REQ_L_XOUT);
        u_Crossbar->o_S_REQ_N(w_s_REQ_N_XOUT);
        u_Crossbar->o_S_REQ_E(w_S_REQ_E_XOUT);
        u_Crossbar->o_S_REQ_W(w_S_REQ_W_XOUT);

//-----------------------------------------------------------//
        //-------WEST IN---------------------
        u_Crossbar->i_W_REQ_L(w_W_REQ_L_XIN);
        u_Crossbar->i_W_REQ_N(w_W_REQ_N_XIN);
        u_Crossbar->i_W_REQ_E(w_W_REQ_E_XIN);
        u_Crossbar->i_W_REQ_S(w_W_REQ_S_XIN);

        //-------WEST OUT---------------------
        u_Crossbar->o_W_REQ_L(w_W_REQ_L_XOUT);
        u_Crossbar->o_W_REQ_N(w_W_REQ_N_XOUT);
        u_Crossbar->o_W_REQ_E(w_W_REQ_E_XOUT);
        u_Crossbar->o_W_REQ_S(w_W_REQ_S_XOUT);

//---------------------------------GRANTS--------------------------------------------//

        //--------LOCAL GRANT OUT-----------
        u_Crossbar->i_L_GNT_N(w_L_GNT_N_XOUT);
        u_Crossbar->i_L_GNT_E(w_L_GNT_E_XOUT);
        u_Crossbar->i_L_GNT_S(w_L_GNT_S_XOUT);
        u_Crossbar->i_L_GNT_W(w_L_GNT_W_XOUT);

        //--------LOCAL GRANT IN------------
        u_Crossbar->o_L_GNT_N(w_L_GNT_N_XIN);
        u_Crossbar->o_L_GNT_E(w_L_GNT_E_XIN);
        u_Crossbar->o_L_GNT_S(w_L_GNT_S_XIN);
        u_Crossbar->o_L_GNT_W(w_L_GNT_W_XIN);

//-----------------------------------------------------------//
        //--------NORTH GRANT OUT------------
        u_Crossbar->i_N_GNT_L(w_N_GNT_L_XOUT);
        u_Crossbar->i_N_GNT_E(w_N_GNT_E_XOUT);
        u_Crossbar->i_N_GNT_S(w_N_GNT_S_XOUT);
        u_Crossbar->i_N_GNT_W(w_N_GNT_W_XOUT);

        //--------NORTH GRANT IN------------
        u_Crossbar->o_N_GNT_L(w_N_GNT_L_XIN);
        u_Crossbar->o_N_GNT_E(w_N_GNT_E_XIN);
        u_Crossbar->o_N_GNT_S(w_N_GNT_S_XIN);
        u_Crossbar->o_N_GNT_W(w_N_GNT_W_XIN);

//-----------------------------------------------------------//
        //--------EAST GRANT OUT------------
        u_Crossbar->i_E_GNT_L(w_E_GNT_L_XOUT);
        u_Crossbar->i_E_GNT_N(w_E_GNT_N_XOUT);
        u_Crossbar->i_E_GNT_S(w_E_GNT_S_XOUT);
        u_Crossbar->i_E_GNT_W(w_E_GNT_W_XOUT);

        //--------EAST GRANT IN--------------
        u_Crossbar->o_E_GNT_L(w_E_GNT_L_XIN);
        u_Crossbar->o_E_GNT_N(w_E_GNT_N_XIN);
        u_Crossbar->o_E_GNT_S(w_E_GNT_S_XIN);
        u_Crossbar->o_E_GNT_W(w_E_GNT_W_XIN);

//-----------------------------------------------------------//
        //--------SOUTH GRANT OUT------------
        u_Crossbar->i_S_GNT_L(w_S_GNT_L_XOUT);
        u_Crossbar->i_S_GNT_N(w_S_GNT_N_XOUT);
        u_Crossbar->i_S_GNT_E(w_S_GNT_E_XOUT);
        u_Crossbar->i_S_GNT_W(w_S_GNT_W_XOUT);

        //--------SOUTH GRANT IN------------
        u_Crossbar->o_S_GNT_L(w_S_GNT_L_XIN);
        u_Crossbar->o_S_GNT_N(w_S_GNT_N_XIN);
        u_Crossbar->o_S_GNT_E(w_S_GNT_E_XIN);
        u_Crossbar->o_S_GNT_W(w_S_GNT_W_XIN);

//-----------------------------------------------------------//
        //--------WEST GRANT OUT------------
        u_Crossbar->i_W_GNT_L(w_W_GNT_L_XOUT);
        u_Crossbar->i_W_GNT_N(w_W_GNT_N_XOUT);
        u_Crossbar->i_W_GNT_E(w_W_GNT_E_XOUT);
        u_Crossbar->i_W_GNT_S(w_W_GNT_S_XOUT);

        //--------WEST GRANT IN------------
        u_Crossbar->o_W_GNT_L(w_W_GNT_L_XIN);
        u_Crossbar->o_W_GNT_N(w_W_GNT_N_XIN);
        u_Crossbar->o_W_GNT_E(w_W_GNT_E_XIN);
        u_Crossbar->o_W_GNT_S(w_W_GNT_S_XIN);

}


void XINA_Router::connections(){

//          cout<<"o_OUT_DATA_L: "<<o_OUT_DATA_L<<endl;

        //---------------Siganls local channel----------------------------//
        //---------Inputs---------//
        w_IN_GNT_L[3] = w_N_GNT_L_XIN.read();
        w_IN_GNT_L[2] = w_E_GNT_L_XIN.read();
        w_IN_GNT_L[1] = w_S_GNT_L_XIN.read();
        w_IN_GNT_L[0] = w_W_GNT_L_XIN.read();
        w_i_GNT_L.write(w_IN_GNT_L);

        w_IN_RD_L[3] = w_N_RD.read();
        w_IN_RD_L[2] = w_E_RD.read();
        w_IN_RD_L[1] = w_S_RD.read();
        w_IN_RD_L[0] = w_W_RD.read();
        w_i_RD_L.write(w_IN_RD_L);

        //-------------------Outputs-------------------------------------//
        w_IN_REQ_L[3] = w_N_REQ_L_XOUT.read();
        w_IN_REQ_L[2] = w_E_REQ_L_XOUT.read();
        w_IN_REQ_L[1] = w_S_REQ_L_XOUT.read();
        w_IN_REQ_L[0] = w_W_REQ_L_XOUT.read();
        w_i_REQ_L.write(w_IN_REQ_L);

        w_IN_ROK_L[3] = w_N_ROK.read();
        w_IN_ROK_L[2] = w_E_ROK.read();
        w_IN_ROK_L[1] = w_S_ROK.read();
        w_IN_ROK_L[0] = w_W_ROK.read();
        w_i_ROK_L.write(w_IN_ROK_L);

        w_L_GNT_N_XOUT.write(w_o_GNT_L.read().get_bit(3));
        w_L_GNT_E_XOUT.write(w_o_GNT_L.read().get_bit(2));
        w_L_GNT_S_XOUT.write(w_o_GNT_L.read().get_bit(1));
        w_L_GNT_W_XOUT.write(w_o_GNT_L.read().get_bit(0));


        //---------------Siganls North channel----------------------------//
        //---------Inputs---------//
        w_IN_GNT_N[3] = w_L_GNT_N_XIN.read();
        w_IN_GNT_N[2] = w_E_GNT_N_XIN.read();
        w_IN_GNT_N[1] = w_S_GNT_N_XIN.read();
        w_IN_GNT_N[0] = w_W_GNT_N_XIN.read();
        w_i_GNT_N.write(w_IN_GNT_N);

        w_IN_RD_N[3] = w_L_RD.read();
        w_IN_RD_N[2] = w_E_RD.read();
        w_IN_RD_N[1] = w_S_RD.read();
        w_IN_RD_N[0] = w_W_RD.read();
        w_i_RD_N.write(w_IN_RD_N);

        //-------------------Outputs-------------------------------------//
        w_IN_REQ_N[3] = w_L_REQ_N_XOUT.read();
        w_IN_REQ_N[2] = w_E_REQ_N_XOUT.read();
        w_IN_REQ_N[1] = w_s_REQ_N_XOUT.read();
        w_IN_REQ_N[0] = w_W_REQ_N_XOUT.read();
        w_i_REQ_N.write(w_IN_REQ_N);

        w_IN_ROK_N[3] = w_L_ROK.read();
        w_IN_ROK_N[2] = w_E_ROK.read();
        w_IN_ROK_N[1] = w_S_ROK.read();
        w_IN_ROK_N[0] = w_W_ROK.read();
        w_i_ROK_N.write(w_IN_ROK_N);

        w_N_GNT_L_XOUT.write(w_o_GNT_N.read().get_bit(3));
        w_N_GNT_E_XOUT.write(w_o_GNT_N.read().get_bit(2));
        w_N_GNT_S_XOUT.write(w_o_GNT_N.read().get_bit(1));
        w_N_GNT_W_XOUT.write(w_o_GNT_N.read().get_bit(0));

        //---------------Siganls East channel----------------------------//
        //---------Inputs---------//
        w_IN_GNT_E[3] = w_L_GNT_E_XIN.read();
        w_IN_GNT_E[2] = w_N_GNT_E_XIN.read();
        w_IN_GNT_E[1] = w_S_GNT_E_XIN.read();
        w_IN_GNT_E[0] = w_W_GNT_E_XIN.read();
        w_i_GNT_E.write(w_IN_GNT_E);

        w_IN_RD_E[3] = w_L_RD.read();
        w_IN_RD_E[2] = w_N_RD.read();
        w_IN_RD_E[1] = w_S_RD.read();
        w_IN_RD_E[0] = w_W_RD.read();
        w_i_RD_E.write(w_IN_RD_E);

        //---------Outputs-------------------------------------------------//
        w_IN_REQ_E[3] = w_L_REQ_E_XOUT.read();
        w_IN_REQ_E[2] = w_N_REQ_E_XOUT.read();
        w_IN_REQ_E[1] = w_S_REQ_E_XOUT.read();
        w_IN_REQ_E[0] = w_W_REQ_E_XOUT.read();
        w_i_REQ_E.write(w_IN_REQ_E);

        w_IN_ROK_E[3] = w_L_ROK.read();
        w_IN_ROK_E[2] = w_N_ROK.read();
        w_IN_ROK_E[1] = w_S_ROK.read();
        w_IN_ROK_E[0] = w_W_ROK.read();
        w_i_ROK_E.write(w_IN_ROK_E);

        w_E_GNT_L_XOUT.write(w_o_GNT_E.read().get_bit(3));
        w_E_GNT_N_XOUT.write(w_o_GNT_E.read().get_bit(2));
        w_E_GNT_S_XOUT.write(w_o_GNT_E.read().get_bit(1));
        w_E_GNT_W_XOUT.write(w_o_GNT_E.read().get_bit(0));


        //---------------Siganls South channel----------------------------//
        //---------Inputs---------//
        w_IN_GNT_S[3] = w_L_GNT_S_XIN.read();
        w_IN_GNT_S[2] = w_N_GNT_S_XIN.read();
        w_IN_GNT_S[1] = w_E_GNT_S_XIN.read();
        w_IN_GNT_S[0] = w_W_GNT_S_XIN.read();
        w_i_GNT_S.write(w_IN_GNT_S);

        w_IN_RD_S[3] = w_L_RD.read();
        w_IN_RD_S[2] = w_N_RD.read();
        w_IN_RD_S[1] = w_E_RD.read();
        w_IN_RD_S[0] = w_W_RD.read();
        w_i_RD_S.write(w_IN_RD_S);

        //---------Outputs---------//
        w_IN_REQ_S[3] = w_L_REQ_S_XOUT.read();
        w_IN_REQ_S[2] = w_N_REQ_S_XOUT.read();
        w_IN_REQ_S[1] = w_E_REQ_S_XOUT.read();
        w_IN_REQ_S[0] = w_W_REQ_S_XOUT.read();
        w_i_REQ_S.write(w_IN_REQ_S);

        w_IN_ROK_S[3] = w_L_ROK.read();
        w_IN_ROK_S[2] = w_N_ROK.read();
        w_IN_ROK_S[1] = w_E_ROK.read();
        w_IN_ROK_S[0] = w_W_ROK.read();
        w_i_ROK_S.write(w_IN_ROK_S);

        w_S_GNT_L_XOUT.write(w_o_GNT_S.read().get_bit(3));
        w_S_GNT_N_XOUT.write(w_o_GNT_S.read().get_bit(2));
        w_S_GNT_E_XOUT.write(w_o_GNT_S.read().get_bit(1));
        w_S_GNT_W_XOUT.write(w_o_GNT_S.read().get_bit(0));

        //---------------Siganls West channel----------------------------//
        //---------Inputs---------//
        w_IN_GNT_W[3] = w_L_GNT_W_XIN.read();
        w_IN_GNT_W[2] = w_N_GNT_W_XIN.read();
        w_IN_GNT_W[1] = w_E_GNT_W_XIN.read();
        w_IN_GNT_W[0] = w_S_GNT_W_XIN.read();
        w_i_GNT_W.write(w_IN_GNT_W);

        w_IN_RD_W[3] = w_L_RD.read();
        w_IN_RD_W[2] = w_N_RD.read();
        w_IN_RD_W[1] = w_E_RD.read();
        w_IN_RD_W[0] = w_S_RD.read();
        w_i_RD_W.write(w_IN_RD_W);


        //---------Outputs---------//
        w_IN_REQ_W[3] = w_L_REQ_W_XOUT.read();
        w_IN_REQ_W[2] = w_N_REQ_W_XOUT.read();
        w_IN_REQ_W[1] = w_E_REQ_W_XOUT.read();
        w_IN_REQ_W[0] = w_S_REQ_W_XOUT.read();
        w_i_REQ_W.write(w_IN_REQ_W);

        w_IN_ROK_W[3] = w_L_ROK.read();
        w_IN_ROK_W[2] = w_N_ROK.read();
        w_IN_ROK_W[1] = w_E_ROK.read();
        w_IN_ROK_W[0] = w_S_ROK.read();
        w_i_ROK_W.write(w_IN_ROK_W);

        w_W_GNT_L_XOUT.write(w_o_GNT_W.read().get_bit(3));
        w_W_GNT_N_XOUT.write(w_o_GNT_W.read().get_bit(2));
        w_W_GNT_E_XOUT.write(w_o_GNT_W.read().get_bit(1));
        w_W_GNT_S_XOUT.write(w_o_GNT_W.read().get_bit(0));

    }
inline XINA_Router::~XINA_Router(){
        delete  u_CIN_L;
        delete  u_CIN_N;
        delete  u_CIN_E;
        delete  u_CIN_S;
        delete  u_CIN_W;
        delete  u_COUT_L;
        delete  u_COUT_N;
        delete  u_COUT_E;
        delete  u_COUT_S;
        delete  u_COUT_W;
        delete  u_Crossbar;
}


#endif //__XINA_ROUTER__H__
