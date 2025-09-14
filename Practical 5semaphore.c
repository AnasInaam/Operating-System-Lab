#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int mutex = 1;
int full = 0;
int empty = 10, x = 0;
void producer()
{
    if(mutex == 1 && empty != 0) {
        wait(&empty);
        wait(&mutex);
        ++full;
        --empty;
        x++;
        printf("\nProducer produces item %d", x);
        signal(&mutex);
        signal(&full);
    } else {
        printf("Buffer is full!");
    }
}

void consumer()
{
    if(mutex == 1 && full != 0) {
        wait(&full);
        wait(&mutex);
        --full;
        ++empty;
        printf("\nConsumer consumes item %d", x);
        x--;
        signal(&mutex);
        signal(&empty);
    } else {
        printf("Buffer is empty!");
    }
}

int main()
{
    int n, i;
    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit");

    for (i = 1; i > 0; i++) {
        printf("\nEnter your choice:");
        scanf("%d", &n);

        switch (n) {
        case 1:
            producer();
            break;

        case 2:
            consumer();
            break;

        case 3:
            exit(0);
            break;
        }
    }
    return 0;
}




