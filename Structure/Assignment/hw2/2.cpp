//22412051_이승은
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

struct polynomical{
    float coef;
    int expon;
};

int simplify(polynomical* terms, int m, polynomical* result);
int multiplyPoly(polynomical* p1, int n1, polynomical* p2, int n2, polynomical** res);
int readPoly(FILE* fp, polynomical** poly);
void printPoly(polynomical* poly, int n);

int main() {
    char filename[50];
    cout << "입력 파일 이름? ";
    cin >> filename;

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        cout << "파일을 열 수 없습니다." << endl;
        return 1;
    }
    polynomical *poly1, *poly2;
    int n1 = readPoly(fp, &poly1);
    int n2 = readPoly(fp, &poly2);
    fclose(fp);

    cout << "첫 번째 다항식 : ";
    printPoly(poly1, n1);

    cout << "두 번째 다항식 : ";
    printPoly(poly2, n2);

    polynomical* result;
    int res_cnt = multiplyPoly(poly1, n1, poly2, n2, &result);

    cout << "다항식의 곱 : ";
    printPoly(result, res_cnt);

    free(poly1);
    free(poly2);
    free(result);

    return 0;
}

int readPoly(FILE* fp, polynomical** poly) {
    int input_data;
    fscanf(fp, "%d", &input_data);
    *poly = (polynomical*)malloc(input_data * sizeof(polynomical));
    if (*poly == NULL) return 0;
    for (int i = 0; i < input_data; i++) {
        if (fscanf(fp, "%f %d", &(*poly)[i].coef, &(*poly)[i].expon) != 2) return 0;
    }
    return input_data;
}

int multiplyPoly(polynomical* p1, int n1, polynomical* p2, int n2, polynomical** result) {
    polynomical* temp = (polynomical*)malloc(n1 * n2 * sizeof(polynomical));
    if (temp == NULL) {
        *result = NULL;
        return 0;
    }
    int k = 0;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++){
            temp[k].coef = p1[i].coef * p2[j].coef;
            temp[k].expon = p1[i].expon + p2[j].expon;
            k++;
        }
    }
    *result = (polynomical*)malloc(k * sizeof(polynomical));
    if (*result == NULL) {
        free(temp);
        return 0;
    }
    int m = simplify(temp, k, *result);
    free(temp);
    return m;
}

void printPoly(polynomical* poly, int n) {
    bool first = true;
    for (int i = 0; i < n; i++) {
        float co = poly[i].coef;
        int ex = poly[i].expon;
        if (fabs(co) < 1e-6) continue;
        
        if(!first) {
            if (co > 0) {
                cout << "+";
            }else {
                cout << "-";
            }
        }
        first = false;

        float abs_co;
        if (co > 0) {
            abs_co = co;
        } else {
            abs_co = -co;
        }
        if (fabs(abs_co - 1.0) > 0 || ex == 0) cout << abs_co;
        if (ex > 0) {
            cout << "X";
            if (ex > 1) cout << "^" << ex;
        }
    }
    if (first) cout << "0";
    cout << endl;
}

int simplify(polynomical* terms, int m, polynomical* result) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (terms[j].expon < terms[j + 1].expon) {
                polynomical temp = terms[j];
                terms[j] = terms[j + 1];
                terms[j + 1] = temp;
            }
        }
    }

    if (m == 0) return 0;

    int result_count = 0;
    result[result_count] = terms[0];

    for (int i = 1; i < m; i++) {
        if (terms[i].expon == result[result_count].expon) {
            result[result_count].coef += terms[i].coef;
        } else {
            result_count++;
            result[result_count] = terms[i];
        }
    }
    result_count++;

    int final_count = 0;
    for (int i = 0; i < result_count; i++) {
        if (fabs(result[i].coef) > 0) {
            if (final_count != i) {
                result[final_count] = result[i];
            }
            final_count++;
        }
    }
    return final_count;
}