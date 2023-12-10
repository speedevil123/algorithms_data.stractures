#include <iostream>
#include <string>
#include <vector>
#include <list>

class HashTable {
private:
    const size_t table_size = 100;
    std::vector<std::string> table;

public:
    HashTable() : table(table_size, "") {}

    int HashFunction(const std::string& key);
    void insert(const std::string& key, size_t& collisions_cnt);
    bool search(const std::string& key, size_t& comparisons_cnt);
    void remove(const std::string& key);
    std::ostream& print(std::ostream& out) const;
    void clear();
};

int HashTable::HashFunction(const std::string& key)
{
    int hash = 0;
    for (char ch : key)
    {
        hash += ch;
    }
    return hash % table_size;
}

void HashTable::insert(const std::string& key, size_t& collisions_cnt)
{
    int index = HashFunction(key);
    int count = 1;
    collisions_cnt = 0;
    while (!table[index].empty())
    {
        collisions_cnt++;
        index = (index + count * count) % table_size;
        count++;
    }
    table[index] = key;
}

bool HashTable::search(const std::string& key, size_t& comparisons_cnt)
{
    int index = HashFunction(key);
    int count = 1;
    comparisons_cnt = 0;
    while (!table[index].empty())
    {
        comparisons_cnt++;
        if (table[index] == key) return true;
        index = (index + count * count) % table_size;
        count++;
    }
    return false;
}

void HashTable::remove(const std::string& key)
{
    int index = HashFunction(key);
    int count = 1;
    while (!table[index].empty())
    {
        if (table[index] == key)
        {
            table[index] = "";
            return;
        }
        index = (index + count * count) % table_size;
        count++;
    }
}



std::ostream& HashTable::print(std::ostream& out) const
{
    for (int i = 0; i < table_size; ++i)
    {
        out << i << ": " << table[i] << std::endl;
    }
    return out;
}

void HashTable::clear()
{
    for (int i = 0; i < table_size; ++i)
    {
        table[i] = "";
    }
}

std::ostream& operator << (std::ostream & out,const HashTable& p)
{
    p.print(out);
    return out;
}

