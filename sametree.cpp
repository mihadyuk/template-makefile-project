#include "sametree.h"

SameTree::SameTree() {}


/*
100. Same Tree
Easy
Topics
premium lock icon
Companies
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.



Example 1:


Input: p = [1,2,3], q = [1,2,3]
Output: true
Example 2:


Input: p = [1,2], q = [1,null,2]
Output: false
Example 3:


Input: p = [1,2,1], q = [1,1,2]
Output: false


Constraints:

The number of nodes in both trees is in the range [0, 100].
-104 <= Node.val <= 104
*/


bool SameTree::isSameTree(TreeNode* p, TreeNode* q) {

    if (p == nullptr && q != nullptr)
        return false;
    if (q == nullptr && p != nullptr)
        return false;
    if (p == nullptr && q == nullptr)
        return true;
    if (p->val == q->val)
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);

    return false;
}

void SameTree::run() {

    TreeNode node_p_right = {3, 0, 0};
    TreeNode node_p_left  = {2, 0, 0};
    TreeNode node_p       = {1, &node_p_left, &node_p_right};

    TreeNode node_q_right = {3, 0, 0};
    TreeNode node_q_left  = {2, 0, 0};
    TreeNode node_q       = {1, &node_q_left, &node_q_right};

    [[maybe_unused]] auto res0 = isSameTree(&node_p, &node_q);

    TreeNode node1_p_right = {1, 0, 0};
    TreeNode node1_p_left  = {2, 0, 0};
    TreeNode node1_p       = {1, &node1_p_left, &node1_p_right};

    TreeNode node1_q_right = {2, 0, 0};
    TreeNode node1_q_left  = {1, 0, 0};
    TreeNode node1_q       = {1, &node1_q_left, &node1_q_right};

    [[maybe_unused]] auto res1 = isSameTree(&node1_p, &node1_q);

    TreeNode node2_p_left  = {2, 0, 0};
    TreeNode node2_p       = {1, &node2_p_left, nullptr};

    TreeNode node2_q_right = {2, 0, 0};
    TreeNode node2_q       = {1, nullptr, &node2_q_right};

    [[maybe_unused]] auto res2 = isSameTree(&node2_p, &node2_q);


    TreeNode node3_p_left  = {2, 0, 0};
    TreeNode node3_p       = {1, &node3_p_left, nullptr};

    TreeNode node3_q_left  = {2, 0, 0};
    TreeNode node3_q       = {1, &node3_q_left, nullptr};

    [[maybe_unused]] auto res3 = isSameTree(&node3_p, &node3_q);

    TreeNode node4_p_right = {2, 0, 0};
    TreeNode node4_p       = {1, nullptr, &node4_p_right};

    TreeNode node4_q_right = {2, 0, 0};
    TreeNode node4_q       = {1, nullptr, &node4_q_right};

    [[maybe_unused]] auto res4 = isSameTree(&node4_p, &node4_q);

    TreeNode node5_p       = {1, nullptr, nullptr};

    TreeNode node5_q       = {1, nullptr, nullptr};

    [[maybe_unused]] auto res5 = isSameTree(&node5_p, &node5_q);


    TreeNode node6_p       = {1, nullptr, nullptr};

    TreeNode node6_q       = {2, nullptr, nullptr};

    [[maybe_unused]] auto res6 = isSameTree(&node6_p, &node6_q);

}
