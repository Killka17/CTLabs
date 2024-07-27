#pragma once

#include <iterator>
#include <stdexcept>
#include <utility>

template< typename T >
class NodeStack
{
  private:
	T value_{};
	NodeStack* previous_{ nullptr };

  public:
	explicit NodeStack(const T& value);
	T getValue();
	NodeStack* getPrevious() noexcept;
	NodeStack* setPrevious(NodeStack* prev) noexcept;
};

template< typename T >
NodeStack< T >::NodeStack(const T& value) : value_(value)
{
}

template< typename T >
T NodeStack< T >::getValue()
{
	return value_;
}

template< typename T >
NodeStack< T >* NodeStack< T >::getPrevious() noexcept
{
	return previous_;
}

template< typename T >
NodeStack< T >* NodeStack< T >::setPrevious(NodeStack* prev) noexcept
{
	previous_ = prev;
	return previous_;
}

template< typename T >
class Stack
{
  private:
	using size_type = std::size_t;
	NodeStack< T >* current_{ nullptr };
	size_type size_{ 0 };

  public:
	void add(const T& value);
	void pop();
	T top();
	[[nodiscard]] bool empty() const noexcept;
	[[nodiscard]] size_type size() const noexcept;
	~Stack();
};

template< typename T >
void Stack< T >::add(const T& value)
{
	auto* next = new NodeStack< T >(value);
	if (size_ > 0)
		next->setPrevious(current_);

	current_ = next;
	++size_;
}

template< typename T >
void Stack< T >::pop()
{
	if (current_ != nullptr)
	{
		auto* temp = current_;
		current_ = current_->getPrevious();
		delete temp;
		--size_;
	}
}

template< typename T >
T Stack< T >::top()
{
	if (current_ == nullptr)
		throw std::runtime_error("Stack is empty");
	return current_->getValue();
}

template< typename T >
bool Stack< T >::empty() const noexcept
{
	return size_ == 0;
}

template< typename T >
typename Stack< T >::size_type Stack< T >::size() const noexcept
{
	return size_;
}

template< typename T >
Stack< T >::~Stack()
{
	while (current_)
		pop();
}

template< typename T >
struct Element
{
  private:
	T* value_{ nullptr };
	bool is_active_{ false };
	std::size_t index_{};
	Element* next_{ nullptr };
	Element* previous_{ nullptr };

  public:
	void clear() noexcept;
	[[nodiscard]] bool isActive() const noexcept;
	[[nodiscard]] std::size_t getIndex() const noexcept;
	T* getValue() const noexcept;
	Element* getNext() const noexcept;
	Element* getPrevious() const noexcept;

	void setIsActive(bool is_active) noexcept;
	void setIndex(std::size_t new_index) noexcept;
	void setValue(T* value) noexcept;
	void setNext(Element* next) noexcept;
	void setPrevious(Element* previous) noexcept;

	explicit Element() noexcept = default;
	Element(Element&& other) noexcept;
	Element& operator=(Element&& other) noexcept;
	Element(const Element& other);
	Element& operator=(const Element& other);
	void swap(Element& other) noexcept;
};

template< typename T >
void Element< T >::swap(Element& other) noexcept
{
	std::swap(value_, other.value_);
	std::swap(index_, other.index_);
	std::swap(next_, other.next_);
	std::swap(previous_, other.previous_);
}

template< typename T >
void Element< T >::clear() noexcept
{
	if (is_active_)
		delete value_;
	value_ = nullptr;
	next_ = nullptr;
	previous_ = nullptr;
}

template< typename T >
bool Element< T >::isActive() const noexcept
{
	return is_active_;
}

template< typename T >
std::size_t Element< T >::getIndex() const noexcept
{
	return index_;
}

template< typename T >
T* Element< T >::getValue() const noexcept
{
	return value_;
}

template< typename T >
Element< T >* Element< T >::getNext() const noexcept
{
	return next_;
}

template< typename T >
Element< T >* Element< T >::getPrevious() const noexcept
{
	return previous_;
}

template< typename T >
void Element< T >::setIsActive(bool is_active) noexcept
{
	is_active_ = is_active;
}

