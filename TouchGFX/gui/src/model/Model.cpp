#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "cmsis_os.h"
#include "stdio.h"

extern osMessageQueueId_t mid_MsgQueue;

typedef struct {                                // object data type
  char Temp[10];
  char Hum[10];
} MSGQUEUE_OBJ_t;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	  MSGQUEUE_OBJ_t msg;
	  osStatus_t status;
	  status = osMessageQueueGet(mid_MsgQueue, &msg, NULL, 0U);   // wait for message
	     if (status == osOK) {
	       printf("stream Ok\r\n");
	       printf("Temp     = %s [°C] \r\n",msg.Temp);// process data
	       printf("Humitity = %s [%%] \r\n",msg.Hum);// process data
	       screenUpdate(msg.Temp,msg.Hum);
	     }
	     else{
	    	// printf("stream Wait\r\n");
	     }
}
void Model::screenUpdate(char temp[10],char hum[10])
{

	modelListener->screenUpdate(temp,hum);
}
