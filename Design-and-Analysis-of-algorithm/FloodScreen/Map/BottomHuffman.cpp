#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
int flag=1;

typedef  struct Node{
    int w;
    Node *left;
    Node *right;
    bool isAdd;     //�жϸý���Ƿ��Ѿ�����Huffman����
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
 * ��Ϊ����������ԣ����ͷ������㵥��������5,3���е�˳��
 * �����ĸ��ڵ�Ҳ��������
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
    //�Ե�һ�Խ��ĸ��ڵ��½���ϣ���ʼ����
    /*
     * ˼·��ÿ���ڼ����н�ɾ���ϴ��Ѿ������������㣬
     * �������ǹ��ɵĸ��ڵ�
     * ���¶Լ�������
     * ��ȡ��СȨ�صĽ�㣬�������У�������һ��ѭ��
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

        //���µ���������
        sort(tree.begin(),tree.end(),comp);

        //���������ȡǰ��λ�����������
        Node *insNode=new Node;
        //����ڶ�λ�����λ��Ƚ���Ѿ��������У�������ѡ��δ����Ľ��в���
        if(tree[1]->w==tree[2]->w){
            if(tree[1]->isAdd== true){
                Node *temp=tree[1];
                tree[1]=tree[2];
                tree[2]=temp;
            }
        }

        //��δ����Ľ������߲���
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

    //�����Ը��ڵ㴦��ԭ��ͬ��
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
            //cout<<" ���ǵ�"<<flag<<"�γɹ����룺 ";flag++;
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
    cout<<"������Huffman���������Ϊ��"<<endl;
    PreOrderTraverse(root);
    cout<<"\n\n\n";

    for(int i=0;i<n;i++){
        cout<<"Ȩ��Ϊ"<<a[i]->w<<"�ı���--------- ";
        string code;
        HuffmanCoding(root,a[i]->w,code);
    }

    return 0;
}