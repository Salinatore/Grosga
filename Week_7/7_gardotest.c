#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define PURPOSE_MAX 20 //max string length of purpose field
#define MAX_ROWS 10000 //number of row in the data file
#define DEVIDER ","
#define MAX_ROW_LENGTH 1000
#define PERCENT 0.75

typedef struct user{
    bool credit_policy;
    char* purpose;
    double int_rate;
    double installment;
    double log_annual_inc;
    double dti;
    unsigned int fico;
    double days_with_cr_line;
    double revol_bal;
    double revol_util;
    unsigned int inq_last_6mths;
    unsigned int delinq_2yrs;
    unsigned int pub_rec;
    bool not_fully_paid;
}USER;

int load_dataset(char file_path[], USER users[], USER* max, USER* min);
USER row_to_user(char row[], USER* max, USER* min, bool* is_first_time);
bool read_line(char row[MAX_ROW_LENGTH], FILE* data);
int* KNN_algorithm(USER test[], USER train[], int n_rows, int const K); //return a pointer to an array of 1 or 0
void normalize_user(USER* user,int n_rows, USER* max, USER* min);
double euclidean_distance(USER test, USER train);

int main(){
    USER users[MAX_ROWS];
    USER max, min;

    char file_path[] = {"Week_7/loan_data.csv"};

    int n_rows = load_dataset(file_path, users, &max, &min);

    normalize_user(users, n_rows, &max, &min);

}

int load_dataset(char file_path[], USER users[], USER* max, USER* min){
    FILE* data = fopen(file_path, "r");
    int n_rows = 0;
    bool is_first_time = true;

    if(data == NULL){
        perror("Error opening file");
        exit(1);
    }

    char row[MAX_ROW_LENGTH];

    read_line(row, data); //to skip the first row

    while(read_line(row, data) && n_rows < MAX_ROWS){
        users[n_rows] = row_to_user(row, max, min, &is_first_time);
        n_rows++;
    }

    fclose(data);

    return n_rows;
}

USER row_to_user(char row[], USER* max, USER* min, bool* is_first_time){
    USER user;
    char* purpose = (char*) malloc(PURPOSE_MAX);

    user.credit_policy = atoi(strtok(row, DEVIDER));
    if(user.credit_policy > max->credit_policy || *is_first_time == true)
        max->credit_policy = user.credit_policy;
    if(user.credit_policy < min->credit_policy || *is_first_time == true)
        min->credit_policy = user.credit_policy;

    user.purpose = strcpy(purpose, strtok(NULL, DEVIDER));
    if(user.purpose > max->purpose || *is_first_time == true)
        max->purpose = user.purpose;
    if(user.purpose < min->purpose || *is_first_time == true)
        min->purpose = user.purpose;

    user.int_rate = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.int_rate > max->int_rate || *is_first_time == true)
        max->int_rate = user.int_rate;
    if(user.int_rate < min->int_rate || *is_first_time == true)
        min->int_rate = user.int_rate;

    user.installment = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.installment > max->installment || *is_first_time == true)
        max->installment = user.installment;
    if(user.installment < min->installment || *is_first_time == true)
        min->installment = user.installment;

    user.log_annual_inc = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.log_annual_inc > max->log_annual_inc || *is_first_time == true)
        max->log_annual_inc = user.log_annual_inc;
    if(user.log_annual_inc < min->log_annual_inc || *is_first_time == true)
        min->log_annual_inc = user.log_annual_inc;

    user.dti = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.dti > max->dti || *is_first_time == true)
        max->dti = user.dti;
    if(user.dti < min->dti || *is_first_time == true)
        min->dti = user.dti;

    user.fico = atoi(strtok(NULL, DEVIDER));
    if(user.fico > max->fico || *is_first_time == true)
        max->fico = user.fico;
    if(user.fico < min->fico || *is_first_time == true)
        min->fico = user.fico;

    user.days_with_cr_line = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.days_with_cr_line > max->days_with_cr_line || *is_first_time == true)
        max->days_with_cr_line = user.days_with_cr_line;
    if(user.days_with_cr_line < min->days_with_cr_line || *is_first_time == true)
        min->days_with_cr_line = user.days_with_cr_line;

    user.revol_bal = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.revol_bal > max->revol_bal || *is_first_time == true)
        max->revol_bal = user.revol_bal;
    if(user.revol_bal < min->revol_bal || *is_first_time == true)
        min->revol_bal = user.revol_bal;

    user.revol_util = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.revol_util > max->revol_util || *is_first_time == true)
        max->revol_util = user.revol_util;
    if(user.revol_util < min->revol_util || *is_first_time == true)
        min->revol_util = user.revol_util;

    user.inq_last_6mths = atoi(strtok(NULL, DEVIDER));
    if(user.inq_last_6mths > max->inq_last_6mths || *is_first_time == true)
        max->inq_last_6mths = user.inq_last_6mths;
    if(user.inq_last_6mths < min->inq_last_6mths || *is_first_time == true)
        min->inq_last_6mths = user.inq_last_6mths;

    user.delinq_2yrs = atoi(strtok(NULL, DEVIDER));
    if(user.delinq_2yrs > max->delinq_2yrs || *is_first_time == true)
        max->delinq_2yrs = user.delinq_2yrs;
    if(user.delinq_2yrs < min->delinq_2yrs || *is_first_time == true)
        min->delinq_2yrs = user.delinq_2yrs;

    user.pub_rec = atoi(strtok(NULL, DEVIDER));
    if(user.pub_rec > max->pub_rec || *is_first_time == true)
        max->pub_rec = user.pub_rec;
    if(user.pub_rec < min->pub_rec || *is_first_time == true)
        min->pub_rec = user.pub_rec;

    user.not_fully_paid = atoi(strtok(NULL, DEVIDER));
    if(user.not_fully_paid > max->not_fully_paid || *is_first_time == true)
        max->not_fully_paid = user.not_fully_paid;
    if(user.not_fully_paid < min->not_fully_paid || *is_first_time == true)
        min->not_fully_paid = user.not_fully_paid;

    if(*is_first_time == true)
        *is_first_time = false;

    return user;
}

