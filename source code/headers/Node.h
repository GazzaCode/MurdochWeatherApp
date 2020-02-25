#ifndef NODE_H
#define NODE_H

    /**
    * @class Node
    * @brief  Represents a node to be used with a BST data structure. The BST managers
    * nodes, nodes do not manage themselves. Nodes will make up the structure of the BST
    * via left and right child pointers.
    *
    * @author Gareth Griffiths
    * @version 03
    * @date 09/05/2019
    *
    * @todo nill.
    *
    * @bug nill.
    */

template<class T>
class Node
{
    public:
        template<typename> friend class BST;

    private:
            ///The data to be stored in the node
        T data;

            ///Pointer to the left child
        Node* left;

            ///Pointer to the right child
        Node* right;

           /**
            * @brief  Constructor to assign data and set left and right pointer to nullptr
            */
        Node(const T &iData): data(iData), left(nullptr), right(nullptr) {};

            /**
            * @brief  Copy constructor to duplicate a Node.
            */
        Node(const Node<T> &node): data(node.getData()), left(node.getLeft()), right(node.getRight()) {};

            /**
            * @brief  Getter for the data in the node.
            * @return T& - the object being stored in the node.
            */
        T& getData() ;

            /**
            * @brief  Getter for the left child pointer.
            * @return Node* - pointer the left child.
            */
        Node* getLeft() const;

            /**
            * @brief  Getter for the right child pointer.
            * @return Node* - pointer the right child.
            */
        Node* getRight() const;

            /**
            * @brief  Setter for the data or object being stored in the node.
            * @param T &iData - the data or object being inputted.
            * @return nill.
            */
        void setData(T &iData);

            /**
            * @brief  Setter for the right child pointer. Used to tell the node which right node
            * to point to.
            * @param Node* iRight - Pointer that points to the specified right node.
            * @return nill.
            */
        void setRight(Node* iRight);

            /**
            * @brief  Setter for the left child pointer. Used to tell the node which left node
            * to point to.
            * @param Node* iLeft - Pointer that points to the specified left node.
            * @return nill.
            */
        void setLeft(Node* iLeft);
};

template<class T>
T& Node<T>::getData()
{
    return data;
}

template<class T>
void Node<T>::setData(T &iData)
{
    data = iData;
}

template<class T>
Node<T>* Node<T>::getLeft() const
{
    return left;
}

template<class T>
void Node<T>::setLeft(Node* iLeft)
{
    left = iLeft;
}

template<class T>
Node<T>* Node<T>::getRight() const
{
    return right;
}

template<class T>
void Node<T>::setRight(Node* iRight)
{
    right = iRight;
}

#endif
