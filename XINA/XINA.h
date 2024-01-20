/*
----------------------------------------------------------------------------------------------
XINA - eXtensible Interconnect Network Architecture
----------------------------------------------------------------------------------------------
PROJECT: XINA_SystemC
MODULE : XINA - General module used by all others components
FILE   : XINA.h
---------------------------------------------------------------------------------------------
DESCRIPTION: Xina Network Topology Module
---------------------------------------------------------------------------------------------
AUTHORS: Laboratory of Embedded and Distributed Systems (LEDS - UNIVALI)
CONTACT: Prof. Douglas Rossi de Melo (drm@univali.br)
-------------------------------- Reviews ----------------------------------------------------
| Date       - Version - Author                      | Description
---------------------------------------------------------------------------------------------
| 20/01/2023 - 1.0     - Welliton da Silva de Lima   | Initial Modeling in SystemC
---------------------------------------------------------------------------------------------
*/

#ifndef __XINA__
#define __XINA__

#include <systemc>
#include <vector>

#include "NoC.h"
#include "../XRouter/XINA_Router.h"

//XINA Network construction parameters
#define DATA_WIDTH   8
#define BUFFER_DEPTH 8
#define Y_SIZE       2
#define X_SIZE       2

//State machine implementation parameters: 0 - Moore | 1 - Mealy
#define FLOW_MODE    1
#define ROUTING_MODE 1
#define ARBITER_MODE 1

//Buffers implementation parameters: 0 - Ring | 1 - Shift
#define BUFFER_MODE  0

class XINA : public INoC{
public:

    //-------------------------------------SIGNALS ---------------------------------------------------//
    sc_vector< sc_vector< sc_signal<sc_bv<DATA_WIDTH+1> > > >  w_X_IN_DATA;
    sc_vector< sc_vector< sc_signal<bool> > >                  w_X_IN_VAL;
    sc_vector< sc_vector< sc_signal<bool> > >                  w_X_IN_ACK;
    sc_vector< sc_vector< sc_signal<sc_bv<DATA_WIDTH+1> > > >  w_X_OUT_DATA;
    sc_vector< sc_vector< sc_signal<bool> > >                  w_X_OUT_VAL;
    sc_vector< sc_vector< sc_signal<bool> > >                  w_X_OUT_ACK;

    sc_vector< sc_vector< sc_signal<sc_bv<DATA_WIDTH+1> > > > w_Y_IN_DATA;
    sc_vector< sc_vector< sc_signal<bool> > >                 w_Y_IN_VAL;
    sc_vector< sc_vector< sc_signal<bool> > >                 w_Y_IN_ACK;
    sc_vector< sc_vector< sc_signal<sc_bv<DATA_WIDTH+1> > > > w_Y_OUT_DATA;
    sc_vector< sc_vector< sc_signal<bool> > >                 w_Y_OUT_VAL;
    sc_vector< sc_vector< sc_signal<bool> > >                 w_Y_OUT_ACK;

    // Connection enabling variables
    int L_ENA;
    int N_ENA;
    int E_ENA;
    int S_ENA;
    int W_ENA;

    std::vector<std::vector<IRouter *>> u_Router;

    SC_HAS_PROCESS(XINA);
    XINA(sc_module_name mn);

    const char* moduleName() const { return "XINA"; }

  ~XINA();
};

