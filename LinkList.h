#pragma once
#include <memory>
#include <iostream>
namespace linklist {

template <typename T>
struct Node {
	T m_data;
	std::unique_ptr<Node<T>> m_next;
	Node(T value) {
		m_data = value;
		m_next = nullptr;
	}
	~Node() = default;
};

template <typename T>
class LinkList
{

	std::unique_ptr<Node<T>> m_root;

public:
	LinkList() = default;
	~LinkList() = default;

	void add(T value) {
		auto newNode = std::make_unique<Node<T>>(value);
		if (m_root == nullptr) {
			m_root = std::move(newNode);
		}
		else {
			auto temp = m_root.get();
			while (temp->m_next != nullptr)
				temp = temp->m_next.get();
			
			temp->m_next = std::move(newNode);
		}
	}

	void insert(T val, int pos) {

		if (m_root == nullptr) {
			add(val);
			return;
		}
		auto node = m_root.get();
		auto newNode = std::make_unique<Node<T>>(val);
		for (int i = 0; i < pos - 1; i++) {
			if (node->m_next == nullptr) {
				node->m_next = std::move(newNode);
				return;
			}
			node = node->m_next.get();
		}
		newNode->m_next = std::move(node->m_next);
		node->m_next = std::move(newNode);
	}

	 
	void removeByValue(T value) {
		if (m_root == nullptr)
			return;

		if (m_root->m_data == value) {
			auto del = std::move(m_root);
			m_root = std::move(del->m_next);
			return;
		}
		auto node = m_root.get();
		while (node->m_next != nullptr) {
			if (node->m_next->m_data == value){
				auto del = std::move(node->m_next);
				node->m_next = std::move(del->m_next);
				break;
			}
		    node = node->m_next.get();
		}
	}

	void removeAllUsingStack() {
		auto del = std::move(m_root);
	}
	

	void removeAll() {
		if (m_root == nullptr)
			return;

		while (m_root->m_next != nullptr)
		{
			auto node = m_root.get();
			while (node->m_next->m_next != nullptr)
				node = node->m_next.get();
			auto del = std::move(node->m_next);
			std::cout << " Removing " << del->m_data<< "\n";
		}
		auto del = std::move(m_root);

	}
	
 
	void show() {
		if (m_root == nullptr) {
			std:: cout << "Empty list\n";
		}
		else {
			auto node = m_root.get();
			while (node != nullptr) {
				std::cout<< node->m_data<<" ";
				node = node->m_next.get();
			}
			std:: cout << "\n";
		}
	}
	  
};


	class DriverProgram {
		public:
			void test();
	};
}
