#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <json/json.h>
#include <time.h>

#define DEVICE_ID 1
#define PORT 2000
#define LOCALHOST "localhost"

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    time_t rawtime;
    struct tm * timeinfo;

    json_object * allData = json_object_new_object();
    json_object * jarray = json_object_new_array();
    json_object * data1 = json_object_new_object();
    json_object *deviceid = json_object_new_int(DEVICE_ID); 

    char buffer[256];
    /*if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }*/

    //portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(LOCALHOST);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); // clears buffer

    serv_addr.sin_family = AF_INET; 

    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    
    json_object_object_add(allData, "deviceid", deviceid);

    while(1)
    {   
        bzero(buffer,256);

        fgets(buffer,255,stdin);

        printf("%s\n", buffer);
        
        if(buffer[0] == 's')
        {
            printf("looop\n");

            time ( &rawtime );
            timeinfo = localtime ( &rawtime );  

            data1 = json_object_new_object();
           
            json_object *d1 = json_object_new_int(1);
            json_object *units = json_object_new_string("seconds");
            json_object *type1 = json_object_new_string("how many");
            json_object *time1 = json_object_new_string(asctime(timeinfo));         

            json_object_object_add(data1, "time", time1);
            json_object_object_add(data1, "type", type1);
            json_object_object_add(data1, "data", d1);
            json_object_object_add(data1, "units", units);

            json_object_array_add(jarray, data1);         

            printf("The json object created: %s\n",json_object_to_json_string(data1));
            printf("The json object created: %s\n",json_object_to_json_string(allData));
        }

        if(buffer[0] == 'd')
            break;
    }

    // add array to data object
    json_object_object_add(allData, "datas", jarray);

    // Send Message to server
    n = write(sockfd,json_object_to_json_string(allData),strlen(json_object_to_json_string(allData)));

    if (n < 0) 
         error("ERROR writing to socket");

    bzero(buffer,256);

    // Messages from server
    n = read(sockfd,buffer,255);

    if (n < 0) 
         error("ERROR reading from socket");

    printf("%s\n",buffer);

    return 0;
}