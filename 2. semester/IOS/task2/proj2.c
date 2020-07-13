// xbobro01 Ivan Bobrov 1BIT for IOS
#include "proj2.h"

int load_res() {
    // initializing semaphores
    int ret = 0;
    j_enter_sem = sem_open(J_ENTER_SEM, O_CREAT, 0666, CLOSED);
    if (j_enter_sem == SEM_FAILED) {
        fprintf(stderr, "%s/n", "Failed to open semphore");
        ret = 1;
    }
    j_immreg_sem = sem_open(J_IMMREG_SEM, O_CREAT, 0666, CLOSED);
    if (j_immreg_sem == SEM_FAILED) {
        fprintf(stderr, "%s/n", "Failed to open semphore");
        ret = 1;
    }
    imm_enter_sem = sem_open(IMM_ENTER_SEM, O_CREAT, 0666, OPENED);
    if (imm_enter_sem == SEM_FAILED) {
        fprintf(stderr, "%s/n", "Failed to open semphore");
        ret = 1;
    }
    imm_confwait_sem = sem_open(IMM_CONFWAIT_SEM, O_CREAT, 0666, CLOSED);
    if (imm_confwait_sem == SEM_FAILED) {
        fprintf(stderr, "%s/n", "Failed to open semphore");
        ret = 1;
    }
    act_change_sem = sem_open(ACT_CHANGE_SEM, O_CREAT, 0666, OPENED);
    if (act_change_sem == SEM_FAILED) {
        fprintf(stderr, "%s/n", "Failed to open semphore");
        ret = 1;
    }

    // allocating shared memory
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    mem = mmap(NULL, sizeof(struct Actual_inf), protection, visibility,-1, 0);
    if (mem == MAP_FAILED) {
        fprintf(stderr, "%s/n", "Memory map creation failed");
        ret = 1;
    }

    // default structer variables setting
    mem->PROCESS_ID = 0;
    mem->IMM_COUNT = 0;
    mem->IMM_W_CERT = 0;
    mem->IMM_W_CERT_FLAG = 0;
    mem->J_IN_B = 0;
    mem->J_WAITS_FOR_IMM = 0;
    mem->IMM_CONFIRMED = 0;
    mem->NB = 0;
    mem->NC = 0;
    mem->NE = 0;

    return(ret);
}

int clean_res() { 
    int ret = 0;
    // deleting semaphores
    if(sem_close(j_enter_sem) == -1) {
        fprintf(stderr, "%s %s\n", "Cannot close semaphore", J_ENTER_SEM);
        ret = 1;
    }
    if(sem_close(j_immreg_sem) == -1) {
        fprintf(stderr, "%s %s\n", "Cannot close semaphore", J_IMMREG_SEM);
        ret = 1;
    }
    if(sem_close(imm_enter_sem) == -1) {
        fprintf(stderr, "%s %s\n", "Cannot close semaphore", IMM_ENTER_SEM);
        ret = 1;
    }
    if(sem_close(imm_confwait_sem) == -1) {
        fprintf(stderr, "%s %s\n", "Cannot close semaphore", IMM_CONFWAIT_SEM);
        ret = 1;
    }
    if(sem_close(act_change_sem) == -1) {
        fprintf(stderr, "%s %s\n", "Cannot close semaphore", ACT_CHANGE_SEM);
        ret = 1;
    }
    
    if (sem_unlink(J_ENTER_SEM) == -1) {
        fprintf(stderr,"Cannot unlink semaphore 1!\n");
        ret = 1;
    }
    if (sem_unlink(J_IMMREG_SEM) == -1) {
        fprintf(stderr,"Cannot unlink semaphore 1!\n");
        ret = 1;
    }
    if (sem_unlink(IMM_ENTER_SEM) == -1) {
        fprintf(stderr,"Cannot unlink semaphore 1!\n");
        ret = 1;
    }
    if (sem_unlink(IMM_CONFWAIT_SEM) == -1) {
        fprintf(stderr,"Cannot unlink semaphore 1!\n");
        ret = 1;
    }
    if (sem_unlink(ACT_CHANGE_SEM) == -1) {
        fprintf(stderr,"Cannot unlink semaphore 1!\n");
        ret = 1;
    }

    // freeing shared memory
    if(munmap(mem, sizeof(struct Actual_inf)) == -1) {
        fprintf(stderr, "%s\n", "munmap failed");
        ret = 1;
    }

    return ret;
}

