#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
//#include "cJSON.c"
//#include "cJSON.h"
#include <time.h>
#include <stdbool.h>
//#include "../json-c/json.h"
#define MAX 80
#define PORT 12345
#define SA struct sockaddr
void obj(char s[]);
void additemtoobj(char *s,char *type, char *r);
void arr(char * s);
void additemtoarr (char * s, char *r);
int server_socket, client_socket;
int channelcheck(int sh);
char * ans;
char auth[100];
char auth_token[100];
void reg(char *buffer);
void login(char *buffer);
void autt();
void create(char *buffer);
void join(char *buffer);
void sendch(char*);
void refresh(char*);
void channel_members(char *);
void leave(char*);
void logout(char *);
struct user
{
    bool a;
    bool b;

    char username[1000];
    char password[1000];
    char auth_tokenu[1000];
    char channel_name_user[1000];
    long long int fp;

};
struct sockaddr_in server, client;
struct user yaroo[1000];
//nt server_socket, client_socket;
//struct sockaddr_in server, client;
int zajr()
{

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
    server_socket = socket(AF_INET, SOCK_STREAM, 6);
    if (server_socket == INVALID_SOCKET)
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError() );
    else
        printf("Socket successfully created..\n");

    // Assign IP and port
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    // Bind newly created socket to given IP and verify
    if ((bind(server_socket, (SA *)&server, sizeof(server))) != 0)
    {
        printf("Socket binding failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully bound..\n");

    // Now server is ready to listen and verify
    if ((listen(server_socket, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    // Accept the data packet from client and verify

}
void zajr_bishtar()
{
    int len = sizeof(client);
    client_socket = accept(server_socket, (SA *)&client, &len);
    if (client_socket < 0)
    {

        printf("Server acceptance failed...\n");
        exit(0);
    }
    else
        printf("Server accepted the client..\n");
}
// Function designed for chat between client and server.
void chat()
{
    char buffer[2000];
    int n;
    static int pio=0;
    memset(buffer, 0, sizeof(buffer));
    //client_socket = zajr();
    // Read the message from client and copy it to buffer
    recv(client_socket, buffer, sizeof(buffer), 0);

    // Print buffer which contains the client message
    printf("From client: %s", buffer);
    char dastoor[100];
    sscanf(buffer,"%s",dastoor);
    printf("%s",dastoor);
    if (strcmp(dastoor,"register")==0)
    {
        reg(buffer);
        strcpy(buffer,ans);
    }
    else if (strcmp(dastoor,"login")==0)
    {
        login(buffer);
        strcpy(buffer,ans);
    }
    else if (strcmp(dastoor,"create")==0)
    {
        create(buffer);
        strcpy(buffer,ans);
    }
    else if (dastoor[0] == 'j')
    {
        join(buffer);
        strcpy(buffer,ans);
    }
    else if (dastoor[0] == 's')
    {
        sendch(buffer);
        strcpy(buffer,ans);
    }
    else if (strcmp(dastoor,"refresh")==0)
    {
        refresh(buffer);
        strcpy(buffer,ans);
    }else if (strcmp(dastoor, "channel") == 0)
    {
        channel_members(buffer);
        strcpy(buffer,ans);
    }else if (strcmp(dastoor,"leave") == 0)
    {
        leave(buffer);
        strcpy(buffer,ans);
    }else if (strcmp(dastoor,"logout") == 0)
    {
        logout(buffer);
        strcpy(buffer,ans);
    }
    /*
    char name[100];
    sscanf(buffer,"%s",name);
    printf("\n%s %s",dastoor,name);*/
    //memset(buffer , 0, sizeof(buffer));
    n = 0;
    // Copy server message to the buffer

    //scanf("%s",buffer);

    // Send the buffer to client
    send(client_socket, buffer, sizeof(buffer), 0);

    // If the message starts with "exit" then server exits and chat ends
    if (strncmp("exit", buffer, 4) == 0)
    {
        printf("Server stopping...\n");
        return;
    }

}

// Driver function
int main()
{
  //  printf("\n:\=%s\n",yaroo[1].password);

    strcpy(auth,"ABCDFGHIJKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz1234567890-=;.,kjsdhfsdkjf`");




    // Function for chatting between client and server
    while (true)
    {
        zajr();
        zajr_bishtar();
        chat();
        closesocket(server_socket);
        //closesocket(server_socket);
    }

}

int  channelcheck(int sh)
{
    if (yaroo[sh].b == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void reg(char*buffer)
{
    char name[100];
    char pass[100];
    char name1[100];
    char pass1[100];
    int flag = 0;
    sscanf(buffer + 8,"%s %s",name,pass);
    name[strlen(name)-1]='\0';
    //printf("\n%s %s",name,pass);
    FILE* fptr = fopen("database.txt","a+");
    rewind(fptr);
    while (true)
    {
        char c = fgetc(fptr);
        if (c == EOF)
        {
            break;
        }
        else
        {
            ungetc(c,fptr);
            fscanf(fptr,"%s %s",name1,pass1);
            if (name1[0] == name[0] && strlen(name1) == strlen(name))
            {
                flag=1;
                for (int i = 0 ; i < strlen(name1); i++)
                    if (name1[i] != name[i])
                    {
                        flag = 0;
                    }
            }
        }
    }
    if (flag == 0)
    {
        fprintf(fptr,"%s %s\n",name,pass);
        char res[1000];
        obj(res);
        additemtoobj(res,"type","Succesfull");
        additemtoobj(res,"content","");
        ans = res;
        printf("%s",ans);
    }
    if (flag == 1)
    {
        char res[1000];
        obj(res);
        additemtoobj(res,"type","Error");
        additemtoobj(res,"content","this username is not available");
        ans = res;
        printf("%s",ans);
    }

    fclose(fptr);
}
void login(char * buffer)
{
    char name[100];
    char pass[100];
    char name1[100];
    char pass1[100];
    int fla = 0;
    int flag = 0;
    int flag1 = 0;
    sscanf(buffer + 5,"%s %s",name,pass);
    name[strlen(name)-1]='\0';
    for (int i = 0 ; i < 100 ; i++)
    {
        if (strcmp(name,yaroo[i].username)== 0 && yaroo[i].a == 1)
        {
            fla = 1;
        }

    }
    if (fla == 0)
    {
    FILE* fptr = fopen("database.txt","a+");
    rewind(fptr);
    while (true)
    {
        char c = fgetc(fptr);
        if (c == EOF)
        {
            break;
        }
        else
        {
            ungetc(c,fptr);
            fscanf(fptr,"%s %s",name1,pass1);
            if (strcmp(name1,name)==0)
            {
                flag = 1;
            }
            if ( strcmp(name1,name) == 0 && strcmp(pass1,pass) == 0)
            {
                flag1 = 1;
            }

        }
    }
    if (flag == 0)
    {
        //cJSON *res;
        char res[1000];
        obj(res);
        additemtoobj(res,"type","Error");
        additemtoobj(res,"content","Username is not valid");
        printf("%s",ans);
        ans = res;
        //cJSON_Delete(res);
    }
    else if (flag1 == 0)
    {
        char res[1000];
        obj(res);
        additemtoobj(res,"type","Error");
        additemtoobj(res,"content","Wrong password");
        ans = res;
        printf("%s",ans);
    }
    else
    {

        char res[1000];
        obj(res);
        additemtoobj(res,"type","AuthToken");
        autt();
        additemtoobj(res,"content",auth_token);
        int sh = 0;
        for (int i = 0 ; i < 100 ; i++)
        {
            if (yaroo[i].a==0)
            {
                sh = i;
                break;
            }


        }
        yaroo[sh].a=1;
        strcpy(yaroo[sh].username,name);
        strcpy(yaroo[sh].password,pass);
        strcpy(yaroo[sh].auth_tokenu,auth_token);
        ans = res;
        //printf("%s",ans);

    //    cJSON_Delete(res);
    }
    }
    else
    {
        char res[1000];
        obj(res);
        additemtoobj(res,"type","Error");
        additemtoobj(res,"content","This user is online");
        printf("%s",ans);
        ans = res;
    }


}
void autt()
{
    int tmp;
    srand(time(NULL));
    for (int i = 0 ; i < 32 ; i++)
    {
        tmp = rand() % 69;
        // printf(" %d ",tmp);
        //printf("\n%c %d\n",auth[tmp],tmp);
        auth_token[i]=auth[tmp];
        //printf("%d\n%c\n",i,auth_token,auth[tmp]);
    }
}
void create(char*buffer)
{
    int flag = 0;
    char auth_tokenf[100];
    char channel_name[100];
    int sh=0;
    sscanf(buffer + 14,"%s %s",channel_name,auth_tokenf);
    //printf("\n%s\n",auth_tokenf);
    channel_name[strlen(channel_name)-1]='\0';
    for (int i = 0 ; i < 100 ; i++)
    {
        if (strcmp(yaroo[i].auth_tokenu,auth_tokenf)==0)
        {
            flag = 1;
            sh = i;
        }
    }
    if (flag == 1)
    {
        int flag = 0 ;
        char channel_name1[100];
        FILE* fptr = fopen("database_name_channel.txt","a+");
        rewind(fptr);
        while (true)
        {
            char c = fgetc(fptr);
            if (c == EOF)
            {
                break;
            }
            else
            {
                ungetc(c,fptr);
                fscanf(fptr,"%s",channel_name1);
                if (strcmp(channel_name1,channel_name)==0 )
                {
                    flag = 1;
                }
            }

        }
        if (flag == 1)
        {
            char res[1000];
            obj(res);
            additemtoobj(res,"type","Error");
            additemtoobj(res,"content","Channel name is not available");
            ans = res;
            printf("%s",ans);
            //cJSON_Delete(res);
        }
        else
        {
            fprintf(fptr,"%s\n",channel_name);
            yaroo[sh].b=1;
            strcpy(yaroo[sh].channel_name_user,channel_name);
            //fprintf(fptr,"%s %s\n",name,pass);
            char res[100];
            obj(res);
            additemtoobj(res,"type","Succesfull");
            additemtoobj(res,"content","");
            ans = res;
            printf("%s",ans);
            strcpy(channel_name1,channel_name);
            strcat(channel_name,".txt");
            FILE *fptr1= fopen(channel_name,"a+");
            fprintf(fptr1,"sender server : %s Created %s\n",yaroo[sh].username,channel_name1);
            fclose(fptr1);
            fclose(fptr);
            printf("%s",ans);
            //cJSON_Delete(res);

        }
    }
    else
    {
        char res[1000];
        obj(res);
        additemtoobj(res,"type","Error");
        additemtoobj(res,"content","Channel name is not available");
        ans = res;
        printf("%s",ans);
        //cJSON_Delete(res);
    }

}
void join(char *buffer)
{
    int flag = 0;
    char auth_tokenf[100];
    char channel_name[100];
    int sh=0;
    sscanf(buffer + 12,"%s %s",channel_name,auth_tokenf);
    //printf("\n%s\n",auth_tokenf);
    channel_name[strlen(channel_name)-1]='\0';
    for (int i = 0 ; i < 100 ; i++)
    {
        if (strcmp(yaroo[i].auth_tokenu,auth_tokenf)==0)
        {
            flag = 1;
            sh = i;
        }
    }
    if (flag == 1)
    {
        int flag = 0 ;
        char channel_name1[100];
        FILE* fptr = fopen("database_name_channel.txt","a+");
        rewind(fptr);
        while (true)
        {
            char c = fgetc(fptr);
            if (c == EOF)
            {
                break;
            }
            else
            {
                ungetc(c,fptr);
                fscanf(fptr,"%s",channel_name1);
                if (strcmp(channel_name1,channel_name)==0 )
                {
                    flag = 1;
                }
            }

        }
        if (flag == 0)
        {
            char res[1000];
            obj(res);
            additemtoobj(res,"type","Error");
            additemtoobj(res,"content","Channel name is not valid");
            ans = res;
            printf("%s",ans);
            //cJSON_Delete(res);
        }
        else
        {
            yaroo[sh].b=1;
            strcpy(yaroo[sh].channel_name_user,channel_name);
            char res[100];
            obj(res);
            additemtoobj(res,"type","Succesfull");
            additemtoobj(res,"content","");
            ans = res;
            printf("%s",ans);
            strcat(channel_name,".txt");
            FILE *fptr1 = fopen(channel_name,"a+");
            fprintf(fptr1,"sender server : %s Joined\n",yaroo[sh].username);
            fclose(fptr1);
            printf("%s",ans);
            // cJSON_Delete(res);

        }
    }
    else
    {
            char res[1000];
            obj(res);
            additemtoobj(res,"type","Error");
            additemtoobj(res,"content","Authtoken is not valid");
            ans = res;
    }
}
void sendch(char * buffer)
{
    char auth_tokenf[100];
    sscanf(buffer + strlen(buffer)-33,"%s",auth_tokenf);
    //printf("\n%s\n",auth_token1);
    int flag = 0;
    int sh = 0;
    for (int i = 0 ; i < 100 ; i++)
    {
        if (strcmp(yaroo[i].auth_tokenu,auth_tokenf) == 0)
        {
            flag = 1;
            sh = i;
        }
    }
    if (flag == 1)
    {
        char message[2000];
        strncpy(message,buffer + 5,strlen(buffer)-36-4);
        message[strlen(buffer)-40]=0;
        printf("%s",message);
        char channel_name[100];
        strcpy(channel_name,yaroo[sh].channel_name_user);
        char res[100];
        obj(res);
        additemtoobj(res,"type","Succesfull");
        additemtoobj(res,"content","");
        ans = res;
        printf("%s",ans);
        strcat(channel_name,".txt");
        FILE *fptr1 = fopen(channel_name,"a+");
        fprintf(fptr1,"sender %s : %s \n",yaroo[sh].username,message);
        fclose(fptr1);
        printf("%s",ans);

    }
    else
    {
            char res[1000];
            obj(res);
            additemtoobj(res,"type","Error");
            additemtoobj(res,"content","Authtoken is not valid");
            ans = res;
    }
}
void refresh(char*buffer)
{


    char auth_tokenf[100];
    sscanf(buffer  + 7,"%s",auth_tokenf);
    //printf("\n%s\n",auth_token1);
    int flag = 0;
    int sh = 0;
    for (int i = 0 ; i < 100 ; i++)
    {
        if (strcmp(yaroo[i].auth_tokenu,auth_tokenf) == 0)
        {
            flag = 1;
            sh = i;
        }
    }
    if (flag == 1)
    {

        char  cmessage[1000];
        char  res[1000];
        obj(res);
        arr(cmessage);
        additemtoobj(res,"type","List");
        char channel_name[100];
        strcpy(channel_name,yaroo[sh].channel_name_user);
        strcat(channel_name,".txt");
        FILE *fptr = fopen(channel_name,"a+");
        fseek(fptr,yaroo[sh].fp,SEEK_SET);
        while (true)
        {
            char c = fgetc(fptr);
            printf("\nc=%d\n",c);
            char message[1000];
            char username[100];
            char tmp[10];
            if (c == EOF)
            {
                break;
            }
            else
            {
                ungetc(c,fptr);
                fscanf(fptr,"%s",tmp);
                fscanf(fptr,"%s %s %[^\n]s",username,tmp,message);
                char emessage[1000];
                obj(emessage);
                additemtoobj(emessage, "sender",username);
                additemtoobj(emessage, "content",message);
                additemtoarr(cmessage, emessage );

                c = fgetc(fptr);
                printf("\nhoohoo");
                // ans = cJSON_PrintUnformatted(emessage);
                //cJSON_Delete(emessage);
                printf("\n%s %s %s\n",username,tmp,message);
            }

        }
        yaroo[sh].fp=ftell(fptr);
        fclose(fptr);
        additemtoobj(res,"message",cmessage);
        ans =  res;
        printf("%s",ans);
        //cJSON_Delete(res);

    }
    else
    {
            char res[1000];
            obj(res);
            additemtoobj(res,"type","Error");
            additemtoobj(res,"content","Authtoken is not valid");
            ans = res;
    }
}
void channel_members(char * buffer)
{
    char auth_tokenf[100];
    sscanf(buffer  + 15,"%s",auth_tokenf);
    int flag = 0;
    int sh = 0;
    for (int i = 0 ; i < 100 ; i++)
    {
        if (strcmp(yaroo[i].auth_tokenu,auth_tokenf) == 0)
        {
            flag = 1;
            sh = i;
        }
    }
    if (flag == 1)
    {
        char res[1000];
        char channel_members1[1000];
        obj(res);
        arr(channel_members1);
        additemtoobj(res,"type","List");
        for (int i = 0 ; i < 100 ; i++)
        {
            if (strcmp(yaroo[i].channel_name_user,yaroo[sh].channel_name_user) == 0)
            {
                additemtoarr(channel_members1,yaroo[i].username);
            }
        }
        additemtoobj(res,"content",channel_members1);
        ans = res;
        printf("%s",ans);
       // cJSON_Delete(res);
    }
    else
    {
            char res[1000];
            obj(res);
            additemtoobj(res,"type","Error");
            additemtoobj(res,"content","Authtoken is not valid");
            ans = res;
    }
}
void leave (char *buffer)
{
    char auth_tokenf[100];
    sscanf(buffer  + 5,"%s",auth_tokenf);
    int flag = 0;
    int sh = 0;
    for (int i = 0 ; i < 100 ; i++)
    {
        if (strcmp(yaroo[i].auth_tokenu,auth_tokenf) == 0)
        {
            flag = 1;
            sh = i;
        }
    }
    if (flag == 0)
    {
            char res[1000];
            obj(res);
            additemtoobj(res,"type","Error");
            additemtoobj(res,"content","Authtoken is not valid");
            ans = res;
    }
    else
    {
    if (channelcheck(sh))
    {
        yaroo[sh].b=0;
        strcpy(yaroo[sh].channel_name_user,"0");
        yaroo[sh].fp=0;
        //fprintf(fptr,"%s %s\n",name,pass);
        char res[1000];
        obj(res);
        additemtoobj(res,"type","Succesfull");
        additemtoobj(res,"content","");
        ans = res;
        printf("%s",ans);
    }
    else
    {
       // fprintf(fptr,"%s %s\n",name,pass);
        char res[1000];
        obj(res);
        additemtoobj(res,"type","Error");
        additemtoobj(res,"content","He is not a member of the channel");
        ans = res;
        printf("%s",ans);
    }
    }
}
void logout(char*buffer)
{

    char auth_tokenf[100];
    sscanf(buffer  + 6,"%s",auth_tokenf);
    int flag = 0;
    int sh = 0;
    for (int i = 0 ; i < 100 ; i++)
    {
        if (strcmp(yaroo[i].auth_tokenu,auth_tokenf) == 0)
        {
            flag = 1;
            sh = i;
        }
    }
    if (flag == 1)
    {
        yaroo[sh].a = 0;
        strcpy(yaroo[sh].username , "0");
        strcpy(yaroo[sh].password,"0");
        strcpy(yaroo[sh].auth_tokenu,"0");
        char res[100];
        obj(res);
        additemtoobj(res,"type","Succesfull");
        additemtoobj(res,"content","");
        ans = res;
        printf("%s",ans);
        printf("%s",ans);
        //cJSON_Delete(res);

    }
    else
    {
            char res[1000];
            obj(res);
            additemtoobj(res,"type","Error");
            additemtoobj(res,"content","Authtoken is not valid");
            ans = res;
    }
}

void obj(char s[])
{
    s[0]= '{';
    s[1] = '}';
    s[2] = 0;


}
void additemtoobj(char *s,char *type, char *r)
{
    if (r[0] == '[')
    {
        if (strlen(s) != 2)
        {
            s[strlen(s)-1] = ',';
            int sh = strlen(s);
            for (int i = 0 ; i <= strlen(type) ; i++)
            {
                if (i == 0)
                {
                    s[sh + i] = '"';
                }
                else
                    s[sh + i] = type[i-1];
            }
            s[sh + strlen(type)+1] = '"';
            s[sh +strlen(type) + 2] =':';
            s[sh + strlen(type) + 3] = 0;
            sh = strlen(s);
            for (int i = 0 ; i < strlen(r) ; i++)
            {
                s[sh + i] = r[i];
            }

            s[sh + strlen(r)] = '}';
            s[sh +strlen(r) + 1] =0;

        }
        else
        {

            int sh = strlen(s)-1;
            for (int i = 0 ; i <= strlen(type) ; i++)
            {
                if (i == 0)
                {
                    s[sh + i] = '"';
                }
                else
                    s[sh + i] = type[i-1];
            }
            s[sh + strlen(type)+1] = '"';
            s[sh +strlen(type) + 2] =':';
            s[sh + strlen(type) + 3] = 0;
            sh = strlen(s);
            for (int i = 0 ; i < strlen(r) ; i++)
            {

                s[sh + i] = r[i];
            }

            s[sh + strlen(r)] = '}';
            s[sh +strlen(r) + 1] =0;
        }
    }
    else
    {
        if (strlen(s) != 2)
        {
            s[strlen(s)-1] = ',';
            int sh = strlen(s);
            for (int i = 0 ; i <= strlen(type) ; i++)
            {
                if (i == 0)
                {
                    s[sh + i] = '"';
                }
                else
                    s[sh + i] = type[i-1];
            }
            s[sh + strlen(type)+1] = '"';
            s[sh +strlen(type) + 2] =':';
            s[sh + strlen(type) + 3] = 0;
            sh = strlen(s);
            for (int i = 0 ; i <= strlen(r) ; i++)
            {
                if (i == 0)
                {
                    s[sh + i] = '"';
                }
                else
                    s[sh + i] = r[i-1];
            }
            s[sh + strlen(r)+1] = '"';
            s[sh + strlen(r)+2] = '}';
            s[sh +strlen(r) + 3] =0;

        }
        else
        {

            int sh = strlen(s)-1;
            for (int i = 0 ; i <= strlen(type) ; i++)
            {
                if (i == 0)
                {
                    s[sh + i] = '"';
                }
                else
                    s[sh + i] = type[i-1];
            }
            s[sh + strlen(type)+1] = '"';
            s[sh +strlen(type) + 2] =':';
            s[sh + strlen(type) + 3] = 0;
            sh = strlen(s);
            for (int i = 0 ; i <= strlen(r) ; i++)
            {
                if (i == 0)
                {
                    s[sh + i] = '"';
                }
                else
                    s[sh + i] = r[i-1];
            }
            s[sh + strlen(r)+1] = '"';
            s[sh + strlen(r)+2] = '}';
            s[sh +strlen(r) + 3] =0;
        }
    }
}
void arr(char * s)
{
    s[0] = '[';
    s[1] = ']';
    s[2] = 0;
}
void additemtoarr (char * s, char *r)
{
    if (r[0] == '{')
    {
        if (strlen(s) == 2)
        {
            int sh = strlen(s)-1;
            for (int i = 0 ; i < strlen(r) ; i++)
            {
                s[sh + i] = r[i];
            }

            s[sh + strlen(r)] = ']';
            s[sh +strlen(r) + 1] =0;
        }
        else
        {
            s[strlen(s)-1] = ',';
            int sh = strlen(s);
            for (int i = 0 ; i < strlen(r) ; i++)
            {
                s[sh + i] = r[i];
            }

            s[sh + strlen(r)] = ']';
            s[sh +strlen(r) + 1] =0;
        }
    }
    else
    {
        if (strlen(s) == 2)
        {
            int sh = strlen(s)-1;
            for (int i = 0 ; i <= strlen(r) ; i++)
            {
                if (i == 0)
                {
                    s[sh + i] = '"';
                }
                else
                    s[sh + i] = r[i-1];
            }
            s[sh + strlen(r)+1] = '"';
            s[sh +strlen(r) + 2] =']';
            s[sh + strlen(r) + 3] = 0;
            sh = strlen(s);
        }
        else
        {

            s[strlen(s) - 1] = ',';
            int sh = strlen(s);
            for (int i = 0 ; i <= strlen(r) ; i++)
            {
                if (i == 0)
                {
                    s[sh + i] = '"';
                }
                else
                    s[sh + i] = r[i-1];
            }
            s[sh + strlen(r)+1] = '"';
            s[sh +strlen(r) + 2] =']';
            s[sh + strlen(r) + 3] = 0;
            sh = strlen(s);
        }
    }
}

