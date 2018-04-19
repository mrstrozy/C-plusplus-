/**
 * @mrstrozy_assignment1
 * @author  Matthew Strozyk <mrstrozy@buffalo.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * This contains the main function. Add further description here....
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include "../include/global.h"
#include "../include/logger.h"

#define KEYBOARD 0
#define QMAX 4


//USED ONLY FOR SERVER***************************************

bool createListenConnection();
void makeNewConnection();
void readData();

int listenSock;//int of the listening socket fd
int connections[QMAX]; //holds the fd's of the connections made


bool clientConnected;


//USED ONLY FOR CLIENT***************************************

int serverFd; //used for the client to keep server sockets fd


//USED FOR BOTH**********************************************

bool checkArgs(int, char **);
bool findMachineIP();
void showFormat();
void checkErr();
void makeList();
void readSockets();
void commandTyped();
void initData();
void mainLoop();

int portNum;	//Holds the port number inputted by the user
int errC;	//The most recent error code given
int fd;         //int of fd that is used to get IP address of machine
int myAddrInfo_len;//Size of myAddrInfo
int maxfd;	//Int of the highest file descriptor

char *myIP;//character string of this machine's IP address
char *myUBIT = "mrstrozy"; //my UBIT displayed at AUTHOR command

fd_set myFDs; //fd_set of all known file descriptors	

bool isServer;
bool isClient;

struct clientInfo
{
        int fd; //fd of the client
        struct sockaddr_in addr_info; //address info for the client
};

struct sockaddr_in myAddrInfo;	//Used to find the IP of this machine
struct sockaddr_in dummyAddr;	//Used with assigned IP to connect to find local machine IP
struct clientInfo myClients[QMAX]; //array of clientInfo that holds the connected client's information


/**
 * main function
 *
 * @param  argc Number of arguments
 :;;;;;:q

:


* @param  argv The argument list
 * @return 0 EXIT_SUCCESS
 */
int main(int argc, char **argv)
{

	/*Init. Logger*/
	cse4589_init_log(argv[2]);

	initData();//initialize the variables

	if(!checkArgs(argc,argv)){return 0;}//Both arguments are valid and we can move on

	if(!findMachineIP()){return 0;} // try to find the ip of the machine through the port given
	

	if(isServer){
	   if(!createListenConnection()){return 0;} //create the connection for listen()
	} 

	mainLoop();
	
	

/**************************************************	
 *	This is an example to follow.
 *
 *	printf("Input a number:");
	scanf("%s", number);
	cse4589_print_and_log("You entered %s\n",number);
***************************************************/

	/*Clear LOGFILE*/
	fclose(fopen(LOGFILE, "w"));

	/*Start Here*/

	return 0;
}


void mainLoop(){

	

	while(1){
	   
           makeList(); //make the select list before calling select
	   

           errC = select(maxfd+1, &myFDs, NULL, NULL, NULL); //need to read if something triggered this
           checkErr();



           if(errC == 0){
              cse4589_print_and_log("Waiting for incoming connections...\n");
           } else {

              readSockets();//read the activity that has occured

           }

        }

}


/********************************************************************************
 *
 * Function: checkArgs
 *
 * Parameters: -Number of arguments passed in by user (numOfArgs)
 * 	       -Actual arguments that the user passed in (argv)
 *
 * Description: checkArgs is a function that makes sure that the user
 * 		has passed in the correct number of arguments and also
 * 		the correct argument format. If the user has not then 
 * 		checkArgs will return false causing the program to exit.
 * 		If everything is in the right order and the correct number
 * 		of arguments are passed in, then checkArgs returns true.
 *
 ********************************************************************************/ 		

