/******************************************************************************
 * maxNodeHeap.h
 * *
 * Source of KaHIP -- Karlsruhe High Quality Partitioning.
 * Christian Schulz <christian.schulz.phone@gmail.com>
 *****************************************************************************/

#ifndef __ELEMENT_H__ 
#define __ELEMENT_H__ 


#include <vector>


template <typename Key>

class Element {
        public:
                Element( Key k, int i ) : key(k), heap_index(i) {};
                virtual ~Element() {};

                Key get_key() {
                        return key;
                }

                void set_key(Key newKey) {
                        key = newKey;
                }

                int get_heap_index() {
                        return heap_index;
                }

                void set_heap_index(int newIndex) {
                        heap_index = newIndex;
                }

        private:
                Key  key;       // the key of the element in the heap
                int  heap_index; 

};

#endif