template< typename T >
void Element< T >::setIndex(std::size_t new_index) noexcept
{
	index_ = new_index;
}

template< typename T >
void Element< T >::setValue(T* value) noexcept
{
	value_ = value;
}

template< typename T >
void Element< T >::setNext(Element* next) noexcept
{
	next_ = next;
}

template< typename T >
void Element< T >::setPrevious(Element* previous) noexcept
{
	previous_ = previous;
}

template< typename T >
Element< T >::Element(Element&& other) noexcept :
	value_(other.value_), index_(other.index_), next_(other.next_), previous_(other.previous_)
{
	other.value_ = nullptr;
	other.next_ = nullptr;
	other.previous_ = nullptr;
}

template< typename T >
Element< T >& Element< T >::operator=(Element&& other) noexcept
{
	if (this != &other)
	{
		clear();
		swap(other);
	}
	return *this;
}

template< typename T >
Element< T >::Element(const Element& other) :
	index_(other.index_), next_(other.next_), value_(new T(*other.value_)), previous_(other.previous_)
{
}

template< typename T >
Element< T >& Element< T >::operator=(const Element& other)
{
	if (this != &other && other.is_active_)
	{
		Element< T > copy(other);
		swap(copy);
	}
	return *this;
}

template< typename T >
struct DeletedCell
{
  private:
	using element_type = Element< T >*;
	element_type left_{ nullptr };
	element_type position_{ nullptr };
	element_type right_{ nullptr };

  public:
	explicit DeletedCell(element_type left_, element_type position_, element_type right_);
	DeletedCell(DeletedCell&& other) noexcept;
	DeletedCell& operator=(DeletedCell&& other) noexcept;
	DeletedCell(const DeletedCell& other);
	DeletedCell& operator=(const DeletedCell& other);

	void swap(DeletedCell& other) noexcept;

	element_type getLeft() const noexcept;
	element_type getPosition() const noexcept;
	element_type getRight() const noexcept;

	void setLeft(element_type new_left) noexcept;
	void setPosition(element_type new_position) noexcept;
	void setRight(element_type new_right) noexcept;
};

template< typename T >
void DeletedCell< T >::swap(DeletedCell& other) noexcept
{
	std::swap(left_, other.left_);
	std::swap(right_, other.right_);
	std::swap(position_, other.position_);
}

template< typename T >
DeletedCell< T >::DeletedCell(element_type left_, element_type position_, element_type right_) :
	left_(left_), position_(position_), right_(right_)
{
}

template< typename T >
DeletedCell< T >::DeletedCell(DeletedCell&& other) noexcept :
	left_(other.left_), position_(other.position_), right_(other.right_)
{
	other.left_ = nullptr;
	other.position_ = nullptr;
	other.right_ = nullptr;
}

template< typename T >
DeletedCell< T >& DeletedCell< T >::operator=(DeletedCell&& other) noexcept
{
	if (this != &other)
	{
		swap(other);
	}
	return *this;
}

template< typename T >
DeletedCell< T >::DeletedCell(const DeletedCell& other) :
	left_(other.left_), position_(other.position_), right_(other.right_)
{
}

template< typename T >
DeletedCell< T >& DeletedCell< T >::operator=(const DeletedCell& other)
{
	if (this != &other)
	{
		DeletedCell< T > copy(other);
		swap(copy);
	}
	return *this;
}

template< typename T >
typename DeletedCell< T >::element_type DeletedCell< T >::getLeft() const noexcept
{
	return left_;
}

template< typename T >
typename DeletedCell< T >::element_type DeletedCell< T >::getPosition() const noexcept
{
	return position_;
}

template< typename T >
typename DeletedCell< T >::element_type DeletedCell< T >::getRight() const noexcept
{
	return right_;
}

template< typename T >
void DeletedCell< T >::setLeft(element_type new_left) noexcept
{
	left_ = new_left;
}

template< typename T >
void DeletedCell< T >::setPosition(element_type new_position) noexcept
{
	position_ = new_position;
}

