#include <assert.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define CYCLIC_WORLD 1
#define OFFSET 5
#define RULE 184


int gather_states(int rank, int size, const unsigned int *state, unsigned int *full_state) {
    int N = 200 / size + 2 * OFFSET + (rank < 200 % size);
    if (rank == 0) {
        for (int i = OFFSET, j = 0; i < N - OFFSET; i++, j++)
            full_state[j] = state[i];
        for (int src = 1, offset = N - 2 * OFFSET; src < size; src++) {
            int src_N = 200 / size + 2 * OFFSET + (src < 200 % size);
            int src_count = src_N - 2 * OFFSET;
            MPI_Recv(full_state + offset, src_count, MPI_UNSIGNED, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            offset += src_count;
        }
    } else {
        int dst = 0;
        MPI_Send(state + OFFSET, N - 2 * OFFSET, MPI_UNSIGNED, dst, 0, MPI_COMM_WORLD);
    }
    return 0;
}

int step(int ghost_lo, int ghost_hi, int lo, int hi, unsigned int *state) {
    int finished = 1;
    unsigned int prev = ghost_lo;
    for (int i = lo; i < hi; i++) {
        int curr = state[i];
        int next = i + 1 < hi ? state[i + 1] : ghost_hi;
        int val = (next) ^ (curr << 1) ^ (prev << 2);
        state[i] = 0;
        for (int pos = 0; pos < 8; pos++) {
            if (RULE & (1 << pos))
                state[i] |= (val == pos);
        }
        if (curr != state[i])
            finished = 0;
        prev = curr;
    }
    return finished;
}

int cellular_automata(int rank, int size) {
    int N = 200 / size + 2 * OFFSET + (size < 200 % size);
    unsigned int *state = NULL, *full_state = NULL, *prev_full_state = NULL;
    unsigned int seed = (rank + 1) * time(NULL);
    state = (unsigned int *) malloc(N * sizeof(unsigned int));
    if (rank == 0) {
        full_state = (unsigned int *) malloc(200 * sizeof(unsigned int));
        prev_full_state = (unsigned int *) malloc(200 * sizeof(unsigned int));
    }
    for (int i = 0; i < OFFSET; i++)
        state[i] = 0;
    for (int i = OFFSET; i < N - OFFSET; i++)
        state[i] = (unsigned int) rand_r(&seed) % 2;
    for (int i = N - OFFSET; i < N; i++)
        state[i] = 0;
    gather_states(rank, size, state, prev_full_state);
    if (rank == 0) {
        for (int i = 0; i < 200; i++) {
            printf("%u", prev_full_state[i]);
        }
        printf("\n");
    }
    int iter = 0;
    int finished = 0;
    while (!finished && iter < 40) {
        if (CYCLIC_WORLD) {
            for (int i = 0; i < OFFSET; i++)
                state[i] = state[N - 2 * OFFSET + i];
            for (int i = N - OFFSET; i < N; i++)
                state[i] = state[i - N];
        }
        int ghost_lo = state[OFFSET];
        int ghost_hi = state[N - OFFSET];
        finished = step(ghost_lo, ghost_hi, OFFSET, N - OFFSET, state);
        MPI_Allreduce(&finished, &finished, 1, MPI_INT, MPI_LAND, MPI_COMM_WORLD);
        iter++;
        gather_states(rank, size, state, full_state);
        if (rank == 0) {
            for (int i = 0; i < 200; i++) {
                printf("%u", full_state[i]);
            }
            printf("\n");
            ghost_lo = CYCLIC_WORLD ? prev_full_state[200 - 1] : 0;
            ghost_hi = CYCLIC_WORLD ? prev_full_state[0] : 0;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    int rank, size;
    double time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Wtime();
    cellular_automata(rank, size);
    MPI_Finalize();
    return 0;
}