#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t chair_sem[3];
sem_t student;
sem_t ta_sleep;

/* threads */
pthread_t *Students;
pthread_t TA; // seprate thread for TA

int chair_count = 0;
int index_chair = 0;
int helped = 0; //variable to decide the number of students that can be helped by the TA
pthread_mutex_t ChairAccess;

void *TA_check()
{
    while (helped < 10)

    {
        sem_wait(&ta_sleep); //TA is currently sleeping.
        printf("Student Arrives\n");
        printf("    TA has been awakened by the student.\n");
        while (1)
        {
            // when TA is awakened, a student occupies chair so we have to put lock on chair.
            pthread_mutex_lock(&ChairAccess);
            if (chair_count == 0) // we will check if chairs are empty, if yes then we unlock the chairs and let student occupy the chair
            {
                //if chairs are empty, break the loop.
                pthread_mutex_unlock(&ChairAccess);
                break;
            }

            //TA gets next student on chair.

            sem_post(&chair_sem[index_chair]); // we signal that the chair has been occupied
            chair_count--;                     // chair is occupied, so count decrements
            printf("Student leaves chair in waiting room and goes to the TA. Remaining Chairs = %d\n", 3 - chair_count);
            index_chair = (index_chair + 1) % 3;
            pthread_mutex_unlock(&ChairAccess);
            // unlock chair access
            printf("\t TA is currently helping the student.\n");
            sleep(2);
            sem_post(&student);
            usleep(1000);
        }
    }
}

void *Student_Check(void *threadID)
{
    int Time_with_ta;
    while (helped < 10)

    {

        printf("Student %ld needs help from the TA\n", (long)threadID);
        pthread_mutex_lock(&ChairAccess); // as student comes, he sits on a chair, so we put lock
        int count = chair_count;

        pthread_mutex_unlock(&ChairAccess);
        if (count < 3) //if chair count < 3, students will sit and wait.
        {
            if (count == 0)          //If student sits on first empty chair, wake up the TA.
                sem_post(&ta_sleep); // wake up ta semaphore
            else
                printf("Student %ld sat on chair. Chairs Remaining: %d\n", (long)threadID, 3 - chair_count);
            pthread_mutex_lock(&ChairAccess); // mutex lock so no one can sit on preoccupied chair

            int index = (index_chair + chair_count) % 3;
            chair_count++;
            pthread_mutex_unlock(&ChairAccess);
            // unlock
            sem_wait(&chair_sem[index]); //Student leaves the chair.
            printf("\t Student %ld is getting help from the TA. \n", (long)threadID);
            sem_wait(&student); //Student waits to go next.
            printf("Student %ld leaves the TA room.\n", (long)threadID);
        }

        else
            printf("Student %ld will return at a later time. \n", (long)threadID);

        //If there are no chairs left .

        helped++;
    }
}

int main()
{
    int number_of_students;
    printf("Enter number of students: ");
    scanf("%d", &number_of_students);

    if (number_of_students == 0)
    {
        printf("TA continues sleeping");
        exit(0);
    }

    int id;
    srand(time(NULL));
    //Initializing Mutex Lock and Semaphores.

    sem_init(&ta_sleep, 0, 0);
    sem_init(&student, 0, 0);

    for (id = 0; id < 3; ++id) //Chairs array of 3 semaphores.
        sem_init(&chair_sem[id], 0, 0);
    pthread_mutex_init(&ChairAccess, NULL);
    Students = (pthread_t *)malloc(sizeof(pthread_t) * number_of_students);

    //Creating TA thread
    pthread_create(&TA, NULL, TA_check, (void *)(long)id);

    //Creating N student thread
    for (id = 0; id < number_of_students; id++)
        pthread_create(&Students[id], NULL, Student_Check, (void *)(long)id);

    pthread_join(TA, NULL);
    for (id = 0; id < number_of_students; id++)
        pthread_join(Students[id], NULL);
    free(Students);
    return 0;
}