void random_sleep(int ms) {
    if (ms == 0) {
        usleep(0);
    } else {
        // get random value and change it to microseconds
        int sleep_time_microsec = (rand() % ms) * 1000;
        usleep(sleep_time_microsec);
    }
}

int params_check(struct Params *params, char *endptr_ig, char *endptr_jg, char *endptr_it, char *endptr_jt) {
    // check if params contains invalid symbols
    if (strcmp("", endptr_ig) 
        || strcmp("", endptr_jg) 
        || strcmp("", endptr_it) 
        || strcmp("", endptr_jt)
        ) 
    {
        fprintf(stderr, "%s\n", "Wrong argument type");
        return 1;
    }
    else if (params->PI < 1 // check if arguments are in needed range 
        || (params->IG < 0 && params->IG > 2000) 
        || (params->JG < 0 && params->JG > 2000) 
        || (params->IT < 0 && params->IT > 2000)
        || (params->JT < 0 && params->JT > 2000)
        )
    {
        fprintf(stderr, "%s\n", "Argument out of range");
        return 1;
    }
    return 0;
}

void my_fprintf(FILE *file, char *person, int self_id, char *action, int extended_info) {
    // case for immigrant
    sem_wait(act_change_sem);
    if (strcmp(person, IMM_NAME) == 0) {
        if (extended_info == 0) {
            if (strcmp(action, "starts") == 0) {
                fprintf(file, "%-10d: %s %-10d: %-20s\n", ++(mem->PROCESS_ID), IMM_NAME, self_id, "starts");
            }
        } else {
            if (strcmp(action, "enters") == 0) {
                mem->NE++;
                mem->NB++;
            } else if (strcmp(action, "checks") == 0) {
                mem->NC++;
            } else if (strcmp(action, "leaves") == 0) {
                mem->NB--;
            }
            fprintf(file, "%-10d: %s %-10d: %-20s: %-5d: %-5d: %-5d\n",
            ++(mem->PROCESS_ID), IMM_NAME, self_id, action, mem->NE, mem->NC, mem->NB);
        }
    }
    // case for judge
    else {
        if (extended_info == 0) {
            if (strcmp(action, "wants to enter") == 0) {
                fprintf(file, "%-10d: %-14s: %-20s\n", ++(mem->PROCESS_ID), J_NAME, "wants to enter");
            } else {
                fprintf(file, "%-10d: %-14s: %-20s\n", ++(mem->PROCESS_ID), J_NAME, "finishes");

            }
        }
        else {
            if (strcmp(action, "ends confirmation") == 0) {
                mem->IMM_W_CERT+= mem->NC;
                mem->NC = 0;
                mem->NE = 0;
            }
            fprintf(file, "%-10d: %-14s: %-20s: %-5d: %-5d: %-5d\n",
            ++(mem->PROCESS_ID), J_NAME, action, mem->NE, mem->NC, mem->NB);
        }
    }
    sem_post(act_change_sem);
   // fflush(file);
}

void immigrant_process(FILE *file, struct Params *params) {
    sem_wait(act_change_sem);
    int self_id = ++(mem->IMM_COUNT); // imm gets own self id
    sem_post(act_change_sem); 
    
    my_fprintf(file, IMM_NAME, self_id, "starts", 0);

    sem_wait(imm_enter_sem);
    my_fprintf(file, IMM_NAME, self_id, "enters", 1);
    sem_post(imm_enter_sem);

    my_fprintf(file, IMM_NAME, self_id, "checks", 1);

    // if registred imm = imm at the building, send signal to judge to continue
    sem_wait(act_change_sem);
    if (mem->NC == mem->NE && mem->J_WAITS_FOR_IMM == 1) {
        sem_post(j_immreg_sem);
        sem_post(act_change_sem);
    }
    else {
        sem_post(act_change_sem);
    }
    
    sem_wait(imm_confwait_sem); // waits for confirmation
    
    sem_wait(act_change_sem);
    (mem->IMM_CONFIRMED)--;
    if (mem->IMM_CONFIRMED > 0) {
        sem_post(imm_confwait_sem);
    }
    sem_post(act_change_sem);

    my_fprintf(file, IMM_NAME, self_id, "wants certificate", 1);
    random_sleep(params->IT); // judge making his decision
    my_fprintf(file, IMM_NAME, self_id, "got certificate", 1);

    sem_wait(imm_enter_sem);    
    my_fprintf(file, IMM_NAME, self_id, "leaves", 1);
    sem_post(imm_enter_sem);
    
    exit(0);
}

