#include "evKeyboard.h"
#include <string>
#include <iostream>

using namespace std;


GenericEvent * KeyBoard::Input()
{

	GenericEvent * ev = NULL;

	if (winTest != NULL)
	{

		i = getch();
		if (i != ERR)
		{
			if ((char)i == '\n')
			{

				TeclasIngresadas[count] = '\0';

				string str1("quit");
				string str2("help");

				if (str1.compare(TeclasIngresadas) == 0) // case "QUIT"
				{
					ev = new Exit;

				}
				else if (str2.compare(TeclasIngresadas) == 0) // case "HELP"
				{
					cout << "Instrucciones de uso\n" << endl;
					cout << "introduciendo PUT path , se envia al servidor el archivo que señalo en path" << endl;
					cout << "introduciendo GET path, se recive el archivo indicado en el path desde servidor hacia cliente" << endl;
					cout << "introduciendo EXIT path , se termina la comunicacion" << endl;
					ev = NULL;

				}
				else
				{
					cout << "Vuelva a ingresar el comando\n" << endl;
					ev = NULL;
				}

				return ev;
			}
			else
			{
				TeclasIngresadas[count] = (char)i;
				printf("%c", (char)i);
				count++;
			}
		}
		
	}
	return 0;
}


KeyBoard::KeyBoard()
{
	this->winTest = NULL;
	winTest = initscr();
	count = 0;
	i = 0;

	//Con las dos opciones de abajo elijo que el getch()sea no bloqueante (nodelay TRUE) y que no
	//muestre los caracteres cuando el usuario los escribe (noecho).
	nodelay(winTest, TRUE);
	noecho();
}

KeyBoard::~KeyBoard()
{
	//Llamo para termiar PDCurses.
	endwin();
}
