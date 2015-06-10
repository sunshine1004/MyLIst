#ifndef _MyList_
#define _MyList_

#include <iostream>
using namespace std;

template <class T>
class MyList{
private:
	T *a;
	int size;

	//the location of last element
	int point;
	//double the space of *a
	void double_space(){
		T *b = new T[size];
		for (int i = 0; i < size; ++i)
			b[i] = a[i];
		size *= 2;
		delete[]a;
		a = new T[size];
		for (int i = 0; i < size / 2; ++i)
			a[i] = b[i];
		delete []b;
	} 

public:
	
	friend MyList<T> operator+(const MyList<T> &l1, const T &item){
		MyList<T> tmp;							//create a temporary variable
		tmp.point = l1.point + 1;
		tmp.a = new T[l1.size + 1];
		for (int i = 0; i <= l1.point; ++i){
			tmp.a[i] = l1.a[i];
		}
		tmp.a[tmp.point] = item;
		return tmp;
	}

	friend MyList<T> operator+(const MyList<T> &l1, const MyList<T> &l2){
		MyList<T> tmp;				
		tmp.size = l1.size + l2.size;		
		delete[]tmp.a;					//clean the space
		tmp.a = new T[tmp.size];
		tmp.point = l1.point + l2.point + 1;
		int i;
		for (i = 0; i <= l1.point; ++i){
			tmp.a[i] = l1.a[i];
		}
		for (; i <= tmp.point; ++i){
			tmp.a[i] = l2.a[i - l1.point - 1];
		}
		return tmp;
	}

	friend ostream& operator<<(ostream &os, const MyList<T> &obj){
		os << "[";
		for (int i = 0; i <= obj.point; ++i){
			os << obj.a[i];
			if (i == obj.point) break;			//ensure will not print redundant ,
			os << ", ";
		}
		os << "]" ;
		return os;
	}

	MyList() {
		size = 100;
		a = new T[size];
		point = -1;			//show the array is empty
	}

	MyList(int num, const T &item)	{
		size = 2 * num;
		point = num - 1;
		a = new T[size];
		for (int i = 0; i < num; ++i)
			a[i] = item;
	}

	MyList(const MyList &l){
		size = l.size;
		a = new T[size];
		for (int i = 0; i <= l.point; ++i)
			a[i] = l.a[i];
		point = l.point;
	}

	MyList(T * arr, int len){
		size = 2 * len;
		a = new T[size];
		for (int i = 0; i < len; ++i)
			a[i] = arr[i];
		point = len - 1;
	}

	//to add a new element to the end of the array
	void push(const T & item){
		++point;
		if (point >= size)
			this->double_space();
		a[point] = item;
	}

	//return and delete the last element of the array
	T pop(){
		try{
			if (point == -1) throw long("!");		//prevent the index is wrong!
			else{
				T temp = a[point--];
				return temp;
			}
		}
		catch (long){
			cout << "------------------------------" << endl;
			cout << "It is empty!" << endl;
			cout << "------------------------------" << endl;
		}
	}

	//to insert a new element in the index of array
	void insert(int index, const T & item){
		try{
			if (index < 0) index += point + 1;
			if (index > point + 1 || index < 0) throw long("!");
			else{
				++point;
				if (point >= size) double_space();
				for (int i = point; i > index; --i){
					a[i] = a[i - 1];
				}
				a[index] = item;
			}
		}
		catch (long){
			cout << "------------------------------" << endl;
			cout << "the index is wrong!" << endl << endl;;
			cout << "------------------------------" << endl;
		}
	}

	//to clean all the elements of array
	void clean(){
		point = -1;
	}

	//return the number of elements of the array
	int get_size(){
		return (point + 1);
	}