void judge_process(FILE *file, struct Params *params) {
    sem_wait(j_enter_sem);
    while(mem->IMM_W_CERT < params->PI) {
        random_sleep(params->JG);
        my_fprintf(file, J_NAME, 0, "wants to enter", 0);

        // when enters -> stop immigrants to enter (1->0)
        sem_wait(imm_enter_sem);
        
        my_fprintf(file, J_NAME, 0, "enters", 1);

        // if registred imm < imm at the building, waits for them
        sem_wait(act_change_sem);
        if (mem->NE != mem->NC) {
            mem->J_WAITS_FOR_IMM = 1;
            sem_post(act_change_sem);
            my_fprintf(file, J_NAME, 0, "waits for imm", 1);
            sem_wait(j_immreg_sem);
            sem_post(act_change_sem);
        } else {
            sem_post(act_change_sem);
        }

        my_fprintf(file, J_NAME, 0, "starts confirmation", 1);
        random_sleep(params->JT);

        sem_wait(act_change_sem);
        mem->IMM_CONFIRMED+=mem->NC;
        if (mem->NC != 0) {
            mem->IMM_W_CERT_FLAG = 1;
        }
        sem_post(act_change_sem);

        my_fprintf(file, J_NAME, 0, "ends confirmation", 1);

        sem_wait(act_change_sem);
        if (mem->IMM_W_CERT_FLAG == 1) {
            mem->IMM_W_CERT_FLAG = 0;
            sem_post(imm_confwait_sem);
        }
        sem_post(act_change_sem);

        random_sleep(params->JT);
        my_fprintf(file, J_NAME, 0, "leaves", 1);

        sem_post(imm_enter_sem);
    }
    my_fprintf(file, J_NAME, 0, "finishes", 0);
    
    exit(0);
}

int main(int argv, char **argc) {
    // argument validation
    if (argv != num_of_args) {
        fprintf(stderr, "%s\n", "You should enter 5 arguments");
        return 1;
    }
    
    struct Params params;
    char *endptr_ig, *endptr_jg, *endptr_it, *endptr_jt;
    params.PI = strtol(argc[1], NULL, int_base);
    params.IG = strtol(argc[2], &endptr_ig, int_base);
    params.JG = strtol(argc[3], &endptr_jg, int_base);
    params.IT = strtol(argc[4], &endptr_it, int_base);
    params.JT = strtol(argc[5], &endptr_jt, int_base);

    // validate params
    if(params_check(&params, endptr_ig, endptr_jg, endptr_it, endptr_jt)) {
        return 1;
    }
    
    // try to open file proj2.out
    FILE *file = fopen(FILE_NAME, FILE_MODE);
    if (file == NULL) {
        fclose(file);
        fprintf(stderr, "%s\n", "Failed to open file proj2.out");
        return 1;
    }
    setbuf(file, NULL);

    // try to load additional resources
    if (load_res()) {
        clean_res();
        return 1;
    }

    pid_t immigrant;
    pid_t f_immigrant;
    pid_t judge;

    // create judge process
    judge = fork();
    if (judge == 0) {
        judge_process(file, &params); // algorithm for judge
    } else if (judge > 0) { // if judge was already created
        f_immigrant = fork();
        if (f_immigrant == 0) {
            sem_post(j_enter_sem); // let judge process start, when first imm entered
            for (int i = 0; i < params.PI; ++i) {
                immigrant = fork();
                random_sleep(params.IG);
                if (immigrant == 0) {
                    immigrant_process(file, &params); // algorithm for immigrant
                }
            }
            waitpid(immigrant, NULL, 0);
            exit(0);
        } else if (f_immigrant < 0){
            fprintf(stderr, "%s\n", "Could not create immigrant child process");
            clean_res();
            return 1;
        }
    } else {
        fprintf(stderr, "%s\n", "Could not create judge child process");
        clean_res();
        return 1;
    }
    
    // wait for processes ending end clean initialized resources
    waitpid(f_immigrant, NULL, 0);
    waitpid(judge, NULL, 0);
    if(clean_res()) {
        return 1;
    }
    fclose(file);
    return 0;
}