#ifndef FSM_SIMULATION_H
#define FSM_SIMULATION_H

/*	
*************************************************************************************************

	Los estados y eventos derivados de estas clases imprimiran un string en pantalla de acuerdo a
lo que se les indique cuando se llame a sus constructores.

*/


#include "GenericFSM.h"

using namespace std;


class TPTFSimulationFSM : public GenericFSM
{
public:
	TPTFSimulationFSM() : GenericFSM() {;};
	TPTFSimulationFSM(GenericState * initState) : GenericFSM(initState) {;};
	virtual void dispatch(GenericEvent& ev);
};

#endif //FSM_SIMULATION_H
