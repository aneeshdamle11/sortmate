#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H (1)

#define CHUNK_SIZE (100)    /* partition size */

/*! \brief Sorts the data in chunks of memory
 * \param[in] filename, size of chunk, option flag
 * \retval number of temporary files created
 * \Note: Data from infile is separated out in files of small sizes.
 * Then each small file is sorted individually, and written in temporary files.
 */
int sort_in_chunks(char *input, int chunk_size, char option);


/*! \brief Merge all sorted temporary files
 * \param[in]: filename, size of chunk, count of temporary files, option flag
 * \retval: void
 * Each sorted temporary file is merged and written to outfile.
 */
void merge_sorted_chunks(char *output, int chunk_size, int number_of_tmp_files, char option);


#endif /* EXTERNAL_SORT_H */