template< typename T >
void DeletedCell< T >::setRight(element_type new_right) noexcept
{
	right_ = new_right;
}

template< typename T >
struct Block
{
  private:
	using size_type = std::size_t;
	Block* next_{ nullptr };
	Block* previous_{ nullptr };
	Element< T >* elements_{ nullptr };
	Stack< DeletedCell< T > > deleted_cells_{};
	size_type block_capacity_{ 0 };

  public:
	explicit Block() = default;
	~Block();
	Block(Block&& other) noexcept;
	Block& operator=(Block&& other) noexcept;
	Block(const Block& other);
	Block& operator=(const Block& other);
	void swap(Block& other) noexcept;

	Block* getNext() const noexcept;
	Block* getPrevious() const noexcept;
	Element< T >* getElements() const noexcept;
	Element< T >& getElement(size_type index) const noexcept;
	Stack< DeletedCell< T > >& getDeletedCells() noexcept;
	[[nodiscard]] size_type getBlockCapacity() const noexcept;

	void setNext(Block* new_next) noexcept;
	void setPrevious(Block* new_previous) noexcept;
	void setElements(Element< T >* new_elements) noexcept;
	void setBlockCapacity(size_type new_capacity) noexcept;
	void setDeletedCell(Stack< DeletedCell< T > > new_deleted_cell) noexcept;
};

template< typename T >
void Block< T >::swap(Block& other) noexcept
{
	std::swap(next_, other.next_);
	std::swap(previous_, other.previous_);
	std::swap(elements_, other.elements_);
	std::swap(deleted_cells_, other.deleted_cells_);
}

template< typename T >
Block< T >::~Block()
{
	elements_[0].clear();
	auto* element = &elements_[1];

	while (element && element->getIndex() != 0)
	{
		auto next_element = element->getNext();
		element->clear();
		element = next_element;
	}
	previous_ = nullptr;
	next_ = nullptr;
}

template< typename T >
Block< T >::Block(Block&& other) noexcept :
	next_(other.next_), previous_(other.previous_), elements_(other.elements_),
	deleted_cells_(std::move(other.deleted_cells_)), block_capacity_(other.block_capacity_)
{
	other.next_ = nullptr;
	other.previous_ = nullptr;
	other.elements_ = nullptr;
}

template< typename T >
Block< T >& Block< T >::operator=(Block&& other) noexcept
{
	if (this != &other)
		swap(other);

	return *this;
}

template< typename T >
Block< T >::Block(const Block& other) :
	next_(other.next_), previous_(other.previous_), deleted_cells_(other.deleted_cells_)
{
	elements_ = new Element< T >[other.block_capacity_];
	for (size_type i = 0; i < other.block_capacity_; ++i)
	{
		elements_[i] = other.elements_[i];
	}
}

template< typename T >
Block< T >& Block< T >::operator=(const Block& other)
{
	if (this != &other)
	{
		Block< T > copy(other);
		swap(copy);
	}
	return *this;
}

template< typename T >
Block< T >* Block< T >::getNext() const noexcept
{
	return next_;
}

template< typename T >
Block< T >* Block< T >::getPrevious() const noexcept
{
	return previous_;
}

template< typename T >
Element< T >* Block< T >::getElements() const noexcept
{
	return elements_;
}

template< typename T >
Element< T >& Block< T >::getElement(size_type index) const noexcept
{
	return elements_[index];
}

template< typename T >
Stack< DeletedCell< T > >& Block< T >::getDeletedCells() noexcept
{
	return deleted_cells_;
}

template< typename T >
typename Block< T >::size_type Block< T >::getBlockCapacity() const noexcept
{
	return block_capacity_;
}

template< typename T >
void Block< T >::setNext(Block* new_next) noexcept
{
	next_ = new_next;
}

template< typename T >
void Block< T >::setPrevious(Block* new_previous) noexcept
{
	previous_ = new_previous;
}

template< typename T >
void Block< T >::setElements(Element< T >* new_elements) noexcept
{
	elements_ = new_elements;
}

template< typename T >
void Block< T >::setBlockCapacity(size_type new_capacity) noexcept
{
	block_capacity_ = new_capacity;
}

