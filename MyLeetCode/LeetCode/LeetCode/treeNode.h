#pragma once
#include "common.h"
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    
};
TreeNode* CreateTree(vector<int> vec)
{
    if (vec.empty())
        return nullptr;

    TreeNode* pRoot = nullptr;
    queue<TreeNode*> qu;
    
    int loc = 0;
    pRoot = new TreeNode(vec[loc++]);
    qu.push(pRoot);
    while (loc < vec.size())
    {
        TreeNode* pParent = qu.front();
        qu.pop();
        if (NIL != vec[loc])
        {
            TreeNode* pLeft = new TreeNode(vec[loc++]);
            pParent->left = pLeft;
            qu.push(pLeft);
        }
        else
            loc++;
        if (loc < vec.size() && NIL != vec[loc])
        {
            TreeNode* pRight = new TreeNode(vec[loc++]);
            pParent->right = pRight;
            qu.push(pRight);
        }
        else
            loc++;
    }

    return pRoot;

}
void PriorTravel(TreeNode * pRoot)
{
    if (!pRoot)
        return;
    cout << pRoot->val << " ";
    PriorTravel(pRoot->left);
    PriorTravel(pRoot->right);
}

void MidTravel(TreeNode* pRoot)
{
    if (!pRoot)
        return;
    
    MidTravel(pRoot->left);
    cout << pRoot->val << " ";
    MidTravel(pRoot->right);
}
void PostOrderTravel(TreeNode* pRoot)
{
    if (!pRoot)
        return;

    MidTravel(pRoot->left);
    MidTravel(pRoot->right);
    cout << pRoot->val << " ";
}
void TravelPerLevel(TreeNode * pRoot)
{
    if (!pRoot)
        return;
    queue<TreeNode*> qu;
    qu.emplace(pRoot);

    while (!qu.empty())
    {
        TreeNode* pNode = qu.front();
        qu.pop();
        cout << pNode->val << " ";
        if (pNode->left)
            qu.emplace(pNode->left);
        if (pNode->right)
            qu.emplace(pNode->right);
    }

}
bool isSameTree(TreeNode* p, TreeNode* q) {

    if (!p && !q)
        return true;
    if (!p || !q)
        return false;

    if (p->val != q->val)
        return false;

    queue<TreeNode*> q1;
    queue<TreeNode*> q2;
    q1.push(p);
    q2.push(q);

    while(!q1.empty() && !q2.empty())
    {
        TreeNode * t1 = q1.front();
        TreeNode * t2 = q2.front();
        if (t1->left
            && t2->left
            && t1->left->val == t2->left->val)
        {
               
                q1.push(t1->left);
                q2.push(t2->left);
        }
        else if ( (!t1->left && t2->left) || (t1->left && !t2->left)
                || (t1->left && t2->left && t1->left->val != t2->left->val))
        {
                return false;
        }

        if (t1->right
            && t2->right
            && t1->right->val == t2->right->val
            )
        {
                q1.push(t1->right);
                q2.push(t2->right);
        }
        else if ( (!t1->right && t2->right) || (t1->right && !t2->right)
                || (t1->right && t2->right && t1->right->val != t2->right->val))
        {
                return false;
        }
        q1.pop();
        q2.pop();

    }
    if(!q1.empty() || !q2.empty())
        return false;

    return true;
}
void depthFirstTravel(TreeNode* pRoot)
{
    if (!pRoot)
        return;
    cout << pRoot->val << " "; 
    depthFirstTravel(pRoot->left);
    depthFirstTravel(pRoot->right);

}
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int> > retVec;
    if (!root)
        return retVec;
    multimap<int, TreeNode*> lmap;
    lmap.insert(pair<int, TreeNode*>(0, root));
    size_t loc = 0;
    multimap<int, TreeNode*>::iterator iter = lmap.begin();
    while (iter != lmap.end())
    {
        TreeNode* pNode = iter->second;
        int leve = iter->first;
        cout << "Level=" << iter->first << " , val=" << pNode->val << endl;
        if (pNode->left)
        {
            
            lmap.insert(pair<int, TreeNode*>(leve + 1, pNode->left));
        }
        if (pNode->right)
        {
            lmap.insert(pair<int, TreeNode*>(leve + 1, pNode->right));
        }
        iter++;
    }
    multimap<int, TreeNode*>::reverse_iterator riter = lmap.rbegin();
    int level = -1;
    vector<int> vec;
    for (; riter != lmap.rend(); riter++)
    {
        TreeNode* pNode = riter->second;
        if (riter->first != level)
        {
            if (!vec.empty())
            {
                retVec.push_back(vec);
                vec.erase(vec.begin(), vec.end());
            }
            
            level = riter->first;
        }
        vec.push_back(pNode->val);

    }
    if (!vec.empty())
        retVec.push_back(vec);
    return retVec;

}

