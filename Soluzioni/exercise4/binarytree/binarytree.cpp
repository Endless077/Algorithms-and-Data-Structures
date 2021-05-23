#include <stdexcept>


namespace lasd {

/* ************************************************************************** */
/*                                  NODE                                      */
/* ************************************************************************** */

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node &compareNode) const noexcept {
    
    if (compareNode.Element() == this->Element()){ 
        bool thisDX = this->HasRightChild();
        bool thisSX = this->HasLeftChild(); 

        bool hisDX = compareNode.HasRightChild();
        bool hisSX = compareNode.HasLeftChild(); 

        bool right = (thisDX == hisDX);
        bool left = (thisSX == hisSX); 

        if( left && right ){ 
            if (thisSX && thisDX){
                return ((compareNode.LeftChild() == LeftChild()) && (compareNode.RightChild() == RightChild()));
            } 
            else if (thisSX){
                return (compareNode.LeftChild() == LeftChild());
            }else if (thisDX){
                return (compareNode.RightChild() == RightChild());
            }else{
                return true;
            }
        }
  }
  return false;
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node &compareNode) const noexcept {
    return !(*this == compareNode);
}

/* ************************************************************************** */
/*                              Binary Tree                                   */
/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data> &compareBT) const noexcept {
    if(size == compareBT.size){
        if(size != 0)
            return Root() == compareBT.Root();
        else
            return true;
    }else{
        return false;
    }
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data> &compareBT) const noexcept {
    return !(*this == compareBT);
}

/* ************************************************************************** */
/*                              Specific Function                             */
/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)
template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor function, void* parametro) {
    if(size!=0)
        MapPreOrder(function, parametro, &(Root()));
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor function, void* parametro) {
    if(size!=0)
        MapPostOrder(function, parametro, &(Root()));
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor function, const void* parametro, void* accumulatore) const {
    if(size!=0)
        FoldPreOrder(function, parametro, accumulatore, &(Root()));
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor function, const void* parametro, void* accumulatore) const {
    if(size!=0)
        FoldPostOrder(function, parametro, accumulatore, &(Root()));
}

/* ************************************************************************ */

// Specific member functions (inherited from InOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor function, void* parametro) {
    if(size!=0)
        MapInOrder(function, parametro, &(Root()));
}

template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor function, const void* parametro, void* accumulatore) const {
    if(size!=0)
        FoldInOrder(function, parametro, accumulatore, &(Root()));
}

/* ************************************************************************ */

// Specific member functions (inherited from BreadthMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor function, void* parametro) {
    if(size!=0)
        MapBreadth(function, parametro, &(Root()));
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor function, const void* parametro, void* accumulatore) const {
    if(size!=0)
        FoldBreadth(function, parametro, accumulatore, &(Root()));
}

/* ************************************************************************** */
/*                                  AUX Function                              */
/* ************************************************************************** */

