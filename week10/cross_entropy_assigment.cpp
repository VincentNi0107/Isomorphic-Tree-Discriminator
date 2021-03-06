/*********************************************************************************/
/* Assignment for oneAPI-based Heterogeneous Computing and Problem Solving       */
/* for JiaoTong University, Nov. 2021                                            */
/* Patric Zhao, patric.zhao@intel.com                                            */
/*********************************************************************************/

#include<iostream>
#include<chrono>
#include<cmath>
#include<CL/sycl.hpp>

#define random_float()  (rand() / double(RAND_MAX));

using namespace std;
using namespace sycl;


// Input size
constexpr int K = 128;
constexpr int M = 32;
constexpr int N = 8192;

constexpr int iterations = 10;

// basic gpu speed
float gpu_kernel(float* X, int* mask, float* weight, float* loss, queue& q) {

    float duration = 0.0;
    auto e = q.submit([&](handler& h) {

        // (TODO) File range of computation 
        h.parallel_for( ???? , [=](auto& idx) {

            // （TODO）: calculate index
            int row = ????? ;
            int col = ????? ;

            float exp_sum = 0.0;
            for (int i = 0; i < M; ++i) {
                exp_sum += exp(X[row * M * N + i * N + col]);
            }

            int mask_id = mask[row * N + col];
            loss[row * N + col] = weight[row * N + col] * log(exp(X[row * M * N + mask_id * N + col]) / exp_sum);

            });
        });

    e.wait();

    // (TODO) calculate computation time 
    duration = ?????? / 1000.0f / 1000.0f;

    return duration;
}


float cpu_kernel(float* X, int* mask, float* weight, float* loss) {
    double duration = 0.0;
    chrono::high_resolution_clock::time_point s, e;

    s = chrono::high_resolution_clock::now();
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < N; ++j) {
            float exp_sum = 0.0;

            for (int k = 0; k < M; ++k) {
                // （TODO）: calculate sum of exp
                exp_sum += ????;
            }

            int mask_id = mask[i * N + j];

            loss[i * N + j] = weight[i * N + j] * (log(exp(X[i * M * N + mask_id * N + j]) / exp_sum));
        }
    }
    e = chrono::high_resolution_clock::now();
    duration = chrono::duration<float, milli>(e - s).count();

    return duration;
}

int verify(float* data_host, float* data_device) {
    int errCount = 0;
    for (int i = 0; i < K * N; ++i) {
        if (fabs(data_host[i] - data_device[i]) > 0.001) ++errCount;
    }
    return errCount;
}

void run(queue& q) {

    // （TODO）: Allocate host memory for input
    float* X_cpu = ???;
    int*   mask_cpu = ???;
    float* weight_cpu = ???;

    // （TODO）: Allocate device memory for input
    float* X_gpu = ???;
    int*   mask_gpu = ???;
    float* weight_gpu = ???;

    // （TOOD）: Allocate shared memory for results
    float* loss_gpu = malloc_ ????  <float>(K * N, q);

    // CPU results for reference
    float* loss_cpu = malloc_host<float>(K * N, q);

    // Init random result for input
    for (int i = 0; i < K * M * N; ++i) {
        X_cpu[i] = random_float();
    }

    for (int i = 0; i < K * N; ++i) {
        loss_gpu[i] = 0.0;
        loss_cpu[i] = 0.0;
        mask_cpu[i] = i % M;
        weight_cpu[i] = random_float();
    }


    // （TODO）: explicit memory copy from CPU to GPU for inputs
    q.memcpy(??? , ???,   sizeof(float) *K * M * N).wait();
    q.memcpy(mask_gpu,   mask_cpu,   ???).wait();
    q.memcpy(  ?????     ).wait();
    

    float duration_cpu = 0.0;
    float duration_gpu = 0.0;

    int warmup = 10;
    for (int i = 0; i < iterations / 2 + warmup / 2; ++i) {
        float duration = cpu_kernel(X_cpu, mask_cpu, weight_cpu, loss_cpu);
        if (i >= warmup / 2) duration_cpu += duration;
    }
    duration_cpu /= iterations / 2;

    for (int i = 0; i < iterations + warmup; ++i) {
        // （TODO）: pass params to function  
        float duration = gpu_kernel(??? ..... ,   q);
        if (i >= warmup) duration_gpu += duration;
    }
    duration_gpu /= iterations;

    printf("Cross Entropy Input Size: K: %d, M: %d, N: %d, Total : %d\n"
        "GPU time: %lf (ms)\n"
        "CPU time: %lf (ms)\n",
        K, M, N, K * M * N, duration_gpu, duration_cpu);

    int errCount = 0;
    errCount = verify(loss_cpu, loss_gpu);
    printf("%d errors in loss_gpu\n", errCount);


    // free all memory in host 
    free(loss_cpu, q);
    free(X_cpu, q);
    free(mask_cpu, q);
    free(weight_cpu, q);

    // （TODO） : free all memory in device 
    free(????);
    free(????);
    free(????);
    free(????);
}

int main() {
    
    auto propList = property_list{ property::queue::enable_profiling() };

    // （TODO） : Select your device, GPU
    queue my_gpu_queue(???, propList);

    run(my_gpu_queue);

    return 0;
}

