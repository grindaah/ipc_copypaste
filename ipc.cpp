#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
//#include "mesg.h"
//
struct Message
{
    char* buff;
    size_t mtype;
};
int main()
{

Message message;
key_t key;
int msgid, length;

message.mtype = 1L;
if ((key = ftok("server", 'A')) < 0){
    printf("can't get key\n"); 
    return 1;
}
if ((msgid = msgget(key, IPC_CREAT)) < 0){
    int errmsg = errno;
    printf("errno=%d\n", errmsg);
    printf("errmsg = %s\n", strerror(errmsg));
    printf("can't get access to queue\n");
    return 1;
}
if ((length = sprintf(message.buff, "Hello, world ipc!\n")) < 0)
{
    printf("buffer copy error\n");
    return 1;
}
if (msgsnd(msgid, (void *) &message, length, 0) !=0)
{
    printf("Ошибка записи сообщения в очередь\n");
    return 1;
}
if (msgctl(msgid, IPC_RMID, 0) < 0)
{
    printf("Ошибка удаления очереди\n");
    return 1;
}

return 0;
}




