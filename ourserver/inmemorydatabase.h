#ifndef INMEMORY_DATABASE_H
#define INMEMORY_DATABASE_H

#include "database_interface.h"
#include "article.h"
#include "newsgroup.h"
#include <map>

class InMemoryDatabase : public Database_interface{
public:

private:
	std::map news_groups;
};

#endif