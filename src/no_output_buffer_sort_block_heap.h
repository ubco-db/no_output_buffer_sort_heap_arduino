#if !defined(NO_OUTPUT_BUFFER_SORT_BLOCK_HEAP_H)
#define NO_OUTPUT_BUFFER_BLOCK_HEAP_H

#if defined(ARDUINO)
#include "serial_c_iface.h"
#endif

#include <stdint.h>

#include "external_sort.h"
#include "file/ion_file.h"

//block to use as output block. Breaks reading in new block code if changed.
#define OUTPUT_BLOCK_ID 							0

// #define BUFFER_OUTPUT_BLOCK_START_OFFSET  		OUTPUT_BLOCK_ID * es->page_size
// #define BUFFER_OUTPUT_BLOCK_START_RECORD_OFFSET  OUTPUT_BLOCK_ID * es->page_size + BLOCK_HEADER_SIZE
// Simplification if OUTPUT_BLOCK_ID is 0
#define BUFFER_OUTPUT_BLOCK_START_OFFSET  			0
#define BUFFER_OUTPUT_BLOCK_START_RECORD_OFFSET 	BLOCK_HEADER_SIZE

#if defined(__cplusplus)
extern "C" {
#endif

/**
@brief      No output sort with input iterator and supporting variable number of records per block.
@param      iterator
                Row iterator for reading input rows
@param      iteratorState
                Structure stores state of iterator (file info etc.)
@param      tupleBuffer
                Pre-allocated space to store one tuple (row) of input being sorted
@param      outputFile
                Already opened file to store sorting output (and in-progress temporary results)
@param      buffer
                Pre-allocated space used by algorithm during sorting
@param      bufferSizeInBlocks
                Size of buffer in blocks
@param      es
                Sorting state info (block size, record size, etc.)
@param      resultFilePtr
                Offset within output file of first output record
@param      metric
                Tracks algorithm metrics (I/Os, comparisons, memory swaps)
@param      compareFn
                Record comparison function for record ordering
*/
int no_output_buffer_sort_block_heap(
        int     (*iterator)(void *state, void* buffer),
        void    *iteratorState,
		void    *tupleBuffer,
        ION_FILE *outputFile,		
		char    *buffer,        
		int     bufferSizeInBlocks,
		external_sort_t *es,
		long    *resultFilePtr,
		metrics_t *metric,
        int8_t  (*compareFn)(void *a, void *b)
);

#if defined(__cplusplus)
}
#endif

#endif
