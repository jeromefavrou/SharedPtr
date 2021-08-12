
#ifndef SHAREDPTR_HPP
#define SHAREDPTR_HPP


#define __ASSERT_USE_STDERR
  
#include <assert.h>

/*
   _____ _                        _ _____  _        
  / ____| |                      | |  __ \| |       
 | (___ | |__   __ _ _ __ ___  __| | |__) | |_ _ __ 
  \___ \| '_ \ / _` | '__/ _ \/ _` |  ___/| __| '__|
  ____) | | | | (_| | | |  __/ (_| | |    | |_| |   
 |_____/|_| |_|\__,_|_|  \___|\__,_|_|     \__|_|   
                                                    
                                                    
    memory managemnt
    manage a shared pointers
    makes the use of pointers safe
    pointer managed even when copying SharedPtr
*/
template<typename T> class SharedPtr 
{
    protected : 
        // shared ptr
        T * m_ptr;

        //number of pointers to the same variable
        int * m_count;

    public:
        SharedPtr(void):m_ptr(nullptr),m_count(new int(0))
        {
        }

        //constructor with pointer passing
        SharedPtr(T * _ctr):m_ptr(_ctr),m_count(new int(1))
        {
        }

        //constructor with raw variable passing
        SharedPtr(T & _ctr):m_ptr(&_ctr),m_count(new int(1))
        {
        }

        //share constructor
        SharedPtr(SharedPtr<T> const & _trm):m_ptr(_trm.m_ptr)
        {
            //share counter
            this->m_count=_trm.m_count;

            //update counter
            ++*this->m_count;
        }

        //copy constructor
        SharedPtr operator=(SharedPtr<T> const & _trm)
        {
            //free actual ptr
            this->free();

            //share counter
            this->m_count= _trm.m_count;
            //update counter
            ++*this->m_count;

            //shared ptr
            this->m_ptr= _trm.m_ptr;

            return *this;
        }

        //access to give pointer
        virtual T * operator->()
        {
            //check if ptr is null and else throw an assert
            assert(!this->isNull());

            return this->m_ptr;
        }

        //return the counter
        int getCount(void) const 
        {
            return *this->m_count;
        }

        //returns the shared pointer without allowing its modification
        T * get(void) const 
        {
            return this->m_ptr;
        }

        //check if ptr is null
        inline bool isNull(void) const
        {
            return this->m_ptr == nullptr;
        }

        void free(void)
        {
            //if last shared pointer
            //free memory
            if(*this->m_count == 1)
            {
                delete m_ptr;
                delete this->m_count;

                return;
            }

            //uncounting pointer to the counter
            --*this->m_count;
        }

        //destructor
        virtual ~SharedPtr()
        {    
            //if last shared pointer
            //free memory
            this->free();
        }

};

#endif