template< typename T >
void Block< T >::setDeletedCell(Stack< DeletedCell< T > > new_deleted_cell) noexcept
{
	deleted_cells_ = new_deleted_cell;
}

template< bool Flag, typename U, typename V >
using conditional_t = typename std::conditional< Flag, U, V >::type;

template< typename T >
class BucketStorage
{
  public:
	using value_type = T;
	using size_type = std::size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;

	template< bool IsConst >
	class Iterator
	{
	  private:
		using element_type_ = Element< T >;
		using end_pointer_type = conditional_t< IsConst, element_type_ const * const *, element_type_** >;

		element_type_* current_node_{ nullptr };
		end_pointer_type end_{ nullptr };
		Block< T >* current_block_;
		size_type block_capacity_;
		size_type current_position_{ 0 };

	  public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = conditional_t< IsConst, const value_type*, value_type* >;
		using reference = conditional_t< IsConst, const value_type&, value_type& >;
		using iterator_category = std::bidirectional_iterator_tag;

		explicit Iterator(element_type_* current_node, end_pointer_type end, Block< T >* current_block, size_type block_capacity);
		explicit Iterator(element_type_* current_node, end_pointer_type end, Block< T >* current_block, size_type block_capacity, size_type current_position);
		Iterator(const Iterator& other);

		element_type_* getCurrent() const;
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

		template< bool OtherIsConst >
		bool operator==(const Iterator< OtherIsConst >& other) const;

		template< bool OtherIsConst >
		bool operator!=(const Iterator< OtherIsConst >& other) const;

		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);

		bool operator<(const Iterator& other) const;
		bool operator>(const Iterator& other) const;
		bool operator<=(const Iterator& other) const;
		bool operator>=(const Iterator& other) const;

		reference operator*() const;
		pointer operator->() const;

		Block< T >* getCurrentBlock();
		element_type_* getCurrentElement();
	};

	template< bool IsConst >
	using iterator_type = Iterator< IsConst >;

	using iterator = iterator_type< false >;
	using const_iterator = iterator_type< true >;

	using difference_type = typename iterator::difference_type;

  private:
	using element_type = Element< T >;
	using block_type = Block< T >;
	Stack< block_type* > last_deleting_;
	block_type* head_block_{ nullptr };
	block_type* tail_block_{ nullptr };
	element_type* last_object_{ nullptr };
	element_type* first_element_{ nullptr };
	size_type size_{ 0 };
	size_type block_capacity_{ 0 };
	size_type current_index_{ 0 };

	void addBlock();
	void delBlock(block_type* block);
	element_type* insertInDeletedCellBody();
	iterator insertInDeletedCell(const value_type& value);
	iterator insertInDeletedCell(value_type&& value);
	void insertBody();
	void initializationContainer();

  public:
	iterator begin() noexcept;
	iterator end() noexcept;

	const_iterator begin() const noexcept;
	const_iterator end() const noexcept;

	const_iterator cbegin() const noexcept;
	const_iterator cend() const noexcept;

	explicit BucketStorage(size_type block_capacity = 64);
	BucketStorage(const BucketStorage& other);
	BucketStorage(BucketStorage&& other) noexcept;
	BucketStorage& operator=(const BucketStorage& other);
	BucketStorage& operator=(BucketStorage&& other) noexcept;

	iterator insert(const value_type& value);
	iterator insert(value_type&& value);
	iterator erase(iterator pos);

	iterator get_to_distance(iterator iter, const difference_type distance);

	[[nodiscard]] size_type size() const noexcept;
	[[nodiscard]] bool empty() const noexcept;
	[[nodiscard]] size_type capacity() const noexcept;

	void clear() noexcept;
	~BucketStorage();
	void shrink_to_fit();
	void swap(BucketStorage& other) noexcept;
};

template< typename T >
template< bool IsConst >
BucketStorage< T >::Iterator< IsConst >::Iterator(element_type_* current_node, end_pointer_type end, Block< T >* current_block, size_type block_capacity) :
	current_node_(current_node), end_(end), current_block_(current_block), block_capacity_(block_capacity)
{
}

