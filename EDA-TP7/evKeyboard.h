#pragma once
#include <curses.h>
#include "TPTF_Events.h"

#define MaxTeclas 10

class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();
	GenericEvent * KeyBoard::Input();
private:
	char TeclasIngresadas[MaxTeclas];
	WINDOW * winTest;
	int count;
	int i;
};
