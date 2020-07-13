// xbobro01 Ivan Bobrov 1BIT for IOS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define num_of_args 6
#define int_base 10

#define IMM_NAME "IMM"
#define J_NAME "JUDGE"

#define FILE_NAME "proj2.out"
#define FILE_MODE "w"

#define J_ENTER_SEM "/sem1"
#define J_IMMREG_SEM "/sem2"
#define IMM_ENTER_SEM "/sem3"
#define IMM_CONFWAIT_SEM "/sem5"
#define ACT_CHANGE_SEM "/sem7"


#define OPENED 1
#define CLOSED 0

sem_t *j_enter_sem;
sem_t *j_immreg_sem;
sem_t *imm_enter_sem;
sem_t *imm_confwait_sem;
sem_t *act_change_sem;


// input params structure
struct Params {
    int PI; // number of immigrants to be created
    int IG; // time to generate next immigrant
    int JG; // time to judge returning to rhe building
    int IT; // time to certificate creation
    int JT; // time to getting certificate
};

// structure with actual information 
struct Actual_inf {
    int PROCESS_ID; // process id
    int J_IN_B; // judge in building flag
    int J_WAITS_FOR_IMM; // judge waiting for immigrants flag
    int IMM_COUNT; // 
    int IMM_W_CERT; // immigrants with certificate
    int IMM_W_CERT_FLAG; // is at the building were immigrants to get confirmation
    int IMM_CONFIRMED; // imm with confirmation
    int NE; // unregistered immigrants without conformation
    int NC; // registered immigrants without conformation
    int NB; // number of immigrans at the building
};

struct Actual_inf actual_inf;
struct Actual_inf *mem = NULL; // pointer to shared memory

// function for resoures (semaphores, shared memory) initialising
int load_res();

// function for deleting semaphores and freeing shared memory
int clean_res();

// sleep function with random value (0, ms) in miliseconds 
void random_sleep(int ms);

// validate programm arguments
int params_check(struct Params *params, char *endptr_ig, char *endptr_jg, char *endptr_it, char *endptr_jt);

// safe write to file function
void my_fprintf(FILE *file, char *person, int self_id, char *action, int extended_info);

// immigrant algorithm
void immigrant_process(FILE *file, struct Params *params);

// judge algorithm
void judge_process(FILE *file, struct Params *params);