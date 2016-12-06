#pragma once
#include <memory>
#include <iostream>

namespace dlinklist{
	template <typename T>
	struct Node {
	public:
		T m_data;
		std::unique_ptr<Node<T>> m_next = nullptr;
		Node<T>* m_previous = nullptr;
		Node(T value) {
			m_data = value;
		}
		~Node() = default;// {std::cout << "Element removed with value " << m_data <<"\n";}
	};

	template <typename T>
	class DoubleLinkList
	{
		
		std::unique_ptr<Node<T>> m_root;
		Node<T>* m_end = nullptr;

	public:
		DoubleLinkList() = default;
		~DoubleLinkList() = default;

		void add(T value) {
			if (m_root == nullptr) {
				m_root = std::make_unique<Node<T>>(value);
				m_end = m_root.get();
				return;
			}
			auto node = m_root.get();
			while (node->m_next != nullptr)
				node = node->m_next.get();

			auto tempNode = std::make_unique<Node<T>>(value);
			tempNode->m_previous = node;
			m_end = tempNode.get();
			node->m_next = std::move(tempNode);
			
		}

		
		void show() {
			if (m_root == nullptr) {
				std::cout << "empty list";
			}
			else {
				auto node = m_root.get();
				while (node != nullptr) {
					std::cout << node->m_data << " ";
					node = node->m_next.get();
				}
				std::cout << "\n";
			}
		}

		void showReverse() {
			if (m_end == nullptr) {
				std::cout << "empty list";
			}
			else {
				auto node = m_end;
				while (node != nullptr) {
					std::cout << node->m_data << " ";
					node = node->m_previous;
				}
				std::cout << "\n";
			}
		}

		void showMiddle() {

			auto fast = m_root.get();
			auto slow = m_root.get();
			while (fast != nullptr && fast->m_next != nullptr) {
				fast = fast->m_next->m_next.get();
				slow = slow->m_next.get();
			}
			std::cout << "Middle : " << slow->m_data <<"\n";
		}

		void showPairSum(T sum) {
			auto front = m_root.get();
			auto back = m_end;

			while (front != nullptr && back != nullptr) {
				if (front->m_data + back->m_data == sum) {
					std::cout << "Sum " << front->m_data << "," << back->m_data << " \n";
					front = front->m_next.get();
					back = back->m_previous;
				}
				else if (front->m_data + back->m_data < sum) {
					front = front->m_next.get();
				}

				else if (front->m_data + back->m_data > sum) {
					back = back->m_previous;
				}

			}
		}
	};

	class DriverProgram {
	public:
		void test();
	};
}