// Auxiliary member functions (for MappableContainer)
template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor fun, void* par, Node* node) {
    if(node != nullptr){
        fun(node->Element(), par);

        if(node->HasLeftChild())
            MapPreOrder(fun, par, &(node->LeftChild()));

        if(node->HasRightChild())
            MapPreOrder(fun, par, &(node->RightChild()));
    }
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor fun, void* par, Node* node) {
    if(node != nullptr){
        if(node->HasLeftChild())
            MapPostOrder(fun, par, &(node->LeftChild()));
        
        if(node->HasRightChild())
            MapPostOrder(fun, par, &(node->RightChild()));
        
        fun(node->Element(), par);
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for FoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
    if(node != nullptr){
        fun(node->Element(), par, acc);

        if(node->HasLeftChild())
            FoldPreOrder(fun, par, acc, &(node->LeftChild()));

        if(node->HasRightChild())
            FoldPreOrder(fun, par, acc, &(node->RightChild()));
    }
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
    if(node != nullptr){
        if(node->HasLeftChild())
            FoldPostOrder(fun, par, acc, &(node->LeftChild()));

        if(node->HasRightChild())
            FoldPostOrder(fun, par, acc, &(node->RightChild()));

        fun(node->Element(), par, acc);
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for InOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor fun, void* par, Node* node) {
    if(node != nullptr){
        if(node->HasLeftChild())
            MapInOrder(fun, par, &(node->LeftChild()));

        fun(node->Element(), par);

        if(node->HasRightChild())
            MapInOrder(fun, par, &(node->RightChild()));
    }
}

template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor fun, const void* par, void* acc, Node* node) const {
    if(node != nullptr){
        if(node->HasLeftChild())
            FoldInOrder(fun, par, acc, &(node->LeftChild()));

        fun(node->Element(), par, acc);

        if(node->HasRightChild())
            FoldInOrder(fun, par, acc, &(node->RightChild()));
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for BreadthMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor fun, void* par, Node* node) {
    lasd::QueueLst<Node*> coda;
    coda.Enqueue(node);
    Node* tmp;

    while(!(coda.Empty())){
        tmp = coda.HeadNDequeue();
        fun(tmp->Element(),par);
        
        if(tmp->HasLeftChild())
            coda.Enqueue(&(tmp->LeftChild()));
        
        if(tmp->HasRightChild())
            coda.Enqueue(&(tmp->RightChild()));
  }
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor fun, const void* par, void* acc, Node* node) const {
    lasd::QueueLst<const Node*> coda;
    coda.Enqueue(node);
    const Node* tmp;

    while(!(coda.Empty())){
        tmp = coda.HeadNDequeue();
        fun(tmp->Element(),par,acc);
        
        if(tmp->HasLeftChild())
            coda.Enqueue(&(tmp->LeftChild()));
        
        if(tmp->HasRightChild())
            coda.Enqueue(&(tmp->RightChild()));
  }
}

/* ************************************************************************** */





/* ************************************************************************** */





/* ************************************************************************** */
/*                              Iterator PreOrder                             */
/* ************************************************************************** */

// Specific constructors
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &bt) {
    current = &bt.Root();
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data> &iter) {
    current = iter.current;
    stk = iter.stk;
}

// Move constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data> &&iter) noexcept {
    std::swap(current,iter.current);
    stk = std::move(iter.stk);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BTPreOrderIterator<Data>::~BTPreOrderIterator() {
    stk.Clear();
    delete current;
    current = nullptr;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> &iter) {
    BTPreOrderIterator<Data> *tmp = new BTPreOrderIterator<Data>(iter);
    std::swap(*tmp, *this);
    delete (tmp);
    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> &&iter) noexcept {
    std::swap(current, iter.current);
    stk = std::move(iter.stk);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> &iter) const noexcept {
    if(current!=iter.current)
        return false;
    
    if(stk!=iter.stk)
        return false;
    
    return true;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> &iter) const noexcept {
    return !(*this==iter);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Terminated");
        
    return current->Element();
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ************************************************************************ */

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    
    if(Terminated())
        throw std::out_of_range("Iterator PreOrder terminated.");

    if(current->HasRightChild())
        stk.Push(&(current->RightChild()));
    
    if(current->HasLeftChild())
        stk.Push(&(current->LeftChild()));

    if(stk.Empty())
        current = nullptr;
    else
        current = stk.TopNPop(); 
    
    return (*this);
}

/* ************************************************************************ */



/* ************************************************************************** */
/*                              Iterator InOrder                              */
/* ************************************************************************** */

//Function GetMostLeftNode
template <typename Data>
void BTInOrderIterator<Data>::getMostLeftNode() {
    while (current->HasLeftChild()) {
        stk.Push(current);
        current = &(current->LeftChild());
    }
}

/* ************************************************************************** */

// Specific constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &bt) {
    current = &bt.Root();
    getMostLeftNode();
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data> &iter) {
    current = iter.current;
    stk = iter.stk;
}

// Move constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> &&iter) noexcept {
    std::swap(current,iter.current);
    stk = std::move(iter.stk);
}
/* ************************************************************************ */

// Destructor
template <typename Data>
BTInOrderIterator<Data>::~BTInOrderIterator() {
    stk.Clear();
    delete current;
    current = nullptr;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> &iter) {
    BTInOrderIterator<Data> *tmp = new BTInOrderIterator<Data>(iter);
    std::swap(*tmp, *this);
    delete (tmp);
    return *this;
}

