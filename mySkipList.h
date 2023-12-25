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

    bool insert_element(K key, V value) {
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

    void display_list() {
        std::cout << "DISPLAY THE JUMP LIST" << std::endl;
        Node<K, V>* node = header->forward[0];
        while (node != nullptr) {
            std::cout << "[" << node->key << ":" << node->value << "]";
            node = node->forward[0];
            if (node != nullptr) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
};

#endif /* MYSKIPLIST_H */