inline XINA::XINA(sc_module_name mn):INoC(mn,(X_SIZE*Y_SIZE)){
// Initialization of link signals

        u_Router.resize(X_SIZE);

        w_X_IN_DATA. init(X_SIZE+1);
        w_X_IN_VAL.  init(X_SIZE+1);
        w_X_IN_ACK.  init(X_SIZE+1);
        w_X_OUT_DATA.init(X_SIZE+1);
        w_X_OUT_VAL. init(X_SIZE+1);
        w_X_OUT_ACK. init(X_SIZE+1);

        w_Y_IN_DATA. init(X_SIZE);
        w_Y_IN_VAL.  init(X_SIZE);
        w_Y_IN_ACK.  init(X_SIZE);
        w_Y_OUT_DATA.init(X_SIZE);
        w_Y_OUT_VAL. init(X_SIZE);
        w_Y_OUT_ACK. init(X_SIZE);

        for(int i=0; i<X_SIZE+1; i++){

            w_X_IN_DATA [i].init(Y_SIZE);
            w_X_IN_VAL  [i].init(Y_SIZE);
            w_X_IN_ACK  [i].init(Y_SIZE);
            w_X_OUT_DATA[i].init(Y_SIZE);
            w_X_OUT_VAL [i].init(Y_SIZE);
            w_X_OUT_ACK [i].init(Y_SIZE);

        }

        for(int i=0; i<X_SIZE; i++){
            u_Router[i].resize(Y_SIZE, NULL);

            w_Y_IN_DATA [i].init(Y_SIZE+1);
            w_Y_IN_VAL  [i].init(Y_SIZE+1);
            w_Y_IN_ACK  [i].init(Y_SIZE+1);
            w_Y_OUT_DATA[i].init(Y_SIZE+1);
            w_Y_OUT_VAL [i].init(Y_SIZE+1);
            w_Y_OUT_ACK [i].init(Y_SIZE+1);

        }

// Network creation loop

        int each = 0;
        unsigned int k=0;
        for(int i=0; i<X_SIZE; i++){
            for(int j=0; j<Y_SIZE; j++,k++){

                L_ENA = (1);
                N_ENA = ((j+1)%Y_SIZE);
                E_ENA = ((i+1)%X_SIZE);
                S_ENA = (j);
                W_ENA = (i);

                u_Router[i][j] = new XINA_Router("Router"+each,i,j,L_ENA,N_ENA,E_ENA,S_ENA,W_ENA,FLOW_MODE,ROUTING_MODE,ARBITER_MODE,BUFFER_MODE);

                u_Router[i][j]->i_CLK(i_CLK);
                u_Router[i][j]->i_RST(i_RST);

                u_Router[i][j]->i_IN_DATA_L  (i_DATA_IN    [k]);
                u_Router[i][j]->i_IN_VAL_L   (i_VALID_IN   [k]);
                u_Router[i][j]->o_IN_ACK_L   (o_RETURN_IN  [k]);
                u_Router[i][j]->o_OUT_DATA_L (o_DATA_OUT   [k]);
                u_Router[i][j]->o_OUT_VAL_L  (o_VALID_OUT  [k]);
                u_Router[i][j]->i_OUT_ACK_L  (i_RETURN_OUT [k]);

                u_Router[i][j]->i_IN_DATA_N  (w_Y_IN_DATA  [i][j+1]);
                u_Router[i][j]->i_IN_VAL_N   (w_Y_IN_VAL   [i][j+1]);
                u_Router[i][j]->o_IN_ACK_N   (w_Y_IN_ACK   [i][j+1]);
                u_Router[i][j]->o_OUT_DATA_N (w_Y_OUT_DATA [i][j+1]);
                u_Router[i][j]->o_OUT_VAL_N  (w_Y_OUT_VAL  [i][j+1]);
                u_Router[i][j]->i_OUT_ACK_N  (w_Y_OUT_ACK  [i][j+1]);

                u_Router[i][j]->i_IN_DATA_E  (w_X_OUT_DATA [i+1][j]);
                u_Router[i][j]->i_IN_VAL_E   (w_X_OUT_VAL  [i+1][j]);
                u_Router[i][j]->o_IN_ACK_E   (w_X_OUT_ACK  [i+1][j]);
                u_Router[i][j]->o_OUT_DATA_E (w_X_IN_DATA  [i+1][j]);
                u_Router[i][j]->o_OUT_VAL_E  (w_X_IN_VAL   [i+1][j]);
                u_Router[i][j]->i_OUT_ACK_E  (w_X_IN_ACK   [i+1][j]);

                u_Router[i][j]->i_IN_DATA_S  (w_Y_OUT_DATA [i][j]);
                u_Router[i][j]->i_IN_VAL_S   (w_Y_OUT_VAL  [i][j]);
                u_Router[i][j]->o_IN_ACK_S   (w_Y_OUT_ACK  [i][j]);
                u_Router[i][j]->o_OUT_DATA_S (w_Y_IN_DATA  [i][j]);
                u_Router[i][j]->o_OUT_VAL_S  (w_Y_IN_VAL   [i][j]);
                u_Router[i][j]->i_OUT_ACK_S  (w_Y_IN_ACK   [i][j]);

                u_Router[i][j]->i_IN_DATA_W  (w_X_IN_DATA  [i][j]);
                u_Router[i][j]->i_IN_VAL_W   (w_X_IN_VAL   [i][j]);
                u_Router[i][j]->o_IN_ACK_W   (w_X_IN_ACK   [i][j]);
                u_Router[i][j]->o_OUT_DATA_W (w_X_OUT_DATA [i][j]);
                u_Router[i][j]->o_OUT_VAL_W  (w_X_OUT_VAL  [i][j]);
                u_Router[i][j]->i_OUT_ACK_W  (w_X_OUT_ACK  [i][j]);
                each++;
            }
        }
}

//------------- Destructor -----------------------
inline XINA::~XINA(){
      for(int i=0; i<X_SIZE; i++){
          for(int j=0; j<Y_SIZE; j++){
            u_Router[i][j];
          }
      }
}
#endif //__XINA__

