// 序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，
// 同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
// 请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，
// 你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
// 提示: 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。
// 你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。
#include <string>
#include <list>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
/*
使用序列化的结果按照先序遍历输出字符串，
反序列化根据前序遍历和中序遍历（如果中序遍历的字符串中有null的话，不需要中序遍历）
本题可以保存null时，不需要前序遍历
使用list的好处是，可以频繁的插入删除，并且删除就自动清除了内存

本题流程：
    序列化：广度优先搜索或者深度优先搜索，先序遍历保存结果在字符串中
    反序列化：1.将整体的字符串按照‘，’拆分成子字符串，封装在链表中
             2.按照链表，恢复二叉树，注意None的情况
*/
class Codec
{
public:
    // dfs
    void dfs(TreeNode *root, string &str) // 注意递归需要传引用
    {
        if (!root)
        {
            str += "None,";
            return;
        }
        else
        {
            str += to_string(root->val) + ","; // to_string将字符串转变为数字
            dfs(root->left, str);
            dfs(root->right, str);
        }
    }
    string serialize(TreeNode *root)
    {
        string str;
        dfs(root, str);
        return str;
    }
    //根据链表字符串，还原树结构
    TreeNode *rdeserialize(list<string> &listData)
    {
        if (listData.front() == "None")
        {
            listData.pop_front();
            return nullptr;
        }
        int num = stoi(listData.front());
        listData.pop_front();
        TreeNode *root = new TreeNode(num);
        root->left = rdeserialize(listData);
        root->right = rdeserialize(listData);
        return root;
    }
    // 将字符串拆成拆分数字(字符)
    TreeNode *deserialize(string data)
    {
        list<string> listData;
        string str;
        // 一个字符一个字符的读入
        for (auto &ch : data)
        {
            if (ch == ',')
            {
                listData.push_back(str);
                str.clear();
            }
            else
            {
                str += ch;
            }
        }
        if (!data.empty())
        {
            listData.push_back(str);
        }
        return rdeserialize(listData);
    }
};
