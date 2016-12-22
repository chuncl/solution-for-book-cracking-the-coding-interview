//An animal shelter holds only dogs and cats, and operates on a strictly "first in, first out" basis.People must adopt either the "oldest"
//(based on arrival time) of all animals at the shelter, or they can select whether they would prefer a dog or a cat(and will receive the oldest animal of that type).
//They cannot select which specific animal they would like.Create the data structures to maintain this system and implement operations such as enqueue, dequeueAny,
//dequeueDog and dequeueCat.You may use the built - in L inkedL ist data structure.

#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include <memory>

class Animal {
public:
	Animal(std::string& name, size_t order) : _name(name), _order(order) {}
	virtual ~Animal() {}

	size_t getOrder() {
		return _order;
	}

	void setOrder(size_t order) {
		_order = order;
	}

	std::string getName() {
		return _name;
	}

	bool isOrderThan(const Animal& other) {
		return _order < other._order;
	}

	virtual std::string getType() = 0;

private:
	std::string _name;
	size_t _order;
};

class Dog : public Animal {
public:
	Dog(std::string& name, size_t order=0) :Animal(name, order) {};
	virtual std::string getType() {
		return "dog";
	}
};

class Cat : public Animal {
public:
	Cat(std::string& name, size_t order=0) : Animal(name, order) {};
	virtual std::string getType() {
		return "cat";
	}
};

class AnimalSheler {
public:
	AnimalSheler() : _order(0) {}
	~AnimalSheler() {}

	void enque(Animal& a) {		
		a.setOrder(_order++);
		if (a.getType() == "dog") {
			// cannot make_unique for a abstract class, e.g., std::make_unique<Animal>
			// but it is OK to have: std::unique_ptr<base> derived = std::unique_ptr<Derived>(new Derived);
			_dogQueue.push_back(std::make_unique<Dog>(a.getName(), a.getOrder()));
		}
		else if (a.getType() == "cat")
			_catQueue.push_back(std::make_unique<Cat>(a.getName(), a.getOrder()));
		else
			assert(true);
	}

	std::unique_ptr<Animal> dequeue() {
		if (_dogQueue.empty()) {
			// needs to use std::move, as list front return unique_ptr that cannot be copiable
			// however, it is valid 
			//using namespace std;

			//unique_ptr<int> foo()
			//{
			//	unique_ptr<int> p(new int(10));

			//	return p;                   // 1
			//								//return move( p );         // 2
			//}

			//int main()
			//{
			//	unique_ptr<int> p = foo();

			//	cout << *p << endl;
			//	return 0;
			//}

			std::unique_ptr<Animal> aptr = std::move(_catQueue.front());
			_catQueue.pop_front();
			return aptr;
		}

		if (_catQueue.empty()) {
			std::unique_ptr<Animal> aptr = std::move(_dogQueue.front());
			_dogQueue.pop_front();
			return aptr;
		}

		if (_catQueue.front()->isOrderThan(*(_dogQueue.front()))) {
			std::unique_ptr<Animal> aptr = std::move(_catQueue.front());
			_catQueue.pop_front();
			return aptr;
		}
		else {
			std::unique_ptr<Animal> aptr = std::move(_dogQueue.front());
			_dogQueue.pop_front();
			return aptr;
		}
	}

	// cannot return std::unique_ptr<Cat>, no conversion from std::unique_ptr<Animal> to that
	std::unique_ptr<Animal> dequeueCat() {
		std::unique_ptr<Animal> aptr = std::move(_catQueue.front());		
		_catQueue.pop_front();
		return aptr;
	}

	std::unique_ptr<Animal> dequeueDog() {
		std::unique_ptr<Animal> aptr = std::move(_dogQueue.front());
		_dogQueue.pop_front();
		return aptr;
	}

	bool empty() {
		return _dogQueue.empty() && _catQueue.empty();
	}

	bool dogEmpty() {
		return _dogQueue.empty();
	}

	bool catEmpty() {
		return _catQueue.empty();
	}

private:
	std::list<std::unique_ptr<Animal> > _dogQueue;
	std::list<std::unique_ptr<Animal> > _catQueue;
	size_t _order;
};

int main()
{
	Dog d(std::string("1st dog"));
	Dog d1(std::string("2nd dog"));
	Dog d2(std::string("3rd dog"));

	Cat c(std::string("1st cat"));
	Cat c1(std::string("2nd cat"));
	Cat c2(std::string("3rd cat"));

	AnimalSheler as;
	
	as.enque(d), as.enque(c), as.enque(d1);
	as.enque(c1), as.enque(d2), as.enque(c2);

	while (!as.empty()) {
		std::unique_ptr<Animal> ans = as.dequeue();
		std::cout << ans->getName() << std::endl;
	}

	as.enque(d), as.enque(c), as.enque(d1);
	as.enque(c1), as.enque(d2), as.enque(c2);

	std::cout << "DEQUE DOG: ==>" << std::endl;
	while (!as.dogEmpty()) {
		std::unique_ptr<Animal> ans = as.dequeueDog();
		std::cout << ans->getName() << std::endl;
	}

	std::cout << "DEQUE CAT: ==>" << std::endl;
	while (!as.catEmpty()) {
		std::unique_ptr<Animal> ans = as.dequeueCat();
		std::cout << ans->getName() << std::endl;
	}
		
	return 0;
}