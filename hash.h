/**
 * A hash for our snake game */
#ifndef _HASH_H_
#define _HASH_H_

#include <math.h>
#include <string>
#include <vector>
#include <forward_list>
#include <iterator>
#include <iostream>
using size_type = size_t;

template <typename KeyType,
		  typename DataType,
		  typename KeyHash = std::hash<KeyType> ,
		  typename KeyEqual = std::equal_to<KeyType> >
class HashTable
{

	class HashEntry{

		public:

			HashEntry(KeyType k_, DataType d_):m_key(k_),m_data(d_)

			{/*Empty*/};

			KeyType m_key;
			//!<Stores the key for an entry.

			DataType m_data;//!<Stores the data for an entry.
	};

	public:

		using Entry = HashEntry;

		HashTable(void): tablesize(101),currentSize(0) { Lists.resize(101);}


		explicit HashTable(size_type size): tablesize(next_prime(size)), currentSize(0)
		{Lists.resize(next_prime(size));}
		
		void makeEmpty();
			
		bool insert(const KeyType & key_ , const DataType & data_item_ ){
		
			auto & whichList = Lists[ hashFunc(key_) % tablesize];
			Entry new_entry (key_, data_item_ );
			auto itr = whichList.begin();
			auto itr_b = whichList.before_begin();
			auto end = whichList.end();
			for (; itr != end; ++itr) {
				
				itr_b++;
				if (true == equalFunc((*itr).m_key , new_entry.m_key)){
					return false;
				}
			}

			whichList.insert_after(itr_b, new_entry);
//			whichList.push_front(new_entry);

				if(++currentSize > tablesize ) 
					rehash( );

				return true;
		}


		bool retrieve(const KeyType & key_,  DataType & data_item_) const{

			
			auto & whichList = Lists[ hashFunc(key_) % tablesize];
			for (auto i = whichList.begin(); i != whichList.end(); ++i) {
				if (true == equalFunc((*i).m_key , key_)){
					data_item_ = (*i).m_data;
					return true;
				}
			}
			return false;

		}
		
		void print() const
		{
			if(!Lists.empty())
			{
				for (auto Lists_iter = Lists.begin(); Lists_iter != Lists.end(); ++Lists_iter) {
					if(!(*Lists_iter ).empty())
					for (auto j = (*Lists_iter ).begin(); j != (*Lists_iter ).end(); ++j) {
						std::cout << "Key: " << (*j).m_key <<" Data: " << (*j).m_data<< std::endl;
					}
				}

			}
		}

		void clear()
		{

		Lists.clear();

		}
		
		bool empty ( void ) const{
		return currentSize == 0;
		}


		size_type count (void) const{
			return currentSize;
		}

		bool remove(const KeyType & key_){

			auto & whichList = Lists[ hashFunc(key_) % tablesize];
			auto itr_back = whichList.before_begin();
			for (auto i = whichList.begin(); i != whichList.end(); ++i) {
		//		std::cout << *i << std::endl;
				if (true == equalFunc((*i).m_key , key_ )){
					whichList.erase_after(itr_back);
					return true;
				}
				itr_back++;
			}	
				return false;
		}

		bool updateValue(const KeyType & key_ , const DataType & data_item_){
			remove(key_);
			insert(key_,data_item_);
		}

	private:

		std::vector<std::forward_list<HashEntry>> Lists; 
		
		size_type currentSize;
		size_type tablesize;
	
		// auxiliary functions
		KeyHash hashFunc;
		KeyEqual equalFunc;
		
		size_type next_prime(size_type number){

			for (int i = 2; i < sqrt(number); ++i) {
				if(number % i == 0) return next_prime(number+1);
			}
			return number;
		}
		
		
		void rehash(){

	//		std::cout << "calls to rehash " << std::endl;
			std::vector<std::forward_list<HashEntry>> oldLists = Lists;
			// Create new double-sized, empty table
			tablesize =  next_prime( 2 * tablesize ); 
			
			Lists.resize(tablesize) ;
			currentSize = 0;
		
			for( auto & thisList : Lists )
				thisList.clear( ); 
			// Copy table over
			for( auto & copyLists : oldLists )
				for( auto & x : copyLists )
					insert(x.m_key, x.m_data);
		}
		

};
#endif
