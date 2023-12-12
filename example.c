#include "MedianFilter.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static sMedianFilter_t medianFilter;

#define DEBUG

int main(int argc, char** argv)
{
//input
    if(argc != 2) {
        fprintf(stderr, "Need to specify window size argument\n");
        exit(EXIT_FAILURE);
    }

    uint32_t wndsz;
    if (sscanf(argv[1], "%"SCNu32, &wndsz) == -1) {
        fprintf(stderr, "Invalid integer\n");
        exit(EXIT_FAILURE);
    }

    if(wndsz % 2 == 0 || wndsz == 0) {
        fprintf(stderr, "Window must be odd and positive\n");
        exit(2);
    }
//initialization
    medianFilter.numNodes = wndsz;
    medianFilter.medianBuffer = (sMedianNode_t*) calloc(sizeof(sMedianNode_t), wndsz);

    if (!medianFilter.medianBuffer) {
        fprintf(stderr, "Memory error\n");
        exit(EXIT_FAILURE);
    }

    if (MEDIANFILTER_Init(&medianFilter) == -1) {
        fprintf(stderr, "medianFilter initialization error\n");
        exit(EXIT_FAILURE);
    }
    
//    filtering

    uint32_t slice;

    while(fread(&slice, sizeof(uint32_t), 1, stdin) > 0)
    {
        int medianValue = MEDIANFILTER_Insert(&medianFilter, slice);
        fwrite(&medianValue, sizeof(uint32_t), 1, stdout);
#ifdef DEBUG
        fprintf(stderr, "New value: %d \tMedian value: %d\r\n", slice, medianValue);
//        sleep(1);
#endif
    }

    fprintf(stderr, "\n");

//    free memory

    free(medianFilter.medianBuffer);

    return 0;
}
