#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <string>
#include <vector>

class DPContainer
{
public:
	DPContainer (void);
	virtual ~DPContainer();

	std::string	 type;
	std::string	 name;

	long long	 offset;
	long long	 size;

	std::vector<DPContainer*> children;

	virtual void add_child (DPContainer *child);

protected:

private:

};

#endif // _CONTAINER_H_

