#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_d 100
#define MAX_N 100000
#define learning_rate 0.0001
#define MAX_ITERATION 100000
#define EPS 1e-6

//Khoi tao mang chua du lieu: X chua toan bo, X1 chua cac diem co nhan la 1, X0 chua cac diem co nhan la 
double X0[MAX_N][MAX_d], X1[MAX_N][MAX_d]; 
double X[MAX_d + 1][MAX_N]; //X co hang la so chieu, diem la so cot. NOi chung la bi nguoc
double label[MAX_N]; // Nhan
int X0_size, X1_size, d, N;
double W[MAX_d + 1];
double lam = 1.0;    

void welcome_message() {
    printf("========================================================================================\n");
    printf("||                                  DO AN TINH TOAN 1                                 ||\n");
    printf("||                               SUPPORT VECTOR MACHINE                               ||\n");
    printf("========================================================================================\n\n");
}
void program_info(){
    printf("Thong tin ve chuong trinh: \n");
    printf("-   Giang vien huong dan: PGS.TS Nguyen Tan Khoi\n");
    printf("-   Ten chuong trinh: Support Vector Machine\n");
    printf("-   Sinh vien thuc hien: Duong Phuoc Thanh      MSSV: 102230373\n");
    printf("                         Le Minh Sang           MSSV: 102230369\n");
    printf("-   Lop sinh hoat: 23T-DT4\n\n");
}

void input() {
    printf("========================================================================================\n");
    printf("||                               CHON DU LIEU TUY CHINH                               ||\n");
    printf("========================================================================================\n\n");

    printf("----------------------------------------------------------------------------------------\n");
    printf("|                              QUY DINH CAC NHAP DU LIEU                               |\n");     
    printf("| - Dong dau tien: 2 so nguyen d va N voi d la so chieu va N la so diem                |\n");
    printf("| - N dong tiep theo: Gom d + 1 so: d so dau tien la toa do                            |\n");
    printf("|   cua diem du lieu, so cuoi cung la nhan cua diem du lieu.                           |\n");
    printf("----------------------------------------------------------------------------------------\n\n");

    printf("- Nhan 1: Nhap du lieu tu file\n");
    printf("- Nhan 2: Nhap du lieu tu ban phim\n");

    int choose;
    char filename[1000];
    FILE    *input;
    do {
        printf("Chon cach nhap du lieu: ");
        scanf("%d", &choose);
        if (choose != 1 && choose != 2) {
            printf("Vui long nhap lai! \n");
        }
    }
    while (choose != 1 && choose != 2);

    switch (choose)
    {
        case 1:
            printf("Ban da chon cach nhap du lieu tu file\n");
            do {
                printf("Vui long nhap ten file: ");
                scanf("%s", filename);
                input = fopen(filename, "r");
                if (input == NULL) {
                    printf("Ten file khong hop le! Vui long nhap lai\n");
                }
            }
            while (input == NULL);
            break;
        case 2:
            printf("Ban da chon cach nhap du lieu tu ban phim\n");
            break;
    }

    //Doc du lieu
    if (choose == 1) {
        fscanf(input, "%d", &d);
        fscanf(input, "%d", &N);
        for (int i = 0; i < N; i++){
            double tmp[d + 1];
            for (int j = 0; j < d + 1; j++)
                fscanf(input, "%lf", &tmp[j]);
            if (tmp[d] == 1) {
                for (int j = 0; j < d; j++)
                    X1[X1_size][j] = tmp[j];
                X1_size++;
            }
            else {
                for (int j = 0; j < d; j++)
                    X0[X0_size][j] = tmp[j];
                X0_size++;
            }
        }
        //Dong file
        fclose(input);
    }
    else{
        scanf("%d", &d);
        scanf("%d", &N);
        for (int i = 0; i < N; i++){
            double tmp[d + 1];
            for (int j = 0; j < d + 1; j++)
                scanf("%lf  ", &tmp[j]);
            if (tmp[d] == 1) {
                for (int j = 0; j < d; j++)
                    X1[X1_size][j] = tmp[j];
                X1_size++;
            }
            else{
                for (int j = 0; j < d; j++)
                    X0[X0_size][j] = tmp[j];
                X0_size++;
            }
        }
    }
    //Them du lieu vao X va label
    for (int i = 0; i < X0_size; i++){
        label[i] = -1;
        for (int j = 0; j < d; j++){
            X[j][i] = X0[i][j];
        }
        X[d][i] = 1;
    }
    for (int i = 0; i < X1_size; i++){
        label[i + X0_size] = 1;
        for (int j = 0; j < d; j++){
            X[j][i + X0_size] = X1[i][j];
        }
        X[d][i + X0_size] = 1;
    }
}

void print_hyperplane(double w, int i) {
    if (i == 0){
        printf("W = %lf x%d ", w, i);
    }
    else if (i == d){
        printf(" %lf ", w);
    }
    else{
        if (w > 0) {
            printf(" + %lf x%d", w, i);
        }
        else {
            printf(" - %lf x%d", -w, i);
        }
    }
}

void output() {
    printf("========================================================================================\n");
    printf("||                                    XUAT DU LIEU                                    ||\n");
    printf("========================================================================================\n\n");

    printf("Sieu mat phang vua tim duoc la: \n");
    for (int i = 0; i < d + 1; i++)
        print_hyperplane(W[i], i);
    printf(" = 0\n");

    FILE *output;
    output = fopen("data.out", "w");
    fprintf(output, "%d %d\n", d, N);
    for (int i = 0; i < X0_size; i++) {
        for (int j = 0; j < d; j++)
            fprintf(output, "%lf ", X0[i][j]);
        fprintf(output, "-1\n");
    }
    for (int i = 0; i < X1_size; i++) {
        for (int j = 0; j < d; j++)
            fprintf(output, "%lf ", X1[i][j]);
        fprintf(output, "1\n");
    }
    for (int i = 0; i < d + 1; i++)
        fprintf(output, "%lf ", W[i]);
    fclose(output);

    printf("Ban co muon xem hinh anh duoc tao tu du lieu khong? Nhan 1 de xem, Nhan 0 de thoat\n");

    int choose;
    do {
        scanf("%d", &choose);
        if (choose != 1 && choose != 0) {
            printf("Vui long nhap lai! \n");
        }
    }
    while (choose != 1 && choose != 0);

    if (choose == 1) {  
        if (d == 2 || d == 3) {
            system("python generate_img.py");
        }
    }
}

void print() {
    welcome_message();
    program_info();
    input();
}

void grad(double g[]) {
    for (int i = 0; i < d + 1; ++i) {
        g[i] = 0.0;
    }
    for (int i = 0; i < N; ++i) {
        double u = 0.0;
        for (int j = 0; j < d + 1; ++j) {
            u += W[j] * X[j][i];
        }
        if (label[i] * u < 1.0) {
            for (int j = 0; j < d + 1; ++j) {
                g[j] -= label[i] * X[j][i];
            }
        }
    }
    for (int j = 0; j < d; ++j) {
        g[j] += lam * W[j]; 
    }
}

void gradient_descent() {
    double g[d + 1];
    int i = 0;
    while (i < MAX_ITERATION) {
        ++i;
        grad(g);
        for (int j = 0; j < d + 1; ++j) {
            W[j] -= learning_rate * g[j];
        }
        double norm_g = 0.0;
        for (int j = 0; j < d + 1; ++j) {
            norm_g += g[j] * g[j];
        }
        if (sqrt(norm_g) < 1e-5) {
            break;
        }
    }
}

int main() {

    print();

    gradient_descent();

    output();
    return 0;

}