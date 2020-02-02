
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#define MAX 80
#define PORT 12345
#define SA struct sockaddr
int marhale=0;
char authtoken[100];
int zajr()
{
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
    //printf("%s",buffer);
    //printf("Enter your message: ");
    n = 0;

    // Copy client message to the buffer
    //while ((buffer[n++] = getchar()) != '\n')
    //;
    //buffer[n++]='\n';
    //if (pio != 0)
    server_socket=zajr();


    // Send the buffer to server
    send(server_socket, buffer, sizeof(buffer), 0);
    printf("\nFrom client :%s \n",buffer);
    memset(buffer, 0, sizeof(buffer));

    // Read the message from server and copy it to buffer
    recv(server_socket, buffer, sizeof(buffer), 0);
    printf("\nFrom server: %s\n", buffer);
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

int main()
{
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
    //	printf("Successfully connected to the server..\n");
    int user;
    char c;
    while (1)
    {
        if (marhale==0)
        {
            printf("Account Menu:\n");
            printf("1: Register\n");
            printf("2: Login\n");
            printf("3: Exit\n");
            scanf("%d",&user);
            if (user == 3)
            {
                closesocket(client_socket);
                return 0;
            }
            scanf("%c",&c);
            chat(client_socket,user);
        }
        if (marhale==1)
        {

            printf("1: Create Channel\n");
            printf("2: Join channel\n");
            printf("3: Logout\n");
            scanf("%d",&user);
            scanf("%c",&c);
            chat(client_socket,user);
        }
        if (marhale == 2)
        {
            //printf("Successfully connected to the server..\n");
            printf("1: Send Message\n");
            printf("2: Refresh\n");
            printf("3: Channel Members\n");
            printf("4: Leave Channel\n");
            scanf("%d",&user);
            scanf("%c",&c);
            chat(client_socket,user);
        }

    }
    // Function for chat
    //chat(client_socket);

    // Close the socket

}
