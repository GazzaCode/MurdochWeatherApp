#ifndef BST_H
#define BST_H

#include "../headers/Node.h"

    /**
    * @class BST
    * @brief  Templated binary search tree with basic operation methods.
    *
    * @author Gareth Griffiths
    * @version 01
    * @date 09/05/2019
    *
    * @todo Add function pointers to all traversal routines.
    *
    * @bug No knowns bugs.
    */

template<class T>
class BST
{
    typedef void (*f1Typ)(const T&);
public:
        /**
        * @brief  Constructor to set the root pointer to nullptr
        */
    BST();

        /**
        * @brief Copy constructor to duplicate a BST
        * @param const BST<T> &bst - another BST to copy to this BST
        */
    BST(const BST<T> &bst);

        /**
        * @brief  Descructor that calls destroy_tree(), recursively deletes all
        * nodes in the tree.
        */
    ~BST();

        /**
        * @brief  Checks if data is not null and then calls the private insert method of the BST class.
        *@param const T &data - the data to be stored into the node.
        *@return void
        */
    void insert(const T &data);

        /**
        *@brief  Checks if data is not null and then calls the private search method of the BST class.
        *@param const T &data - the data to be searched for.
        *@return Bool - true if found, false if not found.
        */
    bool search(const T &data) const;

        /**
        *@brief  Gets node data where a node data = the data. Similar to search routine just returns the data
        * instead of bool.
        *@param const T &data - the data to be searched for.
        *@return const T& - reference to the data that has been found.
        */
    const T& get(const T &data) const;

        /**
        * @brief  Checks if the root is not null then calls the private remove method.
        *@param const T data - the data to be removed from the BST.
        *@return void
        */
    void remove(const T &data);

        /**
        *@brief  Checks if not null then calls the private findSmallest method.
        * findSmallest is used to removing nodes without destroying the structure of the BST.
        *@param nill.
        *@return void
        */
    T findSmallest() const;

        /**
        * @brief Calls private processNodePostOrder. Process (using function pointer) using pre order traversal.
        *@param nill.
        *@return void
        */
    void processNodePreOrder(f1Typ f1) const;

        /**
        * @brief  Calls private processNodePostOrder. Process (using function pointer) using in order traversal.
        *@param nill.
        *@return void
        */
    void processNodeInOrder(f1Typ f1) const;

        /**
        * @brief  Calls private processNodePostOrder. Process (using function pointer) using post order traversal.
        *@param nill.
        *@return void
        */
    void processNodePostOrder(f1Typ f1) const;

        /**
        *@brief  Assignment operator to assign one BST to another.
        *@param const BST<T> &other - the other BST to assign to this BST.
        *@return BST<T> = the new BST after assigning it with another BST.
        */
    BST<T> & operator=( const BST<T> &other );
private:

        /**
        * @brief  Creates a node with specified data.
        *@param const T &data - The data to be added to the node
        *@return Node<T>* - returns the created node.
        */
    Node<T>* CreateNode(const T &data) const;

        /**
        *@brief Insert method to correctly and recursively insert a node into the BST.
        *@param const T &data - the data to be stored into the node.
        *@param Node<T>* leaf - pointer to the node it is being stored to (left or right).
        *@return void
        */
    void insert(const T &data, Node<T> *leaf);

        /**
        * @brief  Search method, recursively goes through the BST
        * the same way as it is inserted to find return a specific node to client.
        *@param Node<T>* root - pointer to the node it is linked to (left or right).
        *@param const T &data - the data to be stored into the node.
        */
    Node<T>* search(Node<T>* root, const T &data) const; //Doesent want to work if root is const for some reason.
                                                         //Nothing in search is modifying the node, so should be valid.
                                                         //getting invalid conversion error.
    Node<T>* get(Node<T>* root, const T &data) const;
        /**
        * @brief  recursively deletes all nodes in the tree (bottom up).
        *@param const Node<T> *leaf - The next node to be removed.
        *@return void
        */
    void destroy_tree(Node<T> *leaf) const; //node cant be const as it is being modified (deleted)

        /**
        * @brief  Deletes a node with a specific value.
        *@param const Node<T> *root - The next node to be traversed to.
        *@param T data - the data to be searched for and removed.
        */
    void remove(Node<T>* root, const T &data); //have to modify the BST (delete), cant be const

        /**
        * @brief  Finds the smallest node in the BST using T overloaded operators. Used for removing
        * nodes from the BST.
        *@param Node<T>* ptr - the next node to traverse to.
        *@return T - the object to be returned to the client.
        */
    T findSmallest(Node<T>* ptr) const;

