
#include "cliente.h"

cliente::cliente()
{
	ioCliente = new boost::asio::io_service();
	clienteSocket = new boost::asio::ip::tcp::socket(*ioCliente);
	clienteResolver = new boost::asio::ip::tcp::resolver(*ioCliente);
}

cliente::~cliente()
{
	delete ioCliente;
	delete clienteSocket;
	delete clienteResolver;
}

//ConectToServer()
//metodo bloqueante que espera a conectarse con un servidor
//recive como paramteros 2 string. el primero, ipserver, es la ip del servidor
//y el segundo string, portnumber, es el numero del puerto en el cual el servidor
//esta escuchando
void cliente::ConectToServer(const char * ipServer, const char * portNumber)
{
	try 
	{
		endpoint = clienteResolver->resolve(boost::asio::ip::tcp::resolver::query(ipServer, portNumber));
		boost::asio::connect(*clienteSocket, endpoint);

	}
	catch (std::exception a)
	{
		std::cout << "Error al conectarse con el servidor, recuerde que este deve estar escuchando el puerto" << std::endl;
		exit(4);
	
	}
	clienteSocket->non_blocking(true);
	
}
 
//sendData()
//recive un arreglo de char, que son lo elementos que mandara. tambien recive
//un int con la cantidad de elementos que se necesitan enviar
//

bool cliente::sendData(char * dataToSend_t, unsigned int sizeData)
{
	size_t len = 0;
	boost::system::error_code error;

	len = clienteSocket->write_some(boost::asio::buffer(dataToSend_t, sizeData), error);

	if ((error.value() == WSAEWOULDBLOCK) || error)
	{
		return false;
	}
	else
	{
		return true;
	}

}



//receiveDataForCliente
//previamente se deve llamar a waitforcleinte()
//recive como paramteros un arreglo de char(buffer) y una int,
//con la cantidad de elementos de dicho arreglo.
//si se puedo recivir toda la informacion devuelve un true, caso contrario
//devuelve un false.
size_t cliente::receiveDataForServidor(char * buffer_t, int bufferSize)
{
	size_t longitudDelMensaje = 0;
	boost::system::error_code error;
	char bufferTemp[900];

	do
	{
		longitudDelMensaje = clienteSocket->read_some(boost::asio::buffer(bufferTemp, 900), error);
	} while (error.value() == WSAEWOULDBLOCK);

	if (error)
	{
		longitudDelMensaje = MY_ERROR;
	}else if (longitudDelMensaje <= bufferSize)//evaluo si entra en lo que me mandaron
	{
		for (size_t i = 0; i < longitudDelMensaje; i++)
		{
			buffer_t[i] = bufferTemp[i];
		}

	}
	else
	{
		longitudDelMensaje = MY_ERROR;
	}

	return longitudDelMensaje;
}




//previamente se deve llamar a waitforcleinte()
//recive como paramteros un arreglo de char(buffer) y una int,
//con la cantidad de elementos de dicho arreglo.
//devuelve: true, si se recivio algo. false, si no se recivio nada
//nota: NO ES BLOQUEANTE!!!!!!!!!!!!!!!!!!!!!!!!
size_t cliente::nonBlockinReceiveDataForServer(char * buffer_t, int bufferSize)
{

	size_t longitudDelMensaje = 0;
	boost::system::error_code error;
	char bufferTemp[900];

	longitudDelMensaje = clienteSocket->read_some(boost::asio::buffer(bufferTemp, 900), error);

	if (error.value() == WSAEWOULDBLOCK)//si no se leyo nada devuelvo MY_EMPTY
	{
		longitudDelMensaje = MY_EMPTY;
	}
	else if (error)
	{
		longitudDelMensaje = MY_ERROR;
	}
	else if (longitudDelMensaje != 0)//si se recivio mensaje
	{
		if (longitudDelMensaje <= bufferSize)//evaluo si entra en lo que me mandaron
		{
			for (size_t i = 0; i < longitudDelMensaje; i++)
			{
				buffer_t[i] = bufferTemp[i];
			}

		}
		else
		{
			longitudDelMensaje = MY_ERROR;
		}

	}

	return longitudDelMensaje;

}
