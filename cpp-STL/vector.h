/*
* AUTHOR: ASHWIN ABRAHAM
*/
#define NULL 0
const unsigned int inc_length = 5;

template <typename T>
class vector{
    private:
        unsigned int len;
        unsigned int alloc_len;
        T* vec;
    public:
        vector(unsigned int l = 0, T fill = T()): alloc_len((1 + l/inc_length)*inc_length), len(l){
            vec = new T [alloc_len];
            for(unsigned int i = 0; i<len; ++i) vec[i] = fill;
        }
        
        vector(const vector& copy){
            len = copy.len;
            alloc_len = copy.alloc_len;
            vec = new T [alloc_len];
            for(unsigned int i = 0; i<len; ++i) vec[i] = copy.vec[i];
        }

        vector& operator=(const vector& assign){
            if(assign == *this) return *this;
            delete [] vec;
            len = assign.len;
            alloc_len = assign.alloc_len;
            vec = new T [alloc_len];
            for(unsigned int i = 0; i<len; ++i) vec[i] = assign.vec[i];
            return *this;
        }

        ~vector(){
            delete [] vec;
        }

        unsigned int size() const{
            return len;
        }

        T& operator[](int i){
            return vec[i];
        }

        void push_back(const T& push){
            if(len==alloc_len){
                alloc_len+=inc_length;
                T* temp = new T [alloc_len];
                for(unsigned int i = 0; i<len; ++i) temp[i] = vec[i];
                temp[len] = push;
                ++len;
                delete [] vec;
                vec = temp;
                return;
            }
            vec[len] = push;
            ++len;
            return;
        }

        void pop_back(){
            if(len>0) --len;
            return;
        }


        class iterator{
            private:
                T* ptr;
            public:
                iterator(T* p = NULL): ptr(p){}

                iterator operator+(int i) const{
                    return iterator(ptr+i);
                }

                iterator operator-(int i) const{
                    return iterator(ptr-i);
                }

                int operator-(const iterator& other) const{
                    return ptr-other.ptr;
                }

                bool operator==(const iterator& other) const{
                    return ptr==other.ptr;
                }

                bool operator!=(const iterator& other) const{
                    return ptr!=other.ptr;
                }

                T& operator*() const{
                    return *ptr;
                }

                T& operator[](int i){
                    return ptr[i];
                }

                iterator operator++(){
                    iterator temp = *this;
                    ++ptr;
                    return temp;
                }

                iterator& operator++(int){
                    ++ptr;
                    return *this;
                }

                iterator operator--(){
                    iterator temp = *this;
                    ++ptr;
                    return temp;
                }

                iterator& operator--(int){
                    ++ptr;
                    return *this;
                }

        };


        const iterator begin(){
            return iterator(vec);
        }

        const iterator end(){
            return iterator(vec+len);
        }

        void insert(iterator pos, const T& val){
            if(len==alloc_len){
                alloc_len+=inc_length;
                T* temp = new T [alloc_len];
                for(unsigned int i = 0; i<=len; ++i){
                    if(i<(pos-(this->begin()))) temp[i] = vec[i];
                    else if(i>(pos-(this->begin()))) temp[i] = vec[i-1];
                    else temp[i] = val;
                }
                ++len;
                delete [] vec;
                vec = temp;
                return;
            }
            T temp = val;
            for(unsigned int i = (pos-(this->begin())); i<=len; ++i){
                T temptemp = temp;
                temp = vec[i];
                vec[i] = temptemp;
            }
            ++len;
            return;
        }

        void erase(iterator pos){
            if(len==0) return;
            --len;
            for(unsigned int i = (pos-(this->begin())); i<len; ++i) vec[i] = vec[i+1];
            return;
        }
};