template< typename T >
template< bool IsConst >
BucketStorage< T >::Iterator< IsConst >::Iterator(element_type_* current_node, end_pointer_type end, Block< T >* current_block, size_type block_capacity, size_type current_position) :
	current_node_(current_node), end_(end), current_block_(current_block), block_capacity_(block_capacity),
	current_position_(current_position)
{
}

template< typename T >
template< bool IsConst >
BucketStorage< T >::Iterator< IsConst >::Iterator(const Iterator& other) :
	current_node_(other.current_node_), current_block_(other.current_block_), block_capacity_(other.block_capacity_),
	current_position_(other.current_position_), end_(other.end_)
{
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::template Iterator< IsConst >::element_type_* BucketStorage< T >::Iterator< IsConst >::getCurrent() const
{
	if (current_node_ == nullptr)
		return ((element_type_*)(*end_)) + 1;

	return current_node_;
}

template< typename T >
template< bool IsConst >
bool BucketStorage< T >::Iterator< IsConst >::operator==(const Iterator& other) const
{
	return getCurrent() == other.getCurrent();
}

template< typename T >
template< bool IsConst >
bool BucketStorage< T >::Iterator< IsConst >::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

template< typename T >
template< bool IsConst >
template< bool OtherIsConst >
bool BucketStorage< T >::Iterator< IsConst >::operator==(const Iterator< OtherIsConst >& other) const
{
	return getCurrent() == other.getCurrent();
}

template< typename T >
template< bool IsConst >
template< bool OtherIsConst >
bool BucketStorage< T >::Iterator< IsConst >::operator!=(const Iterator< OtherIsConst >& other) const
{
	return !(*this == other);
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::template Iterator< IsConst >& BucketStorage< T >::Iterator< IsConst >::operator++()
{
	if (current_node_ == nullptr)
	{
		auto* temp = (element_type_*)(*end_);
		current_node_ = temp;
		return *this;
	}

	if (!current_node_->getNext())
		current_node_ = current_node_ + 1;
	else
	{
		current_node_ = current_node_->getNext();
		while (current_node_->getNext() && !current_node_->isActive())
			current_node_ = current_node_->getNext();

		current_block_ = current_node_->getIndex() == 0 ? current_block_->getNext() : current_block_;
	}

	current_position_++;

	return *this;
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::template Iterator< IsConst > BucketStorage< T >::Iterator< IsConst >::operator++(int)
{
	Iterator temp = *this;
	++(*this);
	return temp;
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::template Iterator< IsConst >& BucketStorage< T >::Iterator< IsConst >::operator--()
{
	if (current_node_ == nullptr)
	{
		current_node_ = *end_;
		return *this;
	}

	if (!current_node_->getPrevious())
		current_node_ = current_node_ + 1;
	else
	{
		current_node_ = current_node_->getPrevious();
		current_block_ = current_node_->getNext()->getIndex() == 0 ? current_block_->getPrevious() : current_block_;
	}

	current_position_--;

	return *this;
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::template Iterator< IsConst > BucketStorage< T >::Iterator< IsConst >::operator--(int)
{
	Iterator temp = *this;
	--(*this);
	return temp;
}

template< typename T >
template< bool IsConst >
bool BucketStorage< T >::Iterator< IsConst >::operator<(const Iterator& other) const
{
	return current_position_ < other.current_position_;
}

template< typename T >
template< bool IsConst >
bool BucketStorage< T >::Iterator< IsConst >::operator>(const Iterator& other) const
{
	return current_position_ > other.current_position_;
}

template< typename T >
template< bool IsConst >
bool BucketStorage< T >::Iterator< IsConst >::operator<=(const Iterator& other) const
{
	return current_position_ <= other.current_position_;
}

template< typename T >
template< bool IsConst >
bool BucketStorage< T >::Iterator< IsConst >::operator>=(const Iterator& other) const
{
	return current_position_ >= other.current_position_;
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::template Iterator< IsConst >::reference BucketStorage< T >::Iterator< IsConst >::operator*() const
{
	return *current_node_->getValue();
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::template Iterator< IsConst >::pointer BucketStorage< T >::Iterator< IsConst >::operator->() const
{
	return &*current_node_->getValue();
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::block_type* BucketStorage< T >::Iterator< IsConst >::getCurrentBlock()
{
	return current_block_;
}

template< typename T >
template< bool IsConst >
typename BucketStorage< T >::template Iterator< IsConst >::element_type_*
	BucketStorage< T >::Iterator< IsConst >::getCurrentElement()
{
	return current_node_;
}

template< typename T >
void BucketStorage< T >::addBlock()
{
	auto* new_block = new block_type();
	new_block->setBlockCapacity(block_capacity_);
	new_block->setElements(new element_type[block_capacity_]);
	new_block->getElement(0).setPrevious(last_object_);
	last_object_->setNext(&new_block->getElement(0));
	new_block->setPrevious(tail_block_);
	tail_block_->setNext(new_block);
	tail_block_ = new_block;
}

template< typename T >
void BucketStorage< T >::delBlock(block_type* block)
{
	if (!block->getPrevious() && !block->getNext())
	{
		clear();
		initializationContainer();
		return;
	}

	if (block->getPrevious() && block->getNext())
	{
		block->getPrevious()->setNext(block->getNext());
		block->getNext()->setPrevious(block->getPrevious());

		block->getPrevious()->getElement(block_capacity_ - size_type(1)).setNext(&block->getNext()->getElement(0));
		block->getNext()->getElement(0).setPrevious(&block->getPrevious()->getElement(block_capacity_ - size_type(1)));
	}
	else if (block->getPrevious() && !block->getNext())
	{
		block->getPrevious()->setNext(nullptr);
		block->getPrevious()->getElement(block_capacity_ - size_type(1)).setNext(nullptr);
		last_object_ = &block->getPrevious()->getElement(block_capacity_ - size_type(1));
	}
	else if (!block->getPrevious() && block->getNext())
	{
		head_block_ = block->getNext();
		block->getNext()->setPrevious(nullptr);
		block->getNext()->getElement(0).setPrevious(nullptr);
		first_element_ = &block->getNext()->getElement(0);
	}

	Stack< block_type* > new_last_deleting;
	while (!last_deleting_.empty())
	{
		auto* link = last_deleting_.top();
		last_deleting_.pop();
		if (link != block)
			new_last_deleting.add(link);
	}

	last_deleting_ = new_last_deleting;
	current_index_ -= block_capacity_;

	delete block;
}

template< typename T >
typename BucketStorage< T >::element_type* BucketStorage< T >::insertInDeletedCellBody()
{
	auto* top_block = last_deleting_.top();
	last_deleting_.pop();

	auto top_deleted_element = top_block->getDeletedCells().top();
	top_block->getDeletedCells().pop();

	top_deleted_element.getLeft()->setNext(top_deleted_element.getPosition());
	top_deleted_element.getRight()->setPrevious(top_deleted_element.getPosition());

	top_deleted_element.getPosition()->setPrevious(top_deleted_element.getLeft());
	top_deleted_element.getPosition()->setNext(top_deleted_element.getLeft());

	return top_deleted_element.getPosition();
}

template< typename T >
typename BucketStorage< T >::iterator BucketStorage< T >::insertInDeletedCell(const value_type& value)
{
	element_type* position = insertInDeletedCellBody();

	position->setValue(new value_type(value));
	position->setIsActive(true);

	return iterator(position, &last_object_, head_block_, block_capacity_);
}

template< typename T >
typename BucketStorage< T >::iterator BucketStorage< T >::insertInDeletedCell(value_type&& value)
{
	element_type* position = insertInDeletedCellBody();

	position->setValue(new value_type(std::move(value)));
	position->setIsActive(true);

	return iterator(position, &last_object_, head_block_, block_capacity_);
}

template< typename T >
void BucketStorage< T >::insertBody()
{
	size_type current_block = current_index_ / block_capacity_;
	size_type inner_index = current_index_ % block_capacity_;

	if (current_block > 0 && inner_index == 0)
		addBlock();

	if (first_element_ == nullptr)
		first_element_ = &tail_block_->getElement(0);

	element_type* elements = tail_block_->getElements();

	elements[inner_index].setIndex(inner_index);
	last_object_ = &elements[inner_index];

	if ((inner_index + 1) % block_capacity_ != 0)
	{
		elements[inner_index].setNext(&elements[inner_index + 1]);
		elements[inner_index + 1].setPrevious(&elements[inner_index]);
	}

	current_index_++;
}

template< typename T >
void BucketStorage< T >::initializationContainer()
{
	head_block_ = new block_type();
	head_block_->setElements(new element_type[block_capacity_]);
	head_block_->setBlockCapacity(block_capacity_);
	tail_block_ = head_block_;
}

template< typename T >
typename BucketStorage< T >::iterator BucketStorage< T >::begin() noexcept
{
	return iterator(head_block_ ? first_element_ : nullptr, &last_object_, head_block_, block_capacity_);
}

template< typename T >
typename BucketStorage< T >::iterator BucketStorage< T >::end() noexcept
{
	return iterator(nullptr, &last_object_, tail_block_, block_capacity_, current_index_);
}

template< typename T >
typename BucketStorage< T >::const_iterator BucketStorage< T >::begin() const noexcept
{
	return const_iterator(head_block_ ? first_element_ : nullptr, &last_object_, head_block_, block_capacity_);
}

template< typename T >
typename BucketStorage< T >::const_iterator BucketStorage< T >::end() const noexcept
{
	return const_iterator(nullptr, &last_object_, tail_block_, block_capacity_, current_index_);
}

template< typename T >
typename BucketStorage< T >::const_iterator BucketStorage< T >::cbegin() const noexcept
{
	return const_iterator(head_block_ ? first_element_ : nullptr, &last_object_, head_block_, block_capacity_);
}

template< typename T >
typename BucketStorage< T >::const_iterator BucketStorage< T >::cend() const noexcept
{
	return const_iterator(nullptr, &last_object_, tail_block_, block_capacity_, current_index_);
}

template< typename T >
BucketStorage< T >::BucketStorage(size_type block_capacity) : block_capacity_(block_capacity)
{
	if (block_capacity == 0)
		throw std::invalid_argument("The block size cannot be equal to 0.");

	initializationContainer();
}

template< typename T >
BucketStorage< T >::BucketStorage(const BucketStorage& other) :
	size_(other.size_), block_capacity_(other.block_capacity_), current_index_(0)
{
	initializationContainer();

	if (!other.head_block_)
		return;

	const_iterator iter = other.begin();
	const_iterator end_ = other.end();

	while (iter != end_)
	{
		if (iter.getCurrentElement()->isActive() && iter.getCurrentElement()->getValue())
			insert(*iter.getCurrentElement()->getValue());
		++iter;
	}
}

template< typename T >
BucketStorage< T >::BucketStorage(BucketStorage&& other) noexcept :
	last_deleting_(std::move(other.last_deleting_)), head_block_(other.head_block_), tail_block_(other.tail_block_),
	last_object_(other.last_object_), first_element_(other.first_element_), size_(other.size_),
	block_capacity_(other.block_capacity_), current_index_(other.current_index_)
{
	other.head_block_ = nullptr;
	other.tail_block_ = nullptr;
	other.last_object_ = nullptr;
	other.first_element_ = nullptr;
	other.size_ = 0;
	other.block_capacity_ = 0;
	other.current_index_ = 0;
}

template< typename T >
BucketStorage< T >& BucketStorage< T >::operator=(const BucketStorage& other)
{
	if (this == &other)
		return *this;

	BucketStorage< T > copy(other);
	swap(copy);

	return *this;
}

template< typename T >
BucketStorage< T >& BucketStorage< T >::operator=(BucketStorage&& other) noexcept
{
	if (this != &other)
	{
		clear();
		initializationContainer();
		swap(other);
	}
	return *this;
}

template< typename T >
typename BucketStorage< T >::iterator BucketStorage< T >::insert(const value_type& value)
{
	if (!last_deleting_.empty())
		return insertInDeletedCell(value);

	size_type inner_index = current_index_ % block_capacity_;

	insertBody();

	Element< T >* elements = tail_block_->getElements();

	elements[inner_index].setValue(new value_type(value));
	elements[inner_index].setIsActive(true);

	size_++;

	return iterator(&elements[inner_index], &last_object_, head_block_, block_capacity_);
}

template< typename T >
typename BucketStorage< T >::iterator BucketStorage< T >::insert(value_type&& value)
{
	if (!last_deleting_.empty())
		return insertInDeletedCell(std::move(value));

	size_type inner_index = current_index_ % block_capacity_;

	insertBody();

	tail_block_->getElement(inner_index).setValue(new value_type(std::move(value)));
	tail_block_->getElement(inner_index).setIsActive(true);

	size_++;

	return iterator(&tail_block_->getElement(inner_index), &last_object_, head_block_, block_capacity_);
}

template< typename T >
typename BucketStorage< T >::iterator BucketStorage< T >::erase(iterator pos)
{
	auto* block = pos.getCurrentBlock();
	auto* current_element = pos.getCurrentElement();

	last_deleting_.add(block);
	block->getDeletedCells().add(DeletedCell(current_element->getPrevious(), current_element, current_element->getNext()));

	if (current_element != first_element_)
	{
		current_element->getPrevious()->setNext(current_element->getNext());
		if (current_element->getNext())
			current_element->getNext()->setPrevious(current_element->getPrevious());
	}
	else
	{
		first_element_ = current_element->getNext();
		first_element_->setPrevious(nullptr);
	}

	if (current_element->isActive())
		delete current_element->getValue();

	current_element->setValue(nullptr);
	current_element->setIsActive(false);
	size_--;
	++pos;

	if (block->getDeletedCells().size() == block_capacity_)
		delBlock(block);

	return pos;
}

template< typename T >
typename BucketStorage< T >::iterator BucketStorage< T >::get_to_distance(iterator iter, const difference_type distance)
{
	auto new_iter = iterator(iter);

	if (distance > 0)
		for (difference_type i = 0; i < distance; ++i)
			++new_iter;
	else
		for (difference_type i = distance; i < 0; ++i)
			--new_iter;

	return new_iter;
}

template< typename T >
typename BucketStorage< T >::size_type BucketStorage< T >::size() const noexcept
{
	return size_;
}

template< typename T >
bool BucketStorage< T >::empty() const noexcept
{
	return size_ == 0;
}

template< typename T >
typename BucketStorage< T >::size_type BucketStorage< T >::capacity() const noexcept
{
	return size_ ? block_capacity_ * ((current_index_ - 1) / block_capacity_ + 1) : 0;
}

template< typename T >
void BucketStorage< T >::clear() noexcept
{
	if (!head_block_ || size_ == 0)
		return;
	auto* temp = head_block_;

	while (temp != nullptr)
	{
		auto temp_next = temp->getNext();
		delete temp;
		temp = temp_next;
	}

	head_block_ = nullptr;
	tail_block_ = nullptr;
	last_object_ = nullptr;
	first_element_ = nullptr;
	size_ = 0;
}

template< typename T >
BucketStorage< T >::~BucketStorage()
{
	clear();
}

template< typename T >
void BucketStorage< T >::shrink_to_fit()
{
	BucketStorage< T > new_storage(block_capacity_);
	iterator iter = begin();
	iterator end_ = end();

	while (iter != end_)
	{
		if (iter.getCurrentElement()->isActive() && iter.getCurrentElement()->getValue())
			new_storage.insert(std::move(*iter.getCurrentElement()->getValue()));
		++iter;
	}

	swap(new_storage);
}

template< typename T >
void BucketStorage< T >::swap(BucketStorage& other) noexcept
{
	std::swap(head_block_, other.head_block_);
	std::swap(tail_block_, other.tail_block_);
	std::swap(last_object_, other.last_object_);
	std::swap(size_, other.size_);
	std::swap(block_capacity_, other.block_capacity_);
	std::swap(current_index_, other.current_index_);
	std::swap(first_element_, other.first_element_);
}
