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

int load_dataset(char file_path[], USER users[]);
USER row_to_user(char row[]);
bool read_line(char row[MAX_ROW_LENGTH], FILE* data);
int* KNN_algorithm(USER test[], USER train[], int n_rows, int const K); //return a pointer to an array of 1 or 0

int main(){
    USER users[MAX_ROWS];

    char file_path[] = {"Week_7/loan_data.csv"}; //

    int n_rows = load_dataset(file_path, users);

    int separator = n_rows * PERCENT;
    printf("%d, %d", n_rows, separator);

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



}

int load_dataset(char file_path[], USER users[]){
    FILE* data = fopen(file_path, "r");
    int n_rows = 0;

    if(data == NULL){
        perror("Error opening file");
        exit(1);
    }

    char row[MAX_ROW_LENGTH];

    read_line(row, data);

    while(read_line(row, data) && n_rows < MAX_ROWS){
        users[n_rows] = row_to_user(row);
        n_rows++;
    }

    fclose(data);

    return n_rows;
}

USER row_to_user(char row[]){
    USER user;
    char* purpose = (char*) malloc(PURPOSE_MAX);

    user.credit_policy = atoi(strtok(row, DEVIDER));
    user.purpose = strcpy(purpose, strtok(NULL, DEVIDER));
    user.int_rate = strtod(strtok(NULL, DEVIDER), NULL);
    user.installment = strtod(strtok(NULL, DEVIDER), NULL);
    user.log_annual_inc = strtod(strtok(NULL, DEVIDER), NULL);
    user.dti = strtod(strtok(NULL, DEVIDER), NULL);
    user.fico = atoi(strtok(NULL, DEVIDER));
    user.days_with_cr_line = strtod(strtok(NULL, DEVIDER), NULL);
    user.revol_bal = strtod(strtok(NULL, DEVIDER), NULL);
    user.revol_util = strtod(strtok(NULL, DEVIDER), NULL);
    user.inq_last_6mths = atoi(strtok(NULL, DEVIDER));
    user.delinq_2yrs = atoi(strtok(NULL, DEVIDER));
    user.pub_rec = atoi(strtok(NULL, DEVIDER));
    user.not_fully_paid = atoi(strtok(NULL, DEVIDER));

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

int* KNN_algorithm(USER test[], USER train[], int n_rows, int const K){
    int* results = (int*) malloc(sizeof(int)*n_rows);

    int i_train = n_rows - (n_rows*PERCENT);

    for(int i = 0; i < i_train; i++){

    }
}

double euclidean_distance(USER test, USER train){
    sqrt(pow(test. , 2));
}

/**
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
*/