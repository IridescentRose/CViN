#ifndef CVIN_TOKENIZER_H
#define CVIN_TOKENIZER_H

struct StringSlice{
    char* ptr;
    unsigned int len;
};

struct TokenArray{
    struct StringSlice* slices;
    unsigned int len;
};

struct TokenArrayIterator{
    struct TokenArray tokens;
    unsigned int pos;
};

/**
 * Gets the front of the iterator
 * @param tkArray - Iterator
 * @return - First parameter in the iterator
 */
struct StringSlice TKAI_front(struct TokenArrayIterator tkArray);

/**
 * Updates the front of the iterator
 * @param tkArray - Iterator
 */
void TKAI_next(struct TokenArrayIterator* tkArray);

/**
 * Tokenizes a given file into a Token Array
 * @param filepath - File
 * @return - Token Array to be processed
 */
struct TokenArray tokenize(const char* filepath);

#endif //CVIN_TOKENIZER_H
