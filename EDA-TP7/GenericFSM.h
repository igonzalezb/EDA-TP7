#ifndef GENERIC_FSM
#define GENERIC_FSM

/*	
*************************************************************************************************

	M�quina de estados finitos gen�rica.
	Para adaptarla a casos particulares, se debe redefinir la funci�n dispatch() con los eventos
particulares que se deseen utilizar.

*/


#include "GenericEvent.h"
#include "GenericState.h"

class GenericFSM
{
public:
	GenericFSM() {;};
	GenericFSM(GenericState * firstState) { currentState = firstState; };
	virtual void dispatch(GenericEvent& ev){;};
	~GenericFSM() { delete currentState ;};
	void setState(GenericState * state) {currentState = state;};
private:

protected:
	GenericState *currentState;

};


#endif //GENERIC_FSM
