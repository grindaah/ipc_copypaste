#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
struct Message
{
    char* buff;
    size_t mtype;
};

int main()
{
    Message message;
    key_t key;
    int msgid, length, n;
    if ((key = ftok("server", 'A')) < 0){
    printf("Невозможно получить ключ\n"); return 1; }
    message.mtype=1L;
    if ((msgid = msgget(key, IPC_CREAT)) < 0){
    printf("Невозможно создать очередь\n"); 
    return 1; }
    n = msgrcv(msgid, &message, sizeof(message), message.mtype, 0);
    if (n > 0) {
        if (write(1, message.buff, n) != n) {
            printf("Ошибка вывода\n");
    return 1;
        }
    }
    else { printf("Ошибка чтения сообщения\n");
       return 1;
    }
    return 0;
}