        /**
        * @brief  Method to realocate the root node and deletes the old root node.
        *@return nill
        */
    void removeRootMatch();

        /**
        * @brief  Method to remove a node where match = node. Does so safetly (does not effect structure of BST).
        *@param Node<T>* parent - pointer to the parent of the node to be removed.
        *@param Node<T>* match - pointer to the node to be removed.
        *@param bool left - 1 to traverse left, 0 to traverse right.
        *@return nill
        */
    void removeMatch(Node<T>* parent, Node<T>* match, bool left);

        /**
        * @brief Process (output the node) using pre order traversal.
        *@param Node<T>* root - pointer to the root to begin traversal.
        *@return void
        */
    void processNodePreOrder(f1Typ f1, Node<T>* root) const;

        /**
        * @brief Process (output the node) using in order traversal.
        *@param Node<T>* root - pointer to the root to begin traversal.
        *@return void
        */
    void processNodeInOrder(f1Typ f1, Node<T>* root) const;

        /**
        * @brief Process (output the node) using post order traversal.
        *@param Node<T>* root - pointer to the root to begin traversal.
        *@return void
        */
    void processNodePostOrder(f1Typ f1, Node<T>* root) const;

        /**
        *@brief Used with the copy constructor to recursively copy one BST to another.
        *@param Node<T>* other - point to the rootPtr you want to copy from
        *@return Node<T>* - this return value will be the root of the new BST
        */
    Node<T>* clone(Node<T>* other) const;

        /**
        *@brief Used within the BST to get the rootPtr.
        *@param nill.
        *@return Node<T>* - The root pointer of the BST
        */
    Node<T>* getRoot() const;

        ///The root pointer to the BST.
    Node<T>* rootPtr;
};

template<class T>
BST<T>::BST()
{
    rootPtr = nullptr;
}

template<class T>
BST<T>::~BST()
{
    destroy_tree(rootPtr);
}

template<class T>
BST<T>::BST(const BST<T> &bst)
{
    //call clone which takes the other bst's rootPtr.
    rootPtr = clone(bst.getRoot());
}

template<class T>
Node<T>* BST<T>::getRoot() const
{
    return rootPtr;
}

template<class T>
Node<T>* BST<T>::clone(Node<T>* other) const
{
  if(other != nullptr)
  {
      Node<T> *newnode = new Node<T>(other->getData()); //Create a new node
      newnode->setLeft(clone(other->getLeft())); //set the left child of other nodes left child
                                                 //this will recursively call all node to the left of the current node.
      newnode->setRight(clone(other->getRight())); //Do the same for the right node.

      return newnode; //Return th enew node.
  }
  return nullptr; //return nullptr if other tree is not a tree.
}

template<class T>
void BST<T>::destroy_tree(Node<T> *leaf) const
{
    if(leaf != nullptr)
    {
        destroy_tree(leaf->getLeft());
        destroy_tree(leaf->getRight());
        delete leaf;
    }
}

template<class T>
Node<T>* BST<T>::CreateNode(const T &data) const
{
    Node<T>* newNode = new Node<T>(data); //Create a new node with the inputted data

    //The following is not needed anymore as Node will be initialized with nullPtrs when the constructor is called.
    //newNode->setLeft(nullptr); //Sets the left child of the child node to null
    //newNode->setRight(nullptr); //Sets the right child of the child node to null

    return newNode;
}

template<class T>
void BST<T>::insert(const T &data)
{
    if(rootPtr!=nullptr)
        insert(data, rootPtr); //pass on data to be inserted and the rootPtr as a starting point
    else
    {
        rootPtr=CreateNode(data); //if the rootPtr doesent exist it will be create, starting the tree.
    }
}

template<class T>
void BST<T>::insert(const T &data, Node<T> *leaf)
{
    if(data < leaf->getData()) //is the data less that the current node data?
    {
        if(leaf->getLeft()!= nullptr) //then check if there is already a node.
            insert(data, leaf->getLeft()); //call insert again to proceed the recusion, it will go left and right until it is set
        else
        {
            leaf->setLeft(CreateNode(data)); //if the data to the left doesn't exist then create a node there with the data.
        }                                    //Next do the same for right.
    }
    else if(data > leaf->getData()) //A BIG INNEFICIANT ERROR WAS HERE!! no longer allowing duplicates. did >=.
    {                             //Because assignment one data is ordered and dates are duplicated, we do not want to enter 30 of the same date. so use > not >=.
        if(leaf->getRight()!= nullptr)
            insert(data, leaf->getRight());
        else
        {
            leaf->setRight(CreateNode(data));
        }
    }
}