	//to delete the elements frome start to end
	void erase(int start, int end){
		try{
			if (start < 0) start += point + 1;
			if (end < 0) end += point + 1;
			if (start > point || end > point || start > end || start < 0 || end < 0) throw long("!");
			else{
				for (int i = start; i < point - end + start; ++i){
					a[i] = a[i + end - start + 1];
				}
				point = point - end + start - 1;
			}
		}
		catch (long){
			cout << "------------------------------" << endl;
			cout << "the index is wrong!" << endl;
			cout << "------------------------------" << endl;
		}
	}

	//return the element on index
	T get_item(int index){
		try{
			if (index < 0) index += point + 1;
			if (index < 0 || index > point) throw long("!");
			else{
				return a[index];
			}
		}
		catch (long){
			cout << "------------------------------" << endl; 
			cout << "the index is wrong!" << endl;
			cout << "------------------------------" << endl;
		}
	}

	//return a new array from start to end
	MyList get_item(int start, int end){
		try{
			MyList<T>  temp;
			if (start < 0) start += point + 1;
			if (end < 0) end += point + 1;
			if (start > point || end > point || start < 0 || end < 0) throw long("!");
			else{
				if (end < start) {
					return temp;
				}
				else{
					while (end - start + 1 > temp.size) double_space();
					temp.point = end - start;
					for (int i = 0; i <= temp.point; ++i){
						temp.a[i] = a[start + i];
					}
					return temp;
				}
			}
		}
		catch (long){
			cout << "------------------------------" << endl;
			cout << "the index is wrong!" << endl;
			cout << "------------------------------" << endl;
		}
	}

	//return the number of item in the array
	int count(const T &item){
		int count = 0;
		for (int i = 0; i <= point; ++i){
			if (a[i] == item)
				++count;
		}
		return count;
	}

	//remove the first item in the array
	void remove(const T &item){
		bool flag = 0;
		int j = 0;
		for (int i = 0; i <= point; ++i){
			if (!flag && a[i] == item){
				flag = 1;
				continue;
			}
			
				a[j] = a[i];
				++j;
			
		}
		if (flag)
			--point;
	}

	MyList &operator= (const MyList &l){
		if (this == &l) return *this;
		delete[]a;
		a = new T[l.size];
		for (int i = 0; i <= l.point; ++i){
			a[i] = l.a[i];
		}
		point = l.point;
		return *this;
	}

	MyList &operator+=(const T &item){
		this->push(item);
		return *this;
	}

	MyList &operator+=(const MyList &l){
		MyList<T> temp(*this);
		size += l.size;
		point += l.point + 1;
		a = new int[size];
		for (int i = 0; i <= temp.point; ++i)
			a[i] = temp[i];
		for (int i = temp.point + 1; i <= point; ++i)
			a[i] = l.a[i - temp.point - 1];
		return *this;
	}

	T &operator[](int index){
		try{
			if (index < 0) index += point;
			if (index < 0 || index > point) throw long(1);
			else return a[index];
		}
		catch (long){
			cout << "------------------------------" << endl;
			cout << "index is wrong !" << endl << endl;
			cout << "------------------------------" << endl;
		}
	}

	//to sort the array
	//if the parameter is false, then from biggest to smallest
	void sort(bool less = true){
		quicksort(a, 0, point);
		if (!less)
			this->reverse();
	}

	//reverse the order of the array
	void reverse(){
		MyList<T> temp(*this);	
		for (int i = 0; i <= point; ++i){
			a[i] = temp.a[point - i];
		}
	}

	~MyList(){
		delete []a;
	}

};

//to sort the array
template <class T>
void quicksort(T a[], int left, int right){
	int i, j, tmp;
	if (left > right) return;
	i = left;
	tmp = a[i];
	j = right;
	while (i != j){
		while (a[j] >= tmp && i < j)
			--j;
		while (a[i] <= tmp && i < j)
			++i;
		if (i < j){
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	a[left] = a[i];
	a[i] = tmp;
	quicksort(a, left, i - 1);
	quicksort(a, i + 1, right);
}


#endif