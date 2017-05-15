#include <iostream>

bool validateInput(char *input);

int main()
{
	char command[600];
	char nombreArchivo[600];
		
	printf("ENTER COMMAND:\n");
	scanf("%s", command);							//esto toma los dos en el mismo string scanf("%[^\n]s", command);
	scanf("%s", nombreArchivo);
	for (int i = 0; i < strlen(command); i++)
		command[i] = toupper(command[i]);
	if (!validateInput(command))
	{
		printf("ERROR\n");
	}
	
	printf("Command entered: %s %s\n", command, nombreArchivo);
	
	
	return EXIT_SUCCESS;
}


bool validateInput(char *input)
{
	if (!strcmp(input, "PUT"))
	{
		printf("caso 1\n");
	}
	else if (!strcmp(input, "GET"))
	{
		printf("caso 2\n");
	}
	else
		return false;

	return true;
}