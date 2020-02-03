
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
//#include <graphics.h>
#include <dos.h>
//#include "graphics.h>
#define MAX 80
#define PORT 12345
#define SA struct sockaddr
int marhale=0;
char authtoken[100];
#include <stdio.h>
//#include<iostream>
#include <stdlib.h>
#include <windows.h>
#include <dos.h>
#include <direct.h>
//using namespace std;

void SetColor(int ForgC)
 {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }

 void ClearConsoleToColors(int ForgC, int BackC)
 {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute(hStdOut, wColor);
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          SetConsoleCursorPosition(hStdOut, coord);
     }
    return;
}
COORD coord={0,0}; // this is global variable
                                   //center of axis is set to the top left cornor of the screen

void gotoxy(int x,int y)
{
  	coord.X=x;
 	coord.Y=y;
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int make_socket()
{
  //  ClearConsoleToColors(15,4);
   // system("COLOR F2");
    //cprintf("ll");
    int client_socket, server_socket;
    struct sockaddr_in servaddr, cli;
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    // Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    // Create and verify socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
        //printf("Socket successfully created..\n");

        // Assign IP and port
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Connect the client socket to server socket
    if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection to the server failed...\n");
        exit(0);
    }
    else
        //	printf("Successfully connected to the server..\n");
        return client_socket;
}
// Function designed for chat between client and server.
void chat(int server_socket,int user)
{
    static int pio=0;
    char buffer[100000];
    int n;
    n=0;
    memset(buffer, 0, sizeof(buffer));
    if (user == 1&& marhale==0)
    {
        char username[100];
        char password[100];
        char c;
        printf("Enter Username\n");
        while ((username[n++] = getchar()) != '\n')
            ;
        for (int i = 0 ; i <1000 ; i++)
            if (username[i]=='\n')
            {
                username[i]='\0';
                break;
            }
        username[n]='\0';
        printf("Password\n");
        n=0;
        while ((password[n++] = getchar()) != '\n')
            ;
        for (int i = 0 ; i <1000 ; i++)
            if (password[i]=='\n')
            {
                password[i]='\0';
                break;
            }
        //scanf("%c",&c);
        // printf("%s %s\n",username,password);
        strcpy(buffer,"register ");
        strcat(buffer,username);
        strcat(buffer,", ");
        strcat(buffer,password);

        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
        //strcar(buffer,'\0');
    }
    if (user == 2 && marhale == 0 )
    {
        char username[100];
        char password[100];
        char c;
        printf("Enter Username\n");
        scanf("%s",username);
        printf("Password\n");
        scanf("%s",password);
        scanf("%c",&c);
        strcpy(buffer,"login ");
        strcat(buffer,username);
        strcat(buffer,", ");
        strcat(buffer,password);
        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale==1 && user==1)
    {
        char channelname[100];
        printf("Channel Name\n");
        scanf("%[^\n]",channelname);
        char c;
        scanf("%c",&c);
        strcpy(buffer,"create channel ");
        strcat(buffer,channelname);
        strcat(buffer,", ");
        strcat(buffer,authtoken);

        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale == 1 && user == 2)
    {
        char channelname[100];
        printf("Channel Name\n");
        scanf("%[^\n]",channelname);
        char c;
        scanf("%c",&c);
        strcpy(buffer,"join channel ");
        strcat(buffer,channelname);
        strcat(buffer,", ");
        strcat(buffer,authtoken);

        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale == 1 && user == 3)
    {
        strcpy(buffer,"logout ");
        strcat(buffer,authtoken);

        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale == 2 && user == 1)
    {
        printf("Write a massage\n");
        char message[1000];
        scanf("%[^\n]",message);
        char c;
        scanf("%c",&c);
        strcpy(buffer,"send ");
        strcat(buffer,message);
        strcat(buffer,", ");
        strcat(buffer,authtoken);

        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale == 2 && user == 2)
    {
        strcpy(buffer,"refresh ");
        strcat(buffer,authtoken);

        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale == 2 && user == 4)
    {
        strcpy(buffer,"leave ");
        strcat(buffer,authtoken);

        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale == 2 && user == 3)
    {
        strcpy(buffer,"channel members ");
        strcat(buffer,authtoken);

        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale == 2 && user == 6)
    {

        strcpy(buffer,"searchmember ");
        char member[100];
        printf("User name:\n");
        scanf("%s",member);
        char c;
        scanf("%c",&c);
        strcat(buffer,member);
        strcat(buffer," ");
        strcat(buffer,authtoken);
        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    if (marhale == 2 && user == 5)
    {
        strcpy(buffer,"searchmessage ");
        char message[100];
        printf("Message:\n");
        scanf("%s",message);
        char c;
        scanf("%c",&c);
        strcat(buffer,message);
        strcat(buffer," ");
        strcat(buffer,authtoken);
        for (int i = 0 ; i <1000 ; i++)
            if (buffer[i]=='\0')
            {
                buffer[i]='\n';
                break;
            }
    }
    //printf("%s",buffer);
    //printf("Enter your message: ");
    n = 0;

    // Copy client message to the buffer
    //while ((buffer[n++] = getchar()) != '\n')
    //;
    //buffer[n++]='\n';
    //if (pio != 0)
    server_socket=make_socket();


    // Send the buffer to server
    send(server_socket, buffer, sizeof(buffer), 0);
    //printf("\nFrom client :%s \n",buffer);
    memset(buffer, 0, sizeof(buffer));

    // Read the message from server and copy it to buffer
    recv(server_socket, buffer, sizeof(buffer), 0);
    printf("\nFrom server: %s\n", buffer);
    if (marhale == 2 && user == 5)
    {
            int flag=0;
            int sar=27;
            printf("Messages:\n");
            if (buffer[sar] != '}')
            while(flag==0)
            {
                for ( int i = sar ; i <10000; i++ )
                {
                    if (buffer[i]=='"' && (buffer[i+1] == ',' || buffer[i+1] == ']'))
                    {
                        sar=i;
                        break;
                    }
                    else
                    {
                        printf("%c",buffer[i]);
                        sar=i;
                    }
                }
                for (int i = sar ; i <sar+3; i++)
                    if (buffer[i]==']' && buffer[i+1] == '}')
                    {
                        flag=1;
                    }
                sar+=3;
                printf("\n");
    }
    }
    if (marhale == 2 && user == 6)
    {
        char pasokh[1000];
        sscanf(buffer,"%[\n]",pasokh);
        printf("\n%s\n",buffer);
    }
    if (marhale!=2)
    {
        if (marhale == 1 && user == 3 && buffer[9]!='E')
        {
            marhale--;
        }
        else
        {
            if (marhale==0 && user == 2 && buffer[9]=='A')
            {
                marhale++;
                for (int i = 31; i <=62; i++)
                    authtoken[i-31]=buffer[i];
            }
            else
            {
                if (marhale !=0 )
                {
                    if (buffer[9]!='E')
                        marhale++;
                }
                else
                {
                    if (user == 1)
                    {
                    if (buffer[9]=='E')
                        printf("Registration failed\n");
                    else
                        printf("Registration completed\n");
                    }
                }
            }
        }
    }
    else
    {
        if (user ==  4)
        {
            marhale--;
        }
        if (user == 2)
        {
            int sar=23;
            int flag=0;
            while(flag==0)
            {
                printf("\n");
                for (int i = sar ; i <= (sar+14); i++)
                    if (buffer[i]==']'  && buffer[i+1]=='}')
                    {
                        flag=1;
                        //printf("\ni=%d\n",i);
                        //printf("g%d\n",strlen(buffer));
                        break;
                    }
                sar+=14;
                for (int i = sar ; i < 10000 && flag!=1; i++)
                    if (buffer[i] != '"' || buffer[i+1] != ',')
                    {
                        printf("%c",buffer[i]);
                        sar=i;
                        if (flag==1)
                            printf("mard2");
                        if (buffer[i]==']')
                        {
                            flag=1;
                            printf("mard");
                            break;
                        }

                    }
                    else
                    {
                        break;
                    }
                sar++;
                printf(": ");
                for (int i = sar+13 ; i < 10000 && flag != 1; i++)
                    if (buffer[i] != '"' || buffer[i+1]!='}')
                    {
                        printf("%c",buffer[i]);
                        sar=i;
                        if (flag==1)
                            printf("mard2");
                        if (buffer[i]==']')
                        {
                            flag=1;
                            printf("mard");
                            break;
                        }

                    }
                    else
                    {
                        break;
                    }
                sar++;
            }
        }
        if (user == 3)
        {
            int flag=0;
            int sar=27;
            printf("Channel Members:\n");
            while(flag==0)
            {
                for ( int i = sar ; i <10000; i++ )
                {
                    if (buffer[i]=='"' && (buffer[i+1] == ',' || buffer[i+1] == ']'))
                    {
                        sar=i;
                        break;
                    }
                    else
                    {
                        printf("%c",buffer[i]);
                        sar=i;
                    }
                }
                for (int i = sar ; i <sar+3; i++)
                    if (buffer[i]==']' && buffer[i+1] == '}')
                    {
                        flag=1;
                    }
                sar+=3;
                printf("\n");
            }
        }
    }
    // Print buffer which contains the server message


    // If the message starts with "exit" then client exits and chat ends
    if ((strncmp(buffer, "exit", 4)) == 0)
    {
        printf("Client stopping...\n");
        return;
    }
}

//gotoxy function


int main()
{

    ClearConsoleToColors(10,9);

    int client_socket, server_socket;
    struct sockaddr_in servaddr, cli;

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    // Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

    // Create and verify socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        printf("Socket creation failed...\n");
        exit(0);
    }
    else
//		printf("Socket successfully created..\n");

        // Assign IP and port
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // Connect the client socket to server socket
    if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection to the server failed...\n");
        exit(0);
    }
    else;
    closesocket(client_socket);
    //	printf("Successfully connected to the server..\n");
    int user;
    char c;
    while (1)
    {
        if (marhale==0)
        {
            ClearConsoleToColors(10,4);

            //yellow();
            printf("Account Menu:\n");
            printf("1: Register\n");
            printf("2: Login\n");
            printf("3: Exit\n");
            gotoxy(15,1);
            printf("<--");
            int i = 1;
            while (1)
            {

                char c,j;
                //j = '\n';
                c=_getch();
                //printf(" c=%d ",j);
                //system("pause");
                if ( c == 72)
                {

                    if (i > 1 && i < 4)
                    {
                    gotoxy(15,i);
                    printf("   ");
                    gotoxy(15,--i);
                    printf("<--");
                    }

                }
                if ( c == 80)
                {
                    if (i >= 1 && i < 3)
                    {
                    gotoxy(15,i);
                    printf("   ");
                    gotoxy(15,++i);
                    printf("<--");
                    }
                }
                if (c == 75)
                    break;

            }
            user = i ;
            gotoxy(0,4);
            //scanf("%d",&user);
            if (user == 3)
            {
                closesocket(client_socket);
                return 0;
            }
            //scanf("%c",&c);
            chat(client_socket,user);
            system("pause");
        }
        if (marhale==1)
        {
            ClearConsoleToColors(10,6);
            printf("1: Create Channel\n");
            printf("2: Join channel\n");
            printf("3: Logout\n");
            gotoxy(20,0);
            printf("<--");
            int i = 0;
            while (1)
            {

                char c,j;
                //j = '\n';
                c=_getch();
                //printf(" c=%d ",j);
                //system("pause");
                if ( c == 72)
                {

                    if (i > 0 && i < 3)
                    {
                    gotoxy(20,i);
                    printf("   ");
                    gotoxy(20,--i);
                    printf("<--");
                    }

                }
                if ( c == 80)
                {
                    if (i >= 0 && i < 2)
                    {
                    gotoxy(20,i);
                    printf("   ");
                    gotoxy(20,++i);
                    printf("<--");
                    }
                }
                if (c == 75)
                    break;

            }
            gotoxy(0,4);
            user = i + 1 ;
            //scanf("%c",&c);
            chat(client_socket,user);
            system("pause");
        }
        if (marhale == 2)
        {
            ClearConsoleToColors(10,19);
            //printf("Successfully connected to the server..\n");
            printf("1: Send Message\n");
            printf("2: Refresh\n");
            printf("3: Channel Members\n");
            printf("4: Leave Channel\n");
            printf("5: Search Message\n");
            printf("6: Search Member\n");
            gotoxy(20,0);
            printf("<--");
            int i = 0;
            while (1)
            {

                char c,j;
                //j = '\n';
                c=_getch();
                //printf(" c=%d ",j);
                //system("pause");
                if ( c == 72)
                {

                    if (i > 0 && i < 6)
                    {
                    gotoxy(20,i);
                    printf("   ");
                    gotoxy(20,--i);
                    printf("<--");
                    }

                }
                if ( c == 80)
                {
                    if (i >= 0 && i < 5)
                    {
                    gotoxy(20,i);
                    printf("   ");
                    gotoxy(20,++i);
                    printf("<--");
                    }
                }
                if (c == 75)
                    break;

            }
            gotoxy(0,6);
            user = i + 1 ;
            chat(client_socket,user);

            system("pause");
        }

    }
    // Function for chat
    //chat(client_socket);

    // Close the socket

}
