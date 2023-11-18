#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define PURPOSE_MAX 20 //max string length of purpose field
#define MAX_ROWS 10000 //number of row in the data file
#define DEVIDER ","
#define MAX_ROW_LENGTH 1000
#define PERCENT (75/100)

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
USER row_to_user(char row[], USER* max, USER* min);
bool read_line(char row[MAX_ROW_LENGTH], FILE* data);
int* KNN_algorithm(USER test[], USER train[], int n_rows, int const K); //return a pointer to an array of 1 or 0
void normalize_user(USER* user,int n_rows, USER* max, USER* min);

int main(){
    USER users[MAX_ROWS];
    USER max, min;

    char file_path[] = {"Week_7/loan_data.csv"}; //

    int n_rows = load_dataset(file_path, users, &max, &min);


    int separator = n_rows * PERCENT;
    printf("%d, %d", n_rows, separator);

    normalize_user(users, n_rows, &max, &min);

    //creation of two arrays, one used as test and the second as train
    USER test[separator], train[n_rows-separator];

    for(int i = 0, i_train = 0; i < n_rows; i++){
        if(i < separator){
            test[i] = users[i];

        }
        else{
            train[i_train] = users[i];
            i_train++;
        }
    }

    printf(" %f", users[1].installment);

}

int load_dataset(char file_path[], USER users[], USER* max, USER* min){
    FILE* data = fopen(file_path, "r");
    int n_rows = 0;

    if(data == NULL){
        perror("Error opening file");
        exit(1);
    }

    char row[MAX_ROW_LENGTH];

    read_line(row, data);

    while(read_line(row, data) && n_rows < MAX_ROWS){
        users[n_rows] = row_to_user(row, max, min);
        n_rows++;
    }

    fclose(data);

    return n_rows;
}

USER row_to_user(char row[], USER* max, USER* min){
    USER user;
    char* purpose = (char*) malloc(PURPOSE_MAX);

    user.credit_policy = atoi(strtok(row, DEVIDER));
    if(user.credit_policy > max->credit_policy)
        max->credit_policy = user.credit_policy;
    if(user.credit_policy < min->credit_policy)
        min->credit_policy = user.credit_policy;

    user.purpose = strcpy(purpose, strtok(NULL, DEVIDER));
    if(user.purpose > max->purpose)
        max->purpose = user.purpose;
    if(user.purpose < min->purpose)
        min->purpose = user.purpose;

    user.int_rate = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.int_rate > max->int_rate)
        max->int_rate = user.int_rate;
    if(user.int_rate < min->int_rate)
        min->int_rate = user.int_rate;

    user.installment = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.installment > max->installment)
        max->installment = user.installment;
    if(user.installment < min->installment)
        min->installment = user.installment;

    user.log_annual_inc = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.log_annual_inc > max->log_annual_inc)
        max->log_annual_inc = user.log_annual_inc;
    if(user.log_annual_inc < min->log_annual_inc)
        min->log_annual_inc = user.log_annual_inc;

    user.dti = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.dti > max->dti)
        max->dti = user.dti;
    if(user.dti < min->dti)
        min->dti = user.dti;

    user.fico = atoi(strtok(NULL, DEVIDER));
    if(user.fico > max->fico)
        max->fico = user.fico;
    if(user.fico < min->fico)
        min->fico = user.fico;

    user.days_with_cr_line = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.days_with_cr_line > max->days_with_cr_line)
        max->days_with_cr_line = user.days_with_cr_line;
    if(user.days_with_cr_line < min->days_with_cr_line)
        min->days_with_cr_line = user.days_with_cr_line;

    user.revol_bal = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.revol_bal > max->revol_bal)
        max->revol_bal = user.revol_bal;
    if(user.revol_bal < min->revol_bal)
        min->revol_bal = user.revol_bal;

    user.revol_util = strtod(strtok(NULL, DEVIDER), NULL);
    if(user.revol_util > max->revol_util)
        max->revol_util = user.revol_util;
    if(user.revol_util < min->revol_util)
        min->revol_util = user.revol_util;

    user.inq_last_6mths = atoi(strtok(NULL, DEVIDER));
    if(user.inq_last_6mths > max->inq_last_6mths)
        max->inq_last_6mths = user.inq_last_6mths;
    if(user.inq_last_6mths < min->inq_last_6mths)
        min->inq_last_6mths = user.inq_last_6mths;

    user.delinq_2yrs = atoi(strtok(NULL, DEVIDER));
    if(user.delinq_2yrs > max->delinq_2yrs)
        max->delinq_2yrs = user.delinq_2yrs;
    if(user.delinq_2yrs < min->delinq_2yrs)
        min->delinq_2yrs = user.delinq_2yrs;

    user.pub_rec = atoi(strtok(NULL, DEVIDER));
    if(user.pub_rec > max->pub_rec)
        max->pub_rec = user.pub_rec;
    if(user.pub_rec < min->pub_rec)
        min->pub_rec = user.pub_rec;

    user.not_fully_paid = atoi(strtok(NULL, DEVIDER));
    if(user.not_fully_paid > max->not_fully_paid)
        max->not_fully_paid = user.not_fully_paid;
    if(user.not_fully_paid < min->not_fully_paid)
        min->not_fully_paid = user.not_fully_paid;

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
/*
int* KNN_algorithm(USER test[], USER train[], int n_rows, int const K){
    int* results = (int*) malloc(sizeof(int)*n_rows);

    int i_train = n_rows - (n_rows*PERCENT);

    for(int i = 0; i < i_train; i++){

    }
}

double euclidean_distance(USER test, USER train) {
    sqrt(pow(test., 2));
}
*/