// Move assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> &&iter) noexcept {
    std::swap(current, iter.current);
    stk = std::move(iter.stk);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> &iter) const noexcept {
    if(current!=iter.current)
        return false;
    
    if(stk!=iter.stk)
        return false;
    
    return true;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data> &iter) const noexcept {
    return !(*this==iter);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Terminated");

    return current->Element();
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ************************************************************************ */

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Iterator InOrder terminated.");
        
    if(current->HasRightChild()){
        current = &(current->RightChild());
        getMostLeftNode();
    }else{
        if(stk.Empty())
            current = nullptr;
        else
            current = stk.TopNPop(); 
    }
    return (*this);
}

/* ************************************************************************ */



/* ************************************************************************** */
/*                              Iterator PostOrder                            */
/* ************************************************************************** */

//Function GetMostLeftLeaf
template <typename Data>
void BTPostOrderIterator<Data>::getMostLeftLeaf() {
    while (current->HasLeftChild()) {
        stk.Push(current);
        current = &(current->LeftChild());
    }

    if(current->HasRightChild()) {
        stk.Push(current);
        current = &(current->RightChild());
        getMostLeftLeaf();
    }
}

/* ************************************************************************** */

// Specific constructors
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> &bt) {
    current = &bt.Root();
    getMostLeftLeaf();
    last = current;
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data> &iter) {
    current = iter.current;
    last = iter.last;
    stk = iter.stk;
}

// Move constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data> &&iter) noexcept {
    std::swap(current,iter.current);
    std::swap(last,iter.last);
    stk = std::move(iter.stk);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BTPostOrderIterator<Data>::~BTPostOrderIterator() {
    stk.Clear();
    delete current;
    delete last;
    current = nullptr;
    last = nullptr;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> &iter) {
    BTPostOrderIterator<Data> *tmp = new BTPostOrderIterator<Data>(iter);
    std::swap(*tmp, *this);
    delete (tmp);
    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> &&iter) noexcept {
    std::swap(current, iter.current);
    std::swap(last,iter.last);
    stk = std::move(iter.stk);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> &iter) const noexcept {
    if(current!=iter.current)
        return false;

    if(last!=iter.last)
        return false;
    
    if(stk!=iter.stk)
        return false;
    
    return true;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> &iter) const noexcept {
    return !(*this==iter);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Terminated");

    return current->Element();
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ************************************************************************ */

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    if(Terminated())
        throw std::out_of_range("Iterator PostOrder terminated.");

    if(stk.Empty()){
        current = nullptr;
        last = nullptr;
    }else{
        current = stk.TopNPop();
        if(current->HasRightChild() && !(&(current->RightChild())==last)){
            stk.Push(current);
            current = &(current->RightChild());
            getMostLeftLeaf();
        }
    }
    last = current;
    return (*this);
}

/* ************************************************************************** */
/*                              Iterator Breadth                              */
/* ************************************************************************** */

// Specific constructors
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> &bt) {
    current = &bt.Root();
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data> &iter) {
    current = iter.current;
    que = iter.que;
}

// Move constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data> &&iter) noexcept {
    std::swap(current,iter.current);
    que = std::move(iter.que);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BTBreadthIterator<Data>::~BTBreadthIterator() {
    que.Clear();
    delete current;
    current = nullptr;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data> &iter) {
    BTBreadthIterator<Data> *tmp = new BTBreadthIterator<Data>(iter);
    std::swap(*tmp, *this);
    delete (tmp);
    return *this;
}

// Move assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> &&iter) noexcept {
    std::swap(current, iter.current);
    que = std::move(iter.que);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data> &iter) const noexcept {
    if(current!=iter.current)
        return false;
    
    if(que!=iter.que)
        return false;
    
    return true;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data> &iter) const noexcept {
    return !(*this==iter);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
    if(Terminated())
        throw std::out_of_range("Terminated");

    return current->Element();
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

/* ************************************************************************ */

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    
    if(Terminated())
        throw std::out_of_range("Iterator Ampiezza terminated.");
    
    if(current->HasLeftChild())
        que.Enqueue(&(current->LeftChild()));
    
    if(current->HasRightChild())
        que.Enqueue(&(current->RightChild()));
    
    if(que.Empty())
        current = nullptr;
    else
        current = que.HeadNDequeue();

    return (*this);

}

/* ************************************************************************ */

}