bool checkArgs(int numOfArgs, char **argv){

//	cse4589_print_and_log("In checkArgs ---------------------------------\n");
//	cse4589_print_and_log("numOfArgs = %d || argv[1] = %s || argv[2] = %s\n\n", numOfArgs, argv[1], argv[2]); 

	
	//Either none or only one parameter given
	if(numOfArgs < 3){
	   cse4589_print_and_log("\nIncorrect number of arguments.\n");
	   showFormat();
	   return false;
	}

	//Number of arguments is too many
	if(numOfArgs > 3){
	   cse4589_print_and_log("\nToo many arguments given.\n");
	   showFormat();
	   return false;
	}

	//The number of arguments is exactly 3, which is correct
	//Now to check the format

	//Confirm that the first argument is an 's' or 'c'
	if(strcmp(argv[1],"s") != 0 && strcmp(argv[1],"c") != 0){
	   cse4589_print_and_log("\nThe first argument is incorrect.\n");
	   showFormat();
	   return false;
	} else if(strcmp(argv[1], "s") == 0){//user inputted s for starting as server
	   
	   cse4589_print_and_log("Program started in Server Mode\n");
	   isServer = true;

	} else {//user wants to start program in client mode

	   cse4589_print_and_log("Program started in Client Mode\n");
	   isClient = true;

	}
	
	
	portNum = atoi(argv[2]);

	//Confirm the port number is valid (port must be between 1024 and 65535)
	if(portNum < 1024 || portNum > 65535){
	   cse4589_print_and_log("Incorrect port number. The port must be between 1024 and 65535.\n");
	   return false;
	}
	//The parameters are valid and the program can now run	
	
	return true;
}

/******************************************************************
 *
 * Function: showFormat
 *
 * Description: showFormat is a basic function that is called
 * 		when the user has run this program with the 
 * 		wrong number of arguments or format. showFormat
 * 		displays the correct way to run this program
 * 		to the user.
 *
 ******************************************************************/

bool findMachineIP(){

	int startPort = 65530;
	
	errC = socket(AF_INET,SOCK_DGRAM,0); //create a socket, returns file descriptor value for new socket
	checkErr(); //check for error on the socket creation
	fd = errC; //set the file descriptor

	//set the Type, Port, and IP of dummyAddr to be used in bind()
	dummyAddr.sin_family = AF_INET;
	dummyAddr.sin_port = htons(startPort); //start at port 
	dummyAddr.sin_addr.s_addr = INADDR_ANY;
	
	errC = -1;
	//loop if the port isn't open until you can bind to an open port
	while(errC == -1){

	   errC = bind(fd, (struct sockaddr*) &dummyAddr, sizeof dummyAddr);

	   if(errC == -1){
	      cse4589_print_and_log("Port %d not open.\n", startPort);
	      startPort = startPort - 1;
	   }
	
	}
	//checkErr();

	//set Type, Port, and IP of myAddrInfo which is passed to 
	//connect() in order to find this machine's IP address
	myAddrInfo.sin_family = AF_INET;
	myAddrInfo.sin_port = htons(53);
	inet_aton("8.8.8.8", &myAddrInfo.sin_addr);

	errC = connect(fd, (struct sockaddr*)&myAddrInfo, sizeof myAddrInfo);//connect to outside server to get machine Ip	
	checkErr();//check if there was an error connecting

	myAddrInfo_len = sizeof myAddrInfo;
	errC = getsockname(fd, (struct sockaddr*)&myAddrInfo, &myAddrInfo_len);

	myIP = inet_ntoa(myAddrInfo.sin_addr);

	cse4589_print_and_log("Your IP address is %s\n", myIP);

		
	errC =  close(fd);//close the file descriptor
	checkErr();
	
	//cse4589_print_and_log("The errc is %d\n", errC);

	return true;
}	



/*******************************************************************************
 *
 * Function: checkErr
 *
 * Parameters:	eCode - the expected code received if there was an error
 *
 *
 * Description:	checkErr takes the return code (errC) and checks it
 * 		with the set error code (eCode). If they match then there is an
 * 		error and the program should exit. If not then the program continues.
 *
 *********************************************************************************/ 		

void checkErr(){
	if(errC < 0){
	   cse4589_print_and_log("You've received an error on %s\n", errno);
	   exit(1);
	}
}

/********************************************************************************
 *
 * Function: showFormat
 *
 * Description: Displays to the user the correct format for running this program
 *
 * *******************************************************************************/

void showFormat(){

	cse4589_print_and_log("Please follow the format of: ./assignment1 [s or c] [PORT NUMBER] \n");
	cse4589_print_and_log("\nTo run as a server listening on port 4321:\n >> ./assignment1 s 4321\n");
	cse4589_print_and_log("\nTo run as a client listening on port 4321:\n >> ./assignment1 c 4321\n\n");
}