template<class T>    //Cant make root const as it has to take rootPtr which cannot be const.
Node<T>* BST<T>::search(Node<T>* root, const T &data) const
{
    if(root != nullptr)
    {
        if(root->getData() == data)
        {
            return root; //process
        }
        if(data < root->getData())
        {
            return search(root->getLeft(), data); //traverse left
        }
        else
            return search(root->right, data); //traverse right
    }
    else
        return nullptr;
}

template<class T>
bool BST<T>::search(const T &data) const
{
    Node<T>* node = search(rootPtr, data); //This is a pointer to a node that is already on the heap
                                           //the node will be deleted when this BST object destructor is called.
                                           //no need to delete here.
    if(node != nullptr)
    {
        return true;
    }
    else
        return false;

}

template<class T>    //Cant make root const as it has to take rootPtr which cannot be const.
Node<T>* BST<T>::get(Node<T>* root, const T &data) const
{
    if(root != nullptr)
    {
        if(root->getData() == data)
        {
            return root; //process
        }
        if(data < root->getData())
        {
            return get(root->getLeft(), data); //traverse left
        }
        else
            return get(root->right, data); //traverse right
    }
    else
        return nullptr;
}

template<class T>
const T& BST<T>::get(const T &data) const
{
    Node<T>* node = get(rootPtr, data); //This is a pointer to a node that is already on the heap
                                           //the node will be deleted when this BST object destructor is called.
                                           //no need to delete here.
    if(node != nullptr)
    {
        return node->getData();
    }
    //No return statement. the BST should always be searched before get is used.

}

template<class T>
void BST<T>::processNodePreOrder(f1Typ f1) const
{
    processNodePreOrder(f1, rootPtr);
}

template<class T>
void BST<T>::processNodePreOrder(f1Typ f1, Node<T>* root) const
{
    if(root != nullptr)
    {
        f1(root->getData());

        if(root->getLeft() != nullptr) //Make sure left child is not null
        {
            processNodePreOrder(root->getLeft()); //Traverse left
        }

        if(root->getRight() != nullptr) //Make sure right child is not null
        {
            processNodePreOrder(root->getRight()); //Traverse right
        }
    }
}

template<class T>
void BST<T>::processNodeInOrder(f1Typ f1) const
{
    processNodeInOrder(f1, rootPtr);
}

template<class T>
void BST<T>::processNodeInOrder(f1Typ f1, Node<T>* root) const
{
    if(root != nullptr)
    {

        if(root->getLeft() != nullptr) //Make sure left child is not null
        {
            processNodeInOrder(f1, root->getLeft()); //Traverse left
        }

        f1(root->getData());

        if(root->getRight() != nullptr) //Make sure right child is not null
        {
            processNodeInOrder(f1, root->getRight());   //Traverse right
        }
    }
}

template<class T>
void BST<T>::processNodePostOrder(f1Typ f1) const
{
    processNodePostOrder(f1, rootPtr);
}

template<class T>
void BST<T>::processNodePostOrder(f1Typ f1, Node<T>* root) const
{
    if(root != nullptr)
    {

        if(root->getLeft() != nullptr) //Make sure left child is not null
        {
            processNodePostOrder(root->getLeft()); //Traverse left
        }

        if(root->getRight() != nullptr) //Make sure right child is not null
        {
            processNodePostOrder(root->getRight()); //Traverse right
        }

        f1(root->getData());
    }
}

template<class T>
void BST<T>::remove(Node<T>* parent, const T &data)
{
    if(rootPtr != nullptr) //Checks if there is a tree
    {
        if(rootPtr->getData() == data) //Does root contain the data we are looking for?
        {
            removeRootMatch();
        }
        else
        {
            if(data < parent->getData() && parent->getLeft() != nullptr) //Is the value < root and does left child exist?
            {
                if(parent->getLeft()->getData() == data) //Does left child contain the data?
                {
                    removeMatch(parent, parent->getLeft(), true); //Remove if it contains the data
                }
                else
                    remove(parent->getLeft(), data); //If the data does not match, then re-call with left child
            }
            else if(data > parent->getData() && parent->getRight() != nullptr) //Is the value > root and does right child exist?
            {
                if(parent->getRight()->getData() == data) //Does right child contain the data?
                {
                    removeMatch(parent, parent->getRight(), false); //Remove if it contains data
                }
                else
                    remove(parent->getRight(), data); //If the data does not match, then re-call with Right child
            }
            else
            {
                std::cout << "could not find " << data << '\n';
            }
        }
    }
    else
        std::cout << "Cannot remove, the tree is null" << '\n';
}

