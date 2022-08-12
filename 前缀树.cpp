// Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。
// 这一数据结构有相当多的应用情景，例如自动补完和拼写检查。
// 请你实现 Trie 类：
// Trie() 初始化前缀树对象。
// void insert(String word) 向前缀树中插入字符串 word 。
// boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
// boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

// 哈希表
#include <unordered_set>
#include <string>
using namespace std;
class Trie
{
private:
    unordered_set<string> tryTree;

public:
    Trie()
    {
    }

    void insert(string word)
    {
        if (tryTree.count(word))
            return;
        tryTree.insert(word);
    }

    bool search(string word)
    {
        if (tryTree.count(word))
            return true;
        else
            return false;
    }

    bool startsWith(string prefix)
    {
        for (auto iter = tryTree.begin(); iter != tryTree.end(); ++iter)
        {
            // 为什么*解引用不行，->可以
            size_t pos = iter->find(prefix); // string的find会返回子字符串的开头下标
            if (pos != iter->npos && pos == 0)
                return true;
        }
        return false;
    }
};

/*字典树
Trie，又称前缀树或字典树，是一棵有根树，其每个节点包含以下字段：26叉树
指向子节点的指针数组 children。对于本题而言，数组长度为 26，即小写英文字母的数量。此时 children[0] 对应小写字母 a，
children[1] 对应小写字母 b，…，children[25] 对应小写字母 z。
布尔字段 isEnd，表示该节点是否为字符串的结尾。*/
#include <vector>
class Trie
{
private:
    vector<Trie *> children;
    bool isEnd;
    Trie *searchPrefix(string prefix)
    {
        Trie *node = this;
        for (auto &c : prefix)
        {
            int id = c - 'a';
            if (!node->children[id])
            {
                return nullptr;
            }
            node = node->children[id];
        }
        return node;
    }

public:
    Trie() : children(26), isEnd(false) {} // Trie*的默认初始化为空指针
    void insert(string word)
    {
        Trie *node = this;
        for (auto &c : word)
        {
            int id = c - 'a';
            if (!node->children[id])
            {
                node->children[id] = new Trie();
            }
            node = node->children[id];
        }
        node->isEnd = true; //最后一个节点，标上结束的标志
    }
    bool search(string word)
    {
        auto node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }
    bool startsWith(string prefix)
    {
        auto node = this->searchPrefix(prefix);
        return node != nullptr;
    }
};