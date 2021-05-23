#include <stdexcept>

namespace lasd
{

	/* ************************************************************************** */
	/*                                  NODE                                      */
	/* ************************************************************************** */

	//Constructor with specifier Data - NODE (Copy)
	template <typename Data>
	List<Data>::Node::Node(const Data &newData)
	{
		info = newData;
		next = nullptr;
	}

	//Constructor with specifier Data - NODE (Move)
	template <typename Data>
	List<Data>::Node::Node(Data &&dato)
	{
		std::swap(info, dato);
		next = nullptr;
	}

	//Copy constructor - NODE
	template <typename Data>
	List<Data>::Node::Node(const Node &assNode)
	{
		info = assNode.info;
		next = assNode.next;
	}

	//Move constructor - NODE
	template <typename Data>
	List<Data>::Node::Node(const Node &&assNode) noexcept
	{
		std::swap(info, assNode.info);
		std::swap(next, assNode.next);
	}

	//Operator == - NODE
	template <typename Data>
	bool List<Data>::Node::operator==(const Node &compareNode) const noexcept
	{
		if (info == compareNode.info)
		{
			return true;
		}
		return false;
	}

	//Operator != - NODE
	template <typename Data>
	bool List<Data>::Node::operator!=(const Node &compareNode) const noexcept
	{
		return !(*this == compareNode);
	}

	/* ************************************************************************** */
	/*                                 LIST                                       */
	/* ************************************************************************** */

	//Constructor
	//template <typename Data>
	//List<Data>::List()
	//{
	//	head = nullptr;
	//	tail = nullptr;
	//	size = 0;
	//}

	//Constructor (with Linear Container)
	template <typename Data>
	List<Data>::List(const LinearContainer<Data> &container)
	{
		size = 0;

		for (ulong index = 0; index < container.Size(); ++index)
		{
			InsertAtBack(container[index]);
		}
	}

	//Copy constructor
	template <typename Data>
	List<Data>::List(const List<Data> &cpyList)
	{
		Node *tmp = cpyList.head;
		while(tmp!=nullptr){
			InsertAtBack(tmp->info);
			tmp=tmp->next;
		}
	}

	//Move constructor
	template <typename Data>
	List<Data>::List(List<Data> &&cpyList) noexcept
	{
		std::swap(head, cpyList.head);
		std::swap(tail, cpyList.tail);
		std::swap(size, cpyList.size);
	}

	//Destructor
	template <typename Data>
	List<Data>::~List()
	{
		Clear();
        delete head;
	}

	/* ************************************************************************** */

	//Copy assignment
	template <typename Data>
	List<Data> &List<Data>::operator=(const List<Data> &assList)
	{
		List<Data> *tmplist = new List<Data>(assList);
		std::swap(*tmplist, *this);
		delete (tmplist);
		return *this;
	}

	//Move assignment
	template <typename Data>
	List<Data> &List<Data>::operator=(List<Data> &&assList) noexcept
	{
		std::swap(head, assList.head);
		std::swap(tail, assList.tail);
		std::swap(size, assList.size);
		return *this;
	}

	/* ************************************************************************** */

