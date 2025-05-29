#ifndef SAMETREE_H
#define SAMETREE_H

class SameTree
{
public:
    SameTree();
    void run();
private:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    bool isSameTree(TreeNode* p, TreeNode* q);
};

#endif // SAMETREE_H
