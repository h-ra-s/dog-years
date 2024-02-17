/*
Heather Slanec
This program creates an array of structures that will hold information for <= 10 dogs
Dog Years Program
*/

#include <stdio.h>
#include<string.h>//for strings
#include <stdlib.h>//for files

//structures-----------------------------------
struct DogInformation
{
	char name[20];
	int weight;
	int age;
	char size[8];
	int dogYears;
};

//function prototypes--------------------------
void readFile(struct DogInformation dogs[], int *numOfDogs);
void dogInput(struct DogInformation dogs[], int *numOfDogs);
void calcSizeAge(struct DogInformation dogs[], int numOfDogs);
void printResults(struct DogInformation dogs[], int numOfDogs);
void saveResults(struct DogInformation dogs[], int numOfDogs);

//main--------------------------------------------------------------------------------
int main()
{
	//declare struct array
	struct DogInformation dogs[10];
	
	//declare var
	int oneTwo, numOfDogs;
	
	//get user input - enter info or read file
	printf("\nWould you like to... \n1. Enter information about your dog");
	printf("\n2. Read in this information from a file (please use a file with values separated by a comma!)"); 
	printf("\nEnter 1 or 2: ");
	scanf("%d", &oneTwo);
	//get enter keystroke
	getchar();
	
	//validate choice
	while(oneTwo != 1 && oneTwo != 2)
	{
		printf("\n\nError! Must enter 1 or 2.");
		printf("\nWould you like to... \n1. Enter information about your dog");
		printf("\n2. Read in this information from a file (please use a file with values separated by a comma!)"); 
		printf("\nEnter 1 or 2: ");		scanf("%d", &oneTwo);
		//get enter keystroke
		getchar();
	}
	
	//if user chooses to read in a file
	if(oneTwo == 2)
	{
		//call function to read file
		readFile(dogs, &numOfDogs);
	}
	//if user chooses to enter info
	else
	{
		//function to get dog info
		dogInput(dogs, &numOfDogs);
	}

	//function to calc dog size and age
	calcSizeAge(dogs, numOfDogs);
	
	
	//ask if user wants to save to file or print to screen
	printf("\nWould you like to... \n1. Print your results to the screen");
	printf("\n2. Save your results to a file"); 
	printf("\nEnter 1 or 2: ");
	scanf("%d", &oneTwo);
	//get enter keystroke
	getchar();
	
	//validate choice
	while(oneTwo != 1 && oneTwo != 2)
	{
		printf("\n\nError! Must enter 1 or 2.");
		printf("\nWould you like to... \n1. Print your results to the screen");
		printf("\n2. Save your results to a file"); 
		printf("\nEnter 1 or 2: ");		
		scanf("%d", &oneTwo);
		//get enter keystroke
		getchar();
	}
	
	//if user chooses to save results to file
	if(oneTwo == 2)
	{
		saveResults(dogs, numOfDogs);
	}
	//if user chooses to print to screen
	else
	{
		//function to print results
		printResults(dogs, numOfDogs);
	}
	
	return 0;
}
//functions--------------------------------------------------------------------------
void saveResults(struct DogInformation dogs[], int numOfDogs)
{
	//get name of file
	char fileName[20];
	printf("\nPlease enter the filename (no extension) where you would like to save your results: ");
	fgets(fileName, 20, stdin);
	//remove enter keystroke from file name
	fileName[strlen(fileName) - 1]= '\0';
	
	//add .csv to end of filename
	/*strncat is included in #include<string.h>,
	format is (originalString, charToAppend, #ofCharsToBeAppended);
	*/
	char fileExt[4] = ".csv";
	strncat(fileName,fileExt,4);
	
	//1 pointer
	FILE *fp;
	
	//2 open file
	fp = fopen(fileName, "w");
	
	//3 stop if file can't be opened
	if(fp == NULL)
	{
		printf("Could not open %s file...exiting program", fileName);
		exit(0);
	}
	
	//4 add data to file
	fprintf(fp, "Dog Name,Dog Weight,Years in Human,Years in Dog");
	int x;
	for(x = 0; x < numOfDogs; x++)
	{
		fprintf(fp, "\n%s,%s dog,%d,%d", dogs[x].name, dogs[x].size, 
			dogs[x].age, dogs[x].dogYears);	
	}
	
	//5 close file
	fclose(fp);
	
	//happy notice
	printf("\nFile successfully created!");
}


void readFile(struct DogInformation dogs[], int *numOfDogs)
{
	//get name of file
	char fileName[20];
	printf("\nPlease enter the entire filename: ");
	fgets(fileName, 20, stdin);
	//remove enter keystroke from file name
	fileName[strlen(fileName) - 1]= '\0';

	
	//1 pointer
	FILE *fp;
	
	//2 open file
	fp = fopen(fileName, "r");
	
	//3 stop if file can't be opened
	if(fp == NULL)
	{
		printf("Could not open %s file...exiting program", fileName);
		exit(0);
	}
	
	//4 read file
	char line[100];
	char *sp;
	int x = 0;
	
	while(fgets(line, 100, fp) != NULL)
	{
		//get name
		sp = strtok(line, ",");
		strcpy(dogs[x].name, sp);

		//get weight
		sp = strtok(NULL, ",");
		dogs[x].weight = atoi(sp);
		//accumulate x
		
		//get age
		sp = strtok(NULL, ",");
		dogs[x].age = atoi(sp);
		
		x++;
	}
	
	//assign num of dogs in file to numOfDogs
	*numOfDogs = x;
	
	//5 close file
	fclose(fp);
}


