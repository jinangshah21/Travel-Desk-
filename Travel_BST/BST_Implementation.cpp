#include "Travel_Desk_BST.cpp"

class BinaryTreeNode
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const
    {
        BinaryTreeNode *c = this->root;
        if (this->root == NULL)
            return 0;

        else
        {
            BinaryTree a;
            BinaryTree b;
            a.root = c->getLeftPtr();
            b.root = c->getRightPtr();
            return 1 + std::max(a.getHeight(), b.getHeight());
        }
    }

    int getNumberOfNodes() const
    {
        BinaryTreeNode *c = this->root;
        if (this->root == NULL)
            return 0;

        else
        {
            BinaryTree a;
            BinaryTree b;
            a.root = c->getLeftPtr();
            b.root = c->getRightPtr();
            return 1 + a.getNumberOfNodes() + b.getNumberOfNodes();
        }
    }
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        BinaryTreeNode *a = this->root;
        if (a == NULL)
            return NULL;
        while (a->getLeftPtr() != NULL)
        {
            a = a->getLeftPtr();
        }
        return a;
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        BinaryTreeNode *a = this->root;
        if (a == NULL)
            return NULL;
        while (a->getRightPtr() != NULL)
        {
            a = a->getRightPtr();
        }
        return a;
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        // return this will find the node with the given key (if it exists) or find the node with the key just larger than the given key k.
        BinaryTreeNode *a = this->root;
        while (a != NULL)
        {
            if (a->getTripNodePtr()->getDepartureTime() > key) a = a->getLeftPtr();
            else if (a->getTripNodePtr()->getDepartureTime() == key) return a;
            else a = a->getRightPtr();
        }
        return NULL;
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        if(node==NULL) return NULL;
        BinaryTreeNode *a = node->getRightPtr();
        if(a==NULL){
            if(a->getParentPtr()->getParentPtr()->getRightPtr()==a->getParentPtr()) return NULL;
            else return a->getParentPtr()->getParentPtr();
        }
        while(a->getLeftPtr()!=NULL) a=a->getLeftPtr();
        return a;
    }
    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        BinaryTreeNode *a = this->searchNodeWithKey(key);
       return this->getSuccessorNode(a);
    }
    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
         if(node==NULL) return NULL;
        BinaryTreeNode *a = node->getLeftPtr();
        if(a==NULL){
            if(a->getParentPtr()->getParentPtr()->getRightPtr()==a->getParentPtr()) return a->getParentPtr()->getParentPtr();
            else return NULL;
        }
        while(a->getRightPtr()!=NULL) a=a->getRightPtr();
        return a;
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        BinaryTreeNode *a = this->searchNodeWithKey(key);
        return this->getPredecessorNode(a);
    }
};