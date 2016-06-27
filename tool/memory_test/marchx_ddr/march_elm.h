
//write data into memory from start_addr to (stop_addr - 4)
void march_write_word_up(unsigned int, unsigned int, unsigned int);

//write data into memory from (stop_addr - 4) to start_addr
void march_write_word_down(unsigned int, unsigned int, unsigned int);

void march_row_write_word_up(unsigned int, unsigned int, unsigned int);

//read data from memory from start_addr to (stop_addr - 4)
int march_read_word_up(unsigned int, unsigned int, unsigned int, unsigned int);

//read data from memory from (stop_addr - 4) to start_addr
int march_read_word_down(unsigned int, unsigned int, unsigned int, unsigned int);

//write data into memory from start_addr to stop_addr
void march_write_byte_up(unsigned int, unsigned int, unsigned int);
