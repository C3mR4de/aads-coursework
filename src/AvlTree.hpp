#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

namespace coursework
{
    template <typename T>
    class AvlTree
    {
    public:

        AvlTree();
        AvlTree(const AvlTree& other) = delete;
        AvlTree(AvlTree&& other);

        AvlTree& operator=(const AvlTree& other) = delete;
        AvlTree& operator=(AvlTree&& other);

    private:
    };
}

#endif // AVL_TREE_HPP
