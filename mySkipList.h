#ifndef MYSKIPLIST_H
#define MYSKIPLIST_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

template<typename K, typename V>
class Node {
public:
    K key;
    V value;
    std::vector<Node<K, V>*> forward;

    Node(K k, V v, int level) : key(k), value(v), forward(level + 1, nullptr) {}
};

template<typename K, typename V>
class SkipList {
private:
    int maxLevel;
    float probability;
    Node<K, V>* header;
    int level;
    int size;

    // private method: get random level for the data inserted
    int get_random_level() {
        int lvl = 0;
        while (rand() % 100 < static_cast<int>(probability * 100) && lvl < maxLevel) {
            lvl++;
        }
        return lvl;
    }

public:
    SkipList(int maxLevel, float probability) 
        : maxLevel(maxLevel), 
          probability(probability), 
          level(0), 
          size(0), 
          header(new Node<K, V>(K(), V(), maxLevel)) {}

    ~SkipList() {
        Node<K, V>* current = header->forward[0]; 
        while (current != nullptr) {
            Node<K, V>* next = current->forward[0];
            delete current;
            current = next;
        }
        delete header;
    }

    // insert element into the skiplist
    bool insert_element(K key, V value);
    // delete element from the skiplist
    bool delete_element(K key);
    // display the level0 list, i.e. the full list
    void display_list() const;
    // display every list we have, including the full list
    void full_display_list() const;

};

template<typename K, typename V>
bool SkipList<K, V>::insert_element(K key, V value) {
    std::vector<Node<K, V>*> update(header->forward);
    Node<K, V>* current = header;

    // find the position to insert
    for (int i = level; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    // element already exists
    if (current != nullptr && current->key == key) {
        return false;
    }

    // update
    int random_level = get_random_level();
    if (random_level > this->level) {
        for (int i = this->level + 1; i <= random_level; ++i) {
            update[i] = header;
        }
        this->level = random_level;
    }

    Node<K, V>* insert_node = new Node<K, V>(key, value, random_level);
    for (int i = 0; i <= random_level; ++i) {
        insert_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = insert_node;
    }

    size++;
    return true;
}

template<typename K, typename V>
bool SkipList<K, V>::delete_element(K key) {
    std::vector<Node<K, V>*> update(header->forward);
    Node<K, V>* current = header;

    // locate the nodes to update
    for (int i = level; i >= 0; --i) {
        while (current->forward[i] != nullptr && current->forward[i]->key < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    //check if the element not exist
    current = current->forward[0];
    if (current == nullptr || current->key != key) {
        return false;
    }

    // update pointers and delete the node
    for (int i = 0; i <= level; --i) {
        if (update[i]->forward != current) {
            break;
        }
        update[i]->forward[i] = current->forward[i];
    }

    delete current;

    // update level
    while (level > 0 && header->forward[level] == nullptr) {
        level--;
    }

    size--;
    return true;
}

template<typename K, typename V>
void SkipList<K, V>::display_list() const {
    std::cout << "DISPLAY THE JUMP LIST" << std::endl;
    Node<K, V>* node = header->forward[0];
    while (node != nullptr) {
        std::cout << "[" << node->key << ":" << node->value << "]";
        node = node->forward[0];
        if (node != nullptr) std::cout << " -> ";
    }
    std::cout << std::endl;
}

template<typename K, typename V>
void SkipList<K, V>::full_display_list() const {
    std::cout << "FULL DISPLAY OF SKIP LIST" << std::endl;

    for (int i = level - 1; i >= 0; i--) {
        Node<K, V>* node = header->forward[i];
        std::cout << "Level " << i << ": ";
        while (node != nullptr) {
            std::cout << "[" << node->key << ":" << node->value << "]";
            node = node->forward[i];
            if (node != nullptr) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
}


#endif /* MYSKIPLIST_H */