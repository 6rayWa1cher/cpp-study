#ifndef EDUSANDBOX_PERSONS_H
#define EDUSANDBOX_PERSONS_H

#include <string>
#include <vector>

class TGUPerson {
public:
	TGUPerson(std::string name, std::string address);

	void setAddress(const std::string& address);

	std::string getAddress();

	std::string getName();

	virtual void print() const;

protected:
	std::string _name;
	std::string _address;
};

class TGUStudent : public TGUPerson {
public:
	TGUStudent(const std::string& name, const std::string& address, int course, double rating);

	void setRating(double newRating);

	void print() const override;

protected:
	int _course;
	double _rating;
};

#endif