bool read_line(char row[MAX_ROW_LENGTH], FILE* data){
    char character = fgetc(data);
    int row_size = 0;

    if(character == EOF)
        return false;   //return false when we read all the file

    while(character != '\r' && character != '\n' && row_size < MAX_ROW_LENGTH - 1){
        row[row_size] = character;
        row_size++;
        character = fgetc(data);
    }
    row[row_size] = '\0';

    return true; //return true otherwise
}

void normalize_user(USER* user, int n_rows, USER* max, USER* min){
    for(int i = 0; i < n_rows; i++){
        user[i].int_rate = (user[i].int_rate - min->int_rate) / (max->int_rate - min->int_rate);
        user[i].installment = (user[i].installment - min->installment) / (max->installment - min->installment);
        user[i].log_annual_inc = (user[i].log_annual_inc - min->log_annual_inc) / (max->log_annual_inc - min->log_annual_inc);
        user[i].dti = (user[i].dti - min->dti) / (max->dti - min->dti);
        user[i].fico = (user[i].fico - min->fico) / (max->fico - min->fico);
        user[i].days_with_cr_line = (user[i].days_with_cr_line - min->days_with_cr_line) / (max->days_with_cr_line - min->days_with_cr_line);
        user[i].revol_bal = (user[i].revol_bal - min->revol_bal) / (max->revol_bal - min->revol_bal);
        user[i].revol_util = (user[i].revol_util - min->revol_util) / (max->revol_util - min->revol_util);
        user[i].inq_last_6mths = (user[i].inq_last_6mths - min->inq_last_6mths) / (max->inq_last_6mths - min->inq_last_6mths);
        user[i].delinq_2yrs = (user[i].delinq_2yrs - min->delinq_2yrs) / (max->delinq_2yrs - min->delinq_2yrs);
        user[i].credit_policy = (user[i].credit_policy - min->credit_policy) / (max->credit_policy - min->credit_policy);
        user[i].pub_rec = (user[i].pub_rec - min->pub_rec) / (max->pub_rec - min->pub_rec);
    }
}

int* KNN_algorithm(USER user[], int n_rows, int const K){
    int* results = (int*) malloc(sizeof(int)*n_rows);

    //creation of two separate array
    int n_test = n_rows * PERCENT;
    int n_train = n_rows-n_test;
    USER test[n_test], train[n_train];

    for(int i = 0, i_train = 0; i < n_rows; i++){
        if(i < n_test){
            test[i] = user[i];
        }
        else{
            train[i_train] = user[i];
            i_train++;
        }
    }

    //alg
    for(int i_train = 0; i_train < n_train; i_train++){
        for(int i_test = 0; i_test < n_rows; i_test++){
            //
        }
        //
    }

    return results;
}

double euclidean_distance(USER test, USER train){
    return (pow(test.int_rate + train.int_rate, 2) + pow(test.dti + train.dti, 2) + pow(test.fico + train.fico, 2));
}