template<class T>
void BST<T>::removeMatch(Node<T>* parent, Node<T>* match, bool left)
{
    if(rootPtr != nullptr)
    {
        Node<T>* delPtr;
        T matchData = match->getData();
        T smallestInRightSubTree;

        //case 0 node has 0 children
        if(match->getLeft() == nullptr && match->getRight() == nullptr)
        {
            delPtr = match;
            if(left == true) //Did the caller want to traverse left?
            {
                parent->setLeft(nullptr); //set the parents left to nullptr before node is deleted
            }
            else
            {
                parent->setRight(nullptr); //set the parents tight to nullptr if traversing right
            }

            delete delPtr;

        }
        //case 1 node has 1 child right
        else if(match->getLeft() == nullptr && match->getRight() != nullptr)
        {
            if(left == true)
            {
                parent->setLeft(match->getRight());
            }
            else
            {
                parent->setRight(match->getRight());
            }
            match->setRight(nullptr);
            delPtr = match;
            delete delPtr;

        }
        //case 1 node has 1 left right
        else if(match->getLeft() != nullptr && match->getRight() == nullptr)
        {
            if(left == true)
            {
                parent->setLeft(match->getLeft());
            }
            else
            {
                parent->setRight(match->getLeft());
            }
            match->setLeft(nullptr);
            delPtr = match;
            delete delPtr;
        }
        //case 2 node has 2 children
        else
        {
            smallestInRightSubTree = findSmallest(match->getRight()); //find smallest will find the smallest node to the the left of this node.
                                                                      //the node that is deleted will then have its data stored, and the node will be deleted.
                                                                      //once the node is deleted, the stored data will be assigned to match.

            remove(match, smallestInRightSubTree); //delete the node containing the smallest value
            match->setData(smallestInRightSubTree); //assign the from the deleted node to match.
        }
    }
    else
    {
        //tree is null
    }
}

template<class T>
void BST<T>::removeRootMatch()
{
    if(rootPtr != nullptr)
    {
        Node<T>* delPtr = rootPtr;
        T rootData = rootPtr->getData();
        T smallestInRightSubTree;

        //case 0 children
        if(rootPtr->getLeft() == nullptr && rootPtr->getRight() == nullptr)
        {
            rootPtr = nullptr;
            delete delPtr;
        }
        //case 1 child right
        else if(rootPtr->getLeft() == nullptr && rootPtr->getRight() != nullptr) //case right child
        {
            rootPtr = rootPtr->getRight(); //First right child becomes the root
            delPtr->setRight(nullptr); //Make sure delPtr is not pointing to right child
            delete delPtr; //Delete the old root
        }
        //case 1 child left
        else if(rootPtr->getLeft() != nullptr && rootPtr->getRight() == nullptr) //case right child
        {
            rootPtr = rootPtr->getLeft(); //First left child becomes the root
            delPtr->setLeft(nullptr); //Make sure delPtr is not pointing to right child
            delete delPtr; //Delete the old root
        }
        //case 2 children - Find the smallest value in the right subtree from root
        else
        {
            smallestInRightSubTree = findSmallest(rootPtr->getRight()); //find smallest value
            remove(rootPtr, smallestInRightSubTree); //Remove node where node = smallest value
            rootPtr->setData(smallestInRightSubTree); //Set the new root as the smallest in right sub tree, This maintains
            //the > and < property as everything else on the right tree must be larger
        }
    }
    else
    {
        //Tree is empty
    }
}

template<class T>
void BST<T>::remove(const T &data)
{
    if(rootPtr!=nullptr)
        remove(rootPtr, data);
}

template<class T>
T BST<T>::findSmallest(Node<T>* ptr) const
{
    if(ptr == nullptr)// is there a tree?
    {
        //tree is empty
        return ptr->getData();
    }
    else
    {
        if(ptr->getLeft() != nullptr) //Traverse down the left side of node (left always smaller)
        {
            return findSmallest(ptr->getLeft());
        }
        else //if ptr->getLeft == null means we have gotten to the bottom of the tree (lowest value)
        {
            return ptr->getData();
        }
    }
}

template<class T>
T BST<T>::findSmallest() const
{
    return findSmallest(rootPtr);
}

template<class T>
BST<T> & BST<T>::operator=( const BST<T> &other )
{
    if ( &other != this )  // for optimization purposes, check for self assignment
    {
        BST<T> temp(other);  // copy the other BST
        std::swap(temp.rootPtr, rootPtr);  // swap the root pointers
    } // temp will be deleted because out of scope

    return *this;
}

#endif //BST_H