void printResults(struct DogInformation dogs[], int numOfDogs)
{
	printf("\n\nDog Name \t\tDog Weight \t\tYears in Human \t\tYears in Dog");
	//print dogs
	int x;
	for(x = 0; x < numOfDogs; x++)
	{
		printf("\n\n%s \t\t\t%s dog \t\t%d \t\t\t%d", dogs[x].name, dogs[x].size, 
			dogs[x].age, dogs[x].dogYears);	
	}
}


void calcSizeAge(struct DogInformation dogs[], int numOfDogs)
{
	//calculate dog size
	int x;
	for(x = 0; x < numOfDogs; x++)
	{
		if(dogs[x].weight <= 20)
			strcpy(dogs[x].size, "Small");
		else if(dogs[x].weight > 20 && dogs[x].weight <= 50)
			strcpy(dogs[x].size, "Medium");
		else
			strcpy(dogs[x].size, "Large");
	}
	
	//calculate dog age
	for(x = 0; x < numOfDogs; x++)
	{
		//for small dogs-------------------------------------
		if(strcmp(dogs[x].size, "Small") == 0)
		{
			//1
			if(dogs[x].age == 1)
				dogs[x].dogYears = 15;
			//2	
			else if(dogs[x].age == 2)
				dogs[x].dogYears = 23;
			//3	
			else if(dogs[x].age == 3)
				dogs[x].dogYears = 28;
			//4+
			else
			{
				//set base age for cumulation/age if dog is 4
				dogs[x].dogYears = 32;
				
				//loop for each year above 4 until real age is reached
				if(dogs[x].age > 4)
				{
					int y;
					for(y = 4; y < dogs[x].age; y++)
					{
						dogs[x].dogYears += 4;
					}
				}
			}
		}

		//for medium dogs----------------------------------
		if(strcmp(dogs[x].size, "Medium") == 0)
		{
			//1
			if(dogs[x].age == 1)
				dogs[x].dogYears = 14;
			//2	
			else if(dogs[x].age == 2)
				dogs[x].dogYears = 23;
			//3	
			else if(dogs[x].age == 3)
				dogs[x].dogYears = 30;
			//4+
			else
			{
				//set base age for cumulation/age if dog is 4
				dogs[x].dogYears = 35;
				
				//loop for each year above 4 until real age is reached
				if(dogs[x].age > 4)
				{
					int y;
					for(y = 4; y < dogs[x].age; y++)
					{
						dogs[x].dogYears += 5;
					}
				}
			}
		}
		
		//for large dogs--------------------------------
		if(strcmp(dogs[x].size, "Large") == 0)
		{
			//1
			if(dogs[x].age == 1)
				dogs[x].dogYears = 12;
			//2	
			else if(dogs[x].age == 2)
				dogs[x].dogYears = 21;
			//3	
			else if(dogs[x].age == 3)
				dogs[x].dogYears = 29;
			//4+
			else
			{
				//set base age for cumulation/age if dog is 4
				dogs[x].dogYears = 36;
				
				//loop for each year above 4 until real age is reached
				if(dogs[x].age > 4)
				{
					int y;
					for(y = 4; y < dogs[x].age; y++)
					{
						dogs[x].dogYears += 7;
					}
				}
			}
		}
	}
}


void dogInput(struct DogInformation dogs[], int *numOfDogs)
{
	//get user input
	printf("\nHow many dogs do you have? ");
	scanf("%d", numOfDogs);
	//remove enter keystroke so not counted in following string input
	getchar();
	
	//make sure dogs < 10 and > 1
	while(*numOfDogs > 10 || *numOfDogs < 1)
	{
		printf("\n\nMust have between 1 and 10 dogs! Try again.");
		
		//get user input
		printf("\nHow many dogs do you have? ");
		scanf("%d", numOfDogs);
		//remove enter keystroke so not counted in following string input
		getchar();
	}
	
	//loop until user has entered info for all dogs
	int x;
	for(x = 0; x < *numOfDogs; x++)
	{
		printf("\n\nPlease enter the dog's name: ");
		fgets(dogs[x].name,30,stdin);
		//remove enter keystroke from end of name and insert null
		dogs[x].name[strlen(dogs[x].name) - 1] = '\0';


		printf("\nPlease enter the dog's weight: ");
		scanf("%d", &dogs[x].weight);
		
		//data validation for weight, based on Guinness World Record
		while(dogs[x].weight < 1 || dogs[x].weight > 343)
		{
			printf("\n\nDog's weight must be between 1 and 343 pounds. Try again!");
			
			printf("\nPlease enter the dog's weight: ");
			scanf("%d", &dogs[x].weight);
		}
		
		
		printf("\nPlease enter the dog's age: ");
		scanf("%d", &dogs[x].age);
		//remove enter keystroke so not counted in string when looping
		getchar();
		
		//data validation for age, based on Guinness World Record
		while(dogs[x].age < 1 || dogs[x].age > 31)
		{
			printf("\n\nDog's age must be between 1 and 31. Try again!");
				
			printf("\nPlease enter the dog's age: ");
			scanf("%d", &dogs[x].age);
			//remove enter keystroke so not counted in string when looping
			getchar();
		}
	}
}














