#include <iostream>
#include <thread>

using namespace std;

#define MAX 10
#define MAX_THREAD 10

int mtx_1[MAX][MAX];
int mtx_2[MAX][MAX];
int mtx_3[MAX][MAX];
int step_i = 0;

void* multi(void* arg){
    int core = step_i++;

    for (int i = core * MAX / 10; i < (core + 1) * MAX / 10; i++) {
        for (int j = 0; j < MAX; j++) {
            for (int k = 0; k < MAX; k++) {
                mtx_3[i][j] += mtx_1[i][k] * mtx_2[k][j];
            }
        }
    }
    return nullptr;
}



int main()
{

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            mtx_1[i][j] = rand() % 10;
            mtx_2[i][j] = rand() % 10;
        }
    }

    cout << endl
         << "Matrix A" << endl;
    for (auto &i : mtx_1) {
        for (int j : i)
            cout << j << " ";
        cout << endl;
    }

    cout << endl
         << "Matrix B" << endl;
    for (auto &i : mtx_2) {
        for (int j : i)
            cout << j << " ";
        cout << endl;
    }

    thread threads[MAX_THREAD];

////                create(&threads[i], NULL, multi, (void*)(p));

    for (int i = 0; i < MAX_THREAD; i++) {
        int* p= nullptr;
        thread(&threads[i], NULL, multi, (void*)(p));
    }

    for (auto &thread : threads)
        thread.join();

    cout << endl
         << "Multiplication of A and B" << endl;
    for (auto &i : mtx_3) {
        for (int j : i)
            cout << j << " ";
        cout << endl;
    }
    return 0;
}