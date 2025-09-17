//22412051 _ 이승은
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <ctime>
using namespace std;

void swap(char* a, char* b);
void permute(string& s, int start, unordered_set<long long>& primes);
int is_prime(long long n);
void sort(vector<int>& num);

int main() {
    clock_t start, finish;
    double duration;
    string numbers;
    cout << "입력 문자열? ";
    cin >> numbers;
    
    // 문자열 길이 10으로 제한
    if (numbers.length() > 10) {
        cout << "10개 이하의 문자열을 입력해주세요." << endl;
        return 1;
    }

    for (int k = 4; k < 11; k++)
    {
        string S = numbers.substr(0, k);
        unordered_set<long long> prime_num;

        start = clock();
        permute(S, 0, prime_num);
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;

        // k == 4일때만 소수 집합 출력
        if (k == 4) {
            vector<int> sort_prime(prime_num.begin(), prime_num.end());
            sort(sort_prime.begin(), sort_prime.end());

            cout << "소수의 집합 = { ";
            for (long long p : sort_prime)
                cout << p << " ";
            cout << "}" << endl;
        }
        cout << "문자열 = " << S << ", "; 
        cout << "소수의 수 = " << prime_num.size() << ", ";
        cout << "실행 시간 = " << duration << endl;
    }
    return 0;
}

//swap 함수
void swap(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

// permutation 사용 / long long으로 오버플로우 막기
// 소수 판별까지 하기
void permute(string& s, int start, unordered_set<long long>& primes) {
    int count = 0;
    if (start == s.length()) {
        for (int i = 1; i <= s.length(); ++i) {
            long long num = stoll(s.substr(0, i));
            if (is_prime(num)) {
                primes.insert(num);
            }
        }
        return;
    }

    for (int i = start; i < s.length(); ++i) {
        swap(&s[start], &s[i]);
        permute(s, start + 1, primes);
        swap(&s[start], &s[i]);
    }
}

// 소수 판별
int is_prime(long long n) {
    if (n < 2)
        return 0;
    for (long long i = 2; i * i <= n; ++i) 
        if (n % i == 0) return 0;
    return 1;
}

// 판별한 소수 집합 sorting 함수
void sort(vector<int>& num) {
    int s = num.size();
    for (int i = 0; i < s - 1; i++) {
        int min = i;
        for (int j = i + 1; j < s; j++) {
            if (num[j] < num[min]) {
                min = j;
            }
        }
        swap(num[i], num[min]);
    }
}