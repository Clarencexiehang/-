#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
int flag=1;

typedef  struct Node{
    int w;
    Node *left;
    Node *right;
    bool isAdd;     //判断该结点是否已经插入Huffman树中
};

void init(Node **a,int n){
    int w;
    for(int i=0;i<n;i++){
        a[i]->left=a[i]->right=NULL;
        a[i]->isAdd= false;
        cin>>w;
        a[i]->w=w;
    }
}

bool comp(Node *a,Node *b){
    return (a->w<b->w);
}

/*
 * 因为本题的特殊性，针对头两个结点单独处理，即5,3排列的顺序
 * 对最后的根节点也单独处理
 */
Node* HuffmanTree(Node **a,int n){
    vector<Node*> tree;
    // push the Node from array "a" into vector "tree"
    for(int i=0;i<n;i++)
        tree.push_back(a[i]);

    sort(tree.begin(),tree.end(),comp);


    Node *firstIns=new Node;
    firstIns->left=tree[1];
    firstIns->right=tree[0];
    firstIns->w=tree[1]->w+tree[0]->w;
    firstIns->isAdd= true;

    //start insert
    //对第一对结点的父节点新建完毕，开始建树
    /*
     * 思路是每次在集合中将删掉上次已经插入的两个结点，
     * 插入他们构成的父节点
     * 重新对集合排序
     * 再取最小权重的结点，插入树中，进入下一次循环
     * */
    Node *ParentNode=new Node;
    for(int i=0;i<n-1;i++){
        if(tree.size()==2)  break;

        //delete the front two element and insert their parent in the tree
        tree.erase(tree.begin(),tree.begin()+2);

        if(i==0)
            tree.push_back(firstIns);
        else
            tree.push_back(ParentNode);

        //对新的容器排序
        sort(tree.begin(),tree.end(),comp);

        //排完序后再取前两位插入哈夫曼树
        Node *insNode=new Node;
        //如果第二位与第三位相比结点已经插入树中，则优先选择未插入的进行插入
        if(tree[1]->w==tree[2]->w){
            if(tree[1]->isAdd== true){
                Node *temp=tree[1];
                tree[1]=tree[2];
                tree[2]=temp;
            }
        }

        //将未插入的结点往左边插入
        if(tree[0]->isAdd==false){
            insNode->left=tree[0];
            insNode->right=tree[1];
        }else{
            insNode->left=tree[1];
            insNode->right=tree[0];
        }


        insNode->w=tree[0]->w+tree[1]->w;
        insNode->isAdd= true;

        ParentNode=insNode;
    }

    //单独对根节点处理，原理同上
    Node *rootNode=new Node;
    if(tree[0]->w<tree[1]->w){
        rootNode->left=tree[0];
        rootNode->right=tree[1];
    }else{
        rootNode->left=tree[1];
        rootNode->right=tree[0];
    }
    rootNode->w=tree[0]->w+tree[1]->w;
    return rootNode;
}

void HuffmanCoding(Node *root,int elem,string &code){
    if (root==NULL)
        return ;
    else {
        if(root->w==elem&&root->left==NULL&&root->right==NULL){
            //cout<<" 这是第"<<flag<<"次成功编码： ";flag++;
            cout<<code<<endl;
            return ;
        }else{
            string record=code;
            code.append("0");
            HuffmanCoding(root->left,elem,code);
            code=record;
            code.append("1");
            HuffmanCoding(root->right,elem,code);
            code=record;
        }

    }
}


void PreOrderTraverse(Node* root) {
    if (root) {
        cout << root->w << " ";
        PreOrderTraverse(root->left);
        PreOrderTraverse(root->right);
    }
}


int main(){
    int n;  cin>>n;
    Node **a=new Node*[n];
    for(int i=0;i<n;i++)
        a[i]=new Node;
    init(a,n);
    Node *root=new Node;
    root=HuffmanTree(a,n);
    cout<<"创建的Huffman树先序遍历为："<<endl;
    PreOrderTraverse(root);
    cout<<"\n\n\n";

    for(int i=0;i<n;i++){
        cout<<"权重为"<<a[i]->w<<"的编码--------- ";
        string code;
        HuffmanCoding(root,a[i]->w,code);
    }

    return 0;
}