void makeList(){
	
	int count; //used in for loop

	FD_ZERO(&myFDs);
	FD_SET(KEYBOARD, &myFDs); //add keyboard to fds for select
	
	if(isClient && clientConnected){//makeList for connected client

	   

	} else {//makeList for server


	   FD_SET(listenSock, &myFDs); //add listening socket to fds for select

	   maxfd = listenSock; //maxfd is the listenSock fd to start

	   for(count = 0; count < QMAX; count++){
	      if(connections[count] != KEYBOARD && connections[count] != listenSock){ //KEYBOARD is 0
	         FD_SET(connections[count], &myFDs); //fd is not equal to KEYBOARD or the listen socket
	         if(connections[count] > maxfd){
	            maxfd = connections[count];
	         }
	      }
	   }
	}
	

}

bool createListenConnection(){

	errC = socket(AF_INET, SOCK_STREAM, 0);
	checkErr();
	listenSock = errC;

	myAddrInfo.sin_family = AF_INET;
        myAddrInfo.sin_port = htons(portNum);
        inet_aton(myIP, &myAddrInfo.sin_addr);

        errC = bind(listenSock, (struct sockaddr*) &myAddrInfo, sizeof myAddrInfo);
        checkErr();

        listen(listenSock, 4); //sock that is listening for incoming connections

	return true;
}

void readSockets(){
	//need to go through each fd and see if there was activity on it
	int count;	

	if(FD_ISSET(KEYBOARD, &myFDs)){
	   commandTyped();
	}

	if(isClient){

	} else {

  	   if(FD_ISSET(listenSock, &myFDs)){


	      makeNewConnection();
	   }


	   for(count = 0; count < QMAX; count++){
	      if(connections[count] != KEYBOARD && FD_ISSET(connections[count], &myFDs)){
	         readData();
	      }
	   }

	}

}

void makeNewConnection(){

	//write code for dealing with new connection
	int emptyNum = 0; //array location of empty client space
	bool foundEmpty = false; //flag for if there was space found
	int ss; //socket size
	struct sockaddr_in *sock;


	//find an open spot for a new connection in myClients[]
	for(int i = 0; i < QMAX && emptyNum == 0; i++){
	   if(myClients[i].fd == 0){
	      emptyNum = i; //emptyNum set to the open spot in myClients[]
	      foundEmpty = true;
	   }
	}

	//no more open spots
	if(foundEmpty == false){
	   cse4589_print_and_log("In makeNewConnection(), could not find space for another client.\n");
	}
		
	ss = sizeof (struct sockaddr_in);

	//accept the incoming connection
	errC = accept(listenSock, (struct sockaddr*) &myClients[emptyNum].addr_info, &ss); 
	checkErr();
	
	cse4589_print_and_log("Connection has been made from %s", inet_ntoa(myClients[emptyNum].addr_info.sin_addr));

	//add to connections[] integer array
	foundEmpty = false;
	for(int j = 0; j < QMAX && foundEmpty == false; j++){
	   if(connections[j] == 0){
	      connections[j] = errC;
	      foundEmpty = true;
	   }
	} 

	 

}

void commandTyped(){
	//Handle the command typed by the user
	char buf[500];
	
	memset(buf, 0, sizeof buf);

	errC = read(KEYBOARD, (void *) buf, 100);
	checkErr();
	
	buf[errC-1] = 0;

	if(isClient){

	   if(strcmp("AUTHOR", buf) == 0){
		cse4589_print_and_log("\nI, %s, have read and understood the course academic integrity policy.\n\n", myUBIT);
	   } else if(strcmp("EXIT", buf) == 0){

		exit(0);

	   } else if(clientConnected){
	   } else {//The command is not valid, ERROR
		cse4589_print_and_log("Command rejected. Please make sure the command is completely upper case and is a valid command.\n");
	   }
	} else {

	   if(strcmp("AUTHOR", buf) == 0){

	      cse4589_print_and_log("\nI, %s, have read and understood the course academic integrity policy.\n\n", myUBIT);

	   } else if(strcmp("IP", buf) == 0){

	   } else if(strcmp("PORT", buf) == 0){

	   } else if(strcmp("LIST", buf) == 0){

	   } else if(strcmp("STATISTICS", buf) == 0){

	   } else if(strcmp("BLOCKED", buf) == 0){

	   } else if(strcmp("LOGIN", buf) == 0){

	   } else if(strcmp("EXIT", buf) == 0){
		exit(0);
	   } else {
	      cse4589_print_and_log("Command rejected. Please make sure the command is completely upper case and is a valid command.\n");
  	   }
	}

}

void readData(){

	//read the data sent from a client

}

void initData(){

	isServer = false;
	isClient = false;
	clientConnected = false;
}
	