	//Operator ==
	template <typename Data>
	bool List<Data>::operator==(const List &compareList) const noexcept
	{
		if (size == compareList.size)
		{
			Node *tmphead = head;
			Node *tmpCmp = compareList.head;

			while (tmphead != nullptr)
			{
				if (tmphead->info != tmpCmp->info)
				{
					return false;
				}
				tmphead = tmphead->next;
				tmpCmp = tmpCmp->next;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	//Operator !=
	template <typename Data>
	bool List<Data>::operator!=(const List &compareList) const noexcept
	{
		return !(*this == compareList);
	}

	/* ************************************************************************** */

	//Insert At Front (Copy)
	template <typename Data>
	void List<Data>::InsertAtFront(const Data &dato) noexcept
	{
		Node *newNodo = new Node(dato);
		if (head == nullptr)
		{
			head = newNodo;
			tail = newNodo;
		}
		else
		{
			newNodo->next = head;
			head = newNodo;
		}
		size = size + 1;
	}

	//Insert At Front (Move)
	template <typename Data>
	void List<Data>::InsertAtFront(Data &&dato) noexcept
	{
		Data mvDato = std::move(dato);
		Node *newNodo = new Node(mvDato);
		if (head == nullptr)
		{
			head = newNodo;
			tail = newNodo;
		}
		else
		{
			newNodo->next = head;
			head = newNodo;
		}
		size = size + 1;
	}

	//Remove From Front
	template <typename Data>
	void List<Data>::RemoveFromFront()
	{
		if (size != 0)
		{
			Node *ptr = head;
			head = head->next;
			size = size - 1;
			delete ptr;
		}
		else
		{
			throw std::length_error("Access to an empty list.");
		}
	}

	//Remove From Front (with return value)
	template <typename Data>
	Data List<Data>::FrontNRemove()
	{
		if (size != 0)
		{
			Node *ptr = head;
			Data returner = head->info;
			head = head->next;
			size = size - 1;
			delete ptr;
			return returner;
		}
		else
		{
			throw std::length_error("Access to an empty list.");
		}
	}

	//Insert At Back (Copy)
	template <typename Data>
	void List<Data>::InsertAtBack(const Data &dato) noexcept
	{
		Node *newNodo = new Node(dato);
		if (head == nullptr)
		{
			head = newNodo;
			tail = newNodo;
		}
		else
		{
			tail->next = newNodo;
			tail = newNodo;
		}
		size++;
	}

	//Insert At Back (Move)
	template <typename Data>
	void List<Data>::InsertAtBack(Data &&dato) noexcept
	{
		Data mvDato = std::move(dato);
		Node *newNodo = new Node(mvDato);
		if (head == nullptr)
		{
			head = newNodo;
			tail = newNodo;
		}
		else
		{
			tail->next = newNodo;
			tail = newNodo;
		}
		size++;
	}

	/* ************************************************************************** */

	//Clear
	template <typename Data>
	void List<Data>::Clear()
	{
		if (size>0) {
			while (head != nullptr)
			{
				Node *tmp = head;
				head = head->next;
				delete tmp;
			}
		}
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	/* ************************************************************************** */

	//Front Access
	template <typename Data>
	Data &List<Data>::Front() const
	{
		if (size != 0)
		{
			return head->info;
		}
		else
		{
			throw std::length_error("Access to an empty list.");
		}
	}

	//Back Access
	template <typename Data>
	Data &List<Data>::Back() const
	{
		if (size != 0)
		{
			return tail->info;
		}
		else
		{
			throw std::length_error("Access to an empty list.");
		}
	}

	//Access for []
	template <typename Data>
	Data &List<Data>::operator[](const ulong index) const
	{
		if (index < size)
		{
			Node *tmp = head;
			for (int i = 0; i < index; ++i)
			{
				tmp = tmp->next;
			}
			return tmp->info;
		}
		else
		{
			throw std::out_of_range("Access at index " + std::to_string(index) + "; list size:" + std::to_string(size));
		}
	}

	/* ************************************************************************** */

	//List MapPreOrder
	template <typename Data>
	void List<Data>::MapPreOrder(MapFunctor function, void *parametro)
	{
		MapPreOrder(function, parametro, head);
	}

	//List MapPostOrder
	template <typename Data>
	void List<Data>::MapPostOrder(MapFunctor function, void *parametro)
	{
		MapPostOrder(function, parametro, head);
	}

	//List FoldPreOrder
	template <typename Data>
	void List<Data>::FoldPreOrder(FoldFunctor function, const void *parametro, void *accumulatore) const
	{
		FoldPreOrder(function, parametro, accumulatore, head);
	}

	//List FoldPostOrder
	template <typename Data>
	void List<Data>::FoldPostOrder(FoldFunctor function, const void *parametro, void *accumulatore) const
	{
		FoldPostOrder(function, parametro, accumulatore, head);
	}

	/* ************************************************************************** */

	//Specific List MapPreOrder
	template <typename Data>
	void List<Data>::MapPreOrder(MapFunctor fun, void *par, Node *curr)
	{
		for (; curr != nullptr; curr = curr->next)
		{
			fun(curr->info, par);
		}
	}

	//Specific List MapPostOrder
	template <typename Data>
	void List<Data>::MapPostOrder(MapFunctor fun, void *par, Node *curr)
	{
		if (curr != nullptr)
		{
			MapPostOrder(fun, par, curr->next);
			fun(curr->info, par);
		}
	}

	//Specific List FoldPreOrder
	template <typename Data>
	void List<Data>::FoldPreOrder(FoldFunctor fun, const void *par, void *acc, Node *curr) const
	{
		for (; curr != nullptr; curr = curr->next)
		{
			fun(curr->info, par, acc);
		}
	}

	//Specific List FoldPostOrder
	template <typename Data>
	void List<Data>::FoldPostOrder(FoldFunctor fun, const void *par, void *acc, Node *curr) const
	{
		if (curr != nullptr)
		{
			FoldPostOrder(fun, par, acc, curr->next);
			fun(curr->info, par, acc);
		}
	}

	/* ************************************************************************** */

}
