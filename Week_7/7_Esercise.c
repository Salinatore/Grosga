/**
 * @file 7_Exercise.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1
 * @date 15/11/23
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#define PURPOSE_MAX 20 //max string length of purpose field
#define MAX_ROWS 10000 //number of row in the data file
#define DEVIDER ","
#define MAX_ROW_LENGTH 1000
#define PERCENT 0.25
#define POSSIBLE_CASES 2 //credit_policy is 1 or 0

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

typedef struct user_distance{
    USER user;
    double distance;
} USER_DISTANCE;

int load_dataset(char file_path[], USER users[], USER* max, USER* min);
USER row_to_user(char row[], USER* max, USER* min, bool* is_first_time);
bool read_line(char row[MAX_ROW_LENGTH], FILE* data);
void normalize_user(USER* user,int n_rows, USER* max, USER* min);
void divide_users(USER users[], int n_rows, USER train[], USER test[]);
void random_divide_user(USER users[], int n_rows, USER train[], USER test[]);
void radomize_users(USER users[], int n_rows);

bool* KNN_algorithm(USER train[], int n_train, USER test[], int n_test, int const K);
double euclidean_distance(USER train, USER test);
double biggest_distance(USER_DISTANCE distances[], int const K);
void add_distance(USER_DISTANCE* distances, USER user, double distance, int const K);
void initialize_distances(USER_DISTANCE* nearest_test, int const K);
void initialize_case_counter(double case_counter[]);

double accuracy(bool* results, USER* test, int n_test);

int main(){
    srand(5);

    USER users[MAX_ROWS];
    USER max, min;
    int K = 3;

    char file_path[] = {"Week_7/loan_data.csv"};

    int n_rows = load_dataset(file_path, users, &max, &min);

    //the normalization would make all the fields equally important
    //normalize_user(users, n_rows, &max, &min); //normalization makes the KNN alg less accurate

    int n_train = n_rows - (n_rows*PERCENT);
    int n_test = n_rows * PERCENT;
    USER train[n_train+1], test[n_test+1]; //the +1 is for the loss in the calc of n_train and n_test width

    //the randomness ensure that the test array is not made only by 1 or 0
    random_divide_user(users, n_rows, train, test);

    //KNN return an array of the prediction made by the algorithm
    bool* results = KNN_algorithm(train, n_train, test, n_test, K);
    //accuracy take the array of bool and confront them to the real values of test.credit_policy
    printf("%f", accuracy(results, test, n_test));

    //just for testing TODO:REMOVE BEFORE DELIVERING
    bool* all_one = memset(malloc(sizeof(bool) * n_test), 1, n_test);
    printf("\n\n%f", accuracy(all_one, test, n_test));
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

    user.credit_policy = (bool) atoi(strtok(row, DEVIDER));
    if(user.credit_policy > max->credit_policy || *is_first_time == true)
        max->credit_policy = user.credit_policy;
    if(user.credit_policy < min->credit_policy || *is_first_time == true)
        min->credit_policy = user.credit_policy;

    user.purpose = strcpy(purpose, strtok(NULL, DEVIDER));

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

void divide_users(USER users[], int n_rows, USER train[], USER test[]){
    int n_test = n_rows * PERCENT;

    for(int i = 0, i_train = 0; i < n_rows; i++){
        if(i < n_test){
            test[i] = users[i];
        }
        else{
            train[i_train] = users[i];
            i_train++;
        }
    }
}

void random_divide_user(USER users[], int n_rows, USER train[], USER test[]){
    radomize_users(users,  n_rows);

    divide_users(users, n_rows, train, test);
}

void radomize_users(USER users[], int n_rows){
    for(int i = 0; i < n_rows*100; i++){
        int swap_from = rand() % n_rows;
        int swap_to = rand() % n_rows;

        USER current_user = users[swap_from];
        users[swap_from] = users[swap_to];
        users[swap_to] = current_user;
    }
}

bool* KNN_algorithm(USER train[], int n_train, USER test[], int n_test, int const K){
    bool* results = (bool*) malloc(sizeof(bool) * n_test);

    for(int i_test = 0; i_test < n_test; i_test++){
        double case_counter[POSSIBLE_CASES];
        initialize_case_counter(case_counter);

        USER_DISTANCE distances[K];
        initialize_distances(distances, K);

        double current_distance = DBL_MAX;

        //search of the K nearest
        for(int i_train = 0; i_train < n_train; i_train++){
            current_distance = euclidean_distance(train[i_train], test[i_test]);
            if(current_distance < biggest_distance(distances, K)){
                add_distance(distances, train[i_train], current_distance, K);
            }
        }

        for(int i = 0; i < K; i++){
            case_counter[distances[i].user.credit_policy] += 1/distances[i].distance; //meno presciso con la distanza pesata
            //case_counter[distances[i].user.credit_policy]++;
        }

        results[i_test] = case_counter[0] > case_counter[1] ? false : true;
    }

    return results;
}

void initialize_case_counter(double case_counter[]){
    for(int i = 0; i < POSSIBLE_CASES; i++){
        case_counter[i] = 0;
    }
}

double euclidean_distance(USER train, USER test){
    return sqrt(pow(test.int_rate - train.int_rate, 2) + pow(test.dti - train.dti, 2) + pow(test.fico - train.fico, 2) + pow(test.not_fully_paid - train.not_fully_paid, 2) + pow(test.inq_last_6mths - train.inq_last_6mths, 2));
}

double biggest_distance(USER_DISTANCE distances[], int const K){
    double biggest_distance = 0;

    for(int i = 0; i < K; i++) {
        biggest_distance = distances[i].distance > biggest_distance ? distances[i].distance : biggest_distance;
    }
    return biggest_distance;
}

void add_distance(USER_DISTANCE* distances, USER user, double distance, int const K){
    int biggest_distance_index = 0;

    for(int i = 0; i < K; i++) {
        biggest_distance_index = distances[i].distance > distances[biggest_distance_index].distance ? i : biggest_distance_index;
    }

    distances[biggest_distance_index].user = user;
    distances[biggest_distance_index].distance = distance;
}

void initialize_distances(USER_DISTANCE* nearest_test, int const K){
    for(int i = 0; i < K; i++){
        nearest_test[i].distance = DBL_MAX;
    }
}

double accuracy(bool* results, USER* test, int n_test){
    double true_positive = 0;

    for(int i_test = 0; i_test < n_test; i_test++){
        if(results[i_test] == test[i_test].credit_policy){
            true_positive++;
        }
    }

    return true_positive / n_test;
}
