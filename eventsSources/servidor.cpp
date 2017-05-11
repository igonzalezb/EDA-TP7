
#include "servidor.h"

//servidor()
//recive como paramtro un int, que representa el puerto que el srvidor escucha,
//en caso que ese puerto no sea indicado, el puerto por defecto es 12345.
//
servidor::servidor(UINT32 port)
{
	portNumber = port;//asigno el puerto al servidor
	ioServer = new boost::asio::io_service();//creo el io_service del servidor
	ServerSocket = new boost::asio::ip::tcp::socket(*ioServer);//creo el socket del servidor
	conectionServerAceptor = new boost::asio::ip::tcp::acceptor(*ioServer,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), portNumber));//creo el aceptor del servidor
	//std::cout << std::endl << "El puerto " << portNumber << " se creo" << std::endl;
	
}

servidor::~servidor()
{
	conectionServerAceptor->close();
	ServerSocket->close();
	delete conectionServerAceptor;
	delete ServerSocket;
	delete ioServer;
	
}

//waitForCliente()
//metodo bloqueante, que espera la conexion del cliente.
//

void servidor::waitForCliente()
{
	conectionServerAceptor->accept(*ServerSocket);
	ServerSocket->non_blocking(true);
}
//receiveDataForCliente
//previamente se deve llamar a waitforcleinte()
//recive como paramteros un arreglo de char(buffer) y una int,
//con la cantidad de elementos de dicho arreglo.
//si se puedo recivir toda la informacion devuelve un true, caso contrario
//devuelve un false.
size_t servidor::receiveDataForCliente(char * buffer_t, int bufferSize)
{
	size_t longitudDelMensaje = 0;
	boost::system::error_code error;
	char bufferTemp[900];
	
	do
	{
		longitudDelMensaje=ServerSocket->read_some(boost::asio::buffer(bufferTemp, 900), error);
	} while (error.value() == WSAEWOULDBLOCK);
		
	if (error)
	{
		longitudDelMensaje = MY_ERROR;
	} else if (longitudDelMensaje <= bufferSize)//evaluo si entra en lo que me mandaron
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
size_t servidor::nonBlockinReceiveDataForCliente(char * buffer_t, int bufferSize)
{
	
	size_t longitudDelMensaje = 0;
	boost::system::error_code error;
	char bufferTemp[900];

	longitudDelMensaje=ServerSocket->read_some(boost::asio::buffer(bufferTemp,900),error);
	
	if (error.value() == WSAEWOULDBLOCK)//si no se leyo nada devuelvo MY_EMPTY
	{
		longitudDelMensaje = MY_EMPTY;
	}
	else if(error)
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



//sendData()
//recive un arreglo de char, que son lo elementos que mandara. tambien recive
//un int con la cantidad de elementos que se necesitan enviar
//
bool servidor::sendData(char * dataToSend_t, unsigned int sizeData)
{
	size_t len = 0;
	boost::system::error_code error;

	len = ServerSocket->write_some(boost::asio::buffer(dataToSend_t, sizeData), error);
	
	if ((error.value() == WSAEWOULDBLOCK) || error)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

