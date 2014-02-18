#include <stdio.h>
#include <json-c/json.h>
#include <time.h>
#include <stdlib.h> 

#define DEVICE_ID 1

void error(char *msg);

int main(int argc, char *argv[])
{
    time_t rawtime;
    struct tm * timeinfo;

    json_object * allData = json_object_new_object();
    json_object * jarray = json_object_new_array();
    json_object * data1 = json_object_new_object();
    json_object *deviceid = json_object_new_int(DEVICE_ID); 

    json_object_object_add(allData, "deviceid", deviceid);

    // add JSONs to JSON array 
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );  

    data1 = json_object_new_object();
   
    json_object *d1 = json_object_new_int(5);
    json_object *units = json_object_new_string("seconds");
    json_object *type1 = json_object_new_string("how many");
    json_object *time1 = json_object_new_string(asctime(timeinfo));         

    json_object_object_add(data1, "time", time1);
    json_object_object_add(data1, "type", type1);
    json_object_object_add(data1, "data", d1);
    json_object_object_add(data1, "units", units);

    json_object_array_add(jarray, data1);         

    printf("The json object created: %s\n",json_object_to_json_string(data1));
    //printf("The json object created: %s\n",json_object_to_json_string(allData));

    // add array to data object
    json_object_object_add(allData, "datas", jarray);
    json_object_to_json_string(allData);

    printf("curl -H 'Content-Type:application/json' -H 'Accept:application/json'-X POST http://localhost:3000/mattress_data -d %sn", json_object_to_json_string(allData));

    return 0;
}


// for good error messages
void error(char *msg)
{
    perror(msg);
    exit(0);
}