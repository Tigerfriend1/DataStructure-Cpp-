#include <iostream>
#include <string>
using namespace std;


#include <iostream>
#include <string>
using namespace std;

template<class T> class CircularChain; //forward declaration

template<class T>
class ChainNode {
	friend class CircularChain<T>;
public:
	ChainNode(T element = 0)
	{
		data = element;
		link = 0;
	}
	friend ostream& operator<<<T>(ostream&, ChainNode<T>&);
private:
	T data;
	ChainNode<T>* link;
};

template <class T>
ostream& operator<<(ostream& os, ChainNode<T>& cn) {

	return os;
}
template<class T>
class CircularChain {
public:
	CircularChain() { first = 0; };
	~CircularChain();
	bool NotNull();
	bool NextNotNull();
	CircularChain<T>& Merge(CircularChain<T>& );
	void GetData(Product*, int);
	friend ostream& operator<<(ostream&, CircularChain<T>&);//List 출력
private:
	int Add(const T& element); //add a new node after first
	ChainNode<T>* first; //point to the first node
};
template <class T>
ostream& operator<<(ostream& os, CircularChain<T>& cc) {

	return os;
}
template <class T>
CircularChain<T>::~CircularChain() { }

template <class T>
class Product {
    friend class CircularChain<T>;
private:
	string Name;
	int price;
public:
	Product(string st, int pay);
};

int main(void) {
	Product pdt1[] = { Product("K9", 6000),Product("G80", 6500),Product("K5", 4000),Product("SM3", 3000),Product("K8", 4500),Product("K3", 2000),Product("Sonata", 4300) };
	Product pdt2[] = { Product("Volvo", 9000),Product("Toyota", 5500),Product("Honda", 8800), Product("Tesla", 7000),Product("BMW", 7300),Product("Lexus", 6800),Product("Ford", 4900),Product("Lincoln", 12000),Product("Audi", 7700) };
	char select;
	CircularChain<Product> a, b, c;
	int count = 0;
	
		cout << endl << "Select command:1: list a의 입력,2: list b의 입력, 3: 출력, 4: merge sort, 5: Merge 출력, 6: quit" << endl;
		cin >> select;
		switch (select)
		{
		case '1':
			cout << "리스트 a 입력: ";
			count = sizeof pdt1 / sizeof pdt1[0];
        }

    return 0;
}
