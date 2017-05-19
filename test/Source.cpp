#include <iostream>

bool validateInput(char *input);

int main()
{
	char command[600];		//Aca se guarda el Put o el Get (se pasa todo a mayusculas)
	
	char nombreArchivo[600];	//Aca se guarda el nombre del archivo
	char path[700];// = { "Download\\" };
	
	printf("ENTER COMMAND:\n");	//Solo para probar


	scanf("%s", command);				//esto toma los dos en el mismo string scanf("%[^\n]s", command);
	printf("Download\\");
	scanf("%s", path);

	for (int i = 0; i < strlen(command); i++)
		command[i] = toupper(command[i]);

	if (!validateInput(command))
	{
		printf("ERROR\n");
	}
	
	//strcat(path,nombreArchivo);

	printf("Command entered: %s %s\n", command, path);	//para probar


	return EXIT_SUCCESS;
}


bool validateInput(char *input)
{
	if (!strcmp(input, "PUT"))
	{
		//Poner aca lo que tiene que hacer
		printf("caso 1\n");
	}
	else if (!strcmp(input, "GET"))
	{
		//poner aca lo que tiene que hacer
		printf("caso 2\n");
	}
	else
		return false;

	return true;
}