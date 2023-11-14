#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PURPOSE_MAX 20 //max string length of purpose field
#define MAX_ROWS 10000 //number of row in the data file
#define DEVIDER "," //
#define MAX_ROW_LENGTH 1000


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

typedef USER* USER_P;

void fill_borrowers_array(USER borrowers[], FILE* input_file);
USER row_to_user(char row[]);
int load_dataset(char path[], USER users[]);
bool read_line(char row[MAX_ROW_LENGTH], FILE* data);
double standardize(double number, double max, double min);

int main(){
    //open file to read
    //char* path = "Week_7/loan_data.csv";
    USER users[MAX_ROWS];

    int n_rows = load_dataset(path, users);
}

double standardize(double number, double max, double min){
    return (number - min)/(max - min);
}

int load_dataset(char path[], USER users[]){
    FILE* data = fopen(path, "r");
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
        return false;

    while(character != '\r' && character != '\n' && row_size < MAX_ROW_LENGTH - 1){
        row[row_size] = character;
        row_size++;
        character = fgetc(data);
    }
    row[row_size] = '\0';

    return true;
}

