#include <iostream>
#include<Windows.h>
#include"tinyxml2.h"

using namespace std;
using namespace tinyxml2;


void createXml()
{
	//------------
	//声明要创建的xml文件
	//------------
	tinyxml2::XMLDocument xml;
	tinyxml2::XMLDeclaration* declaration = xml.NewDeclaration();
	xml.InsertFirstChild(declaration);

	//------------
	//创建根节点
	//------------
	tinyxml2::XMLElement* rootNode = xml.NewElement("computer");
	xml.InsertEndChild(rootNode);

	//------------
	//创建子节点
	//------------
	tinyxml2::XMLElement* root_1_NodeComputerMonitor = xml.NewElement("ComputerMonitor");
	tinyxml2::XMLElement* root_1_NodeKeyboard = xml.NewElement("Keyboard");
	tinyxml2::XMLElement* root_1_CPU = xml.NewElement("CPU");

	//------------
	//给子节点增加内容
	//------------
	tinyxml2::XMLText* text_root_1_NodeComputerMonitor = xml.NewText("SAMSUNG");
	root_1_NodeComputerMonitor->InsertFirstChild(text_root_1_NodeComputerMonitor);

	tinyxml2::XMLText* text_root_1_root_1_CPU = xml.NewText("intel");
	root_1_CPU->InsertFirstChild(text_root_1_root_1_CPU);

	//------------
	//给子节点增加内容
	//------------
	root_1_NodeComputerMonitor->SetAttribute("size", "15");
	root_1_CPU->SetAttribute("series", "XEON");

	//------------
	//创建子节点的子节点
	//------------
	tinyxml2::XMLElement* root_2_NodeKeyboardAttribute = xml.NewElement("KeyboardAttribute");
	
	//------------
	//给子节点的子节点增加内容
	//------------
	tinyxml2::XMLText* text_root_2_NodeKeyboardAttribute = xml.NewText("cherry Mechanical Keyboard");
	root_2_NodeKeyboardAttribute->InsertFirstChild(text_root_2_NodeKeyboardAttribute);

	//------------
	//构建xml树，根节点的下的子节点树
	//------------
	rootNode->InsertEndChild(root_1_NodeComputerMonitor);//childNodeStu是root的子节点
	rootNode->InsertEndChild(root_1_NodeKeyboard);
	rootNode->InsertEndChild(root_1_CPU);
	//------------
	//构建xml树，根节点的下的子节点的子节点树
	//------------
	root_1_NodeKeyboard->InsertEndChild(root_2_NodeKeyboardAttribute);

	//------------
	//将xml保存到当前项目中
	//------------
	xml.SaveFile("computer.xml");
}
 
void deCodeXml()
{
	//------------
	//声明
	//------------
	tinyxml2::XMLDocument xml;

	//------------
	//导入xml文件
	//------------
	if (xml.LoadFile("computer.xml") != XML_SUCCESS)
	{
		return;
	}

	//------------
	//找到导入的xml的根节点
	//------------
	tinyxml2::XMLElement* rootNode = xml.RootElement();
	if (rootNode == NULL) {
		return;
	}

	//------------
	//读取第一层子节点信息并且打印在控制台上
	//------------
	tinyxml2::XMLElement* root_1_NodeComputerMonitor = rootNode->FirstChildElement("ComputerMonitor");
	std::string text_root_1_NodeComputerMonitor = root_1_NodeComputerMonitor->GetText();
	cout << "text_root_1_NodeComputerMonitor = " << text_root_1_NodeComputerMonitor.c_str()<<endl;

	//------------
	//读取第二层子节点信息并且打印在控制台上
	//------------
	tinyxml2::XMLElement* root_1_NodeKeyboard = rootNode->FirstChildElement("Keyboard");
	tinyxml2::XMLElement* root_2_NodeKeyboardAttribute = root_1_NodeKeyboard->FirstChildElement("KeyboardAttribute");
	std::string text_root_2_NodeKeyboardAttribute = root_2_NodeKeyboardAttribute->GetText();
	cout << "text_root_2_NodeKeyboardAttribute = " << text_root_2_NodeKeyboardAttribute.c_str() << endl;
}

void color(short x)                   //设置颜色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	//SetConsoleTextAttribute()函数是一个API设置字体颜色和背景色的函数
}


//读取XML， 传入根元素即可
void print_xml(XMLElement* node)
{
	color(2);
	const XMLAttribute* at = node->FirstAttribute();

	if (node->GetText() == NULL)
	{
		if (at != NULL)
		{
			cout << node->Value() << "  ";
			for (;at != NULL;at = at->Next())
			{
				cout << at->Name() << "=" << at->Value() << ' ';
			}
			cout << endl;
		}
		else cout << node->Value() << endl;
	}
	// }


	for (XMLElement* firChild = node->FirstChildElement(); firChild; firChild = firChild->NextSiblingElement())
	{
		XMLElement* t = firChild;
		if (firChild->GetText() != NULL)
		{
			const XMLAttribute* at1 = firChild->FirstAttribute();
			if (at1 != NULL)
			{
				cout << firChild->Value() << "  ";
				for (;at1 != NULL;at1 = at1->Next())
				{
					cout << firChild->Value() << "    ";
					for (;at1 != NULL;at1 = at1->Next())
					{
						cout << at1->Name() << "=" << at1->Value() << "   " << firChild->GetText() << endl;
					}
					cout << endl;
				}
			}
			else cout << firChild->Value() << "    " << firChild->GetText() << endl;

		}

		//if (!t->NoChildren())
		print_xml(t);
	}
}

//定位/查找元素
XMLElement* FindNode(string value, XMLElement* rootNode) {
	//递归函数跳出代码 
	if (rootNode == NULL) {
		return 0;
	}

	/*递归遍历查找结点，遍历顺序为先从上到下再从左到右（即先遍历到叶子结点，再遍历同级所有叶子结点）*/
	XMLElement* Node = rootNode;   //记录此时遍历到的结点 
	XMLElement* FirstNode = rootNode->FirstChildElement();   //记录该结点第一个孩子结点  
	const XMLAttribute* At = rootNode->FirstAttribute();    //记录该结点的属性

	//遍历该结点属性，若匹配则直接返回，若不匹配则循环结束 
	while (At != NULL) {
		if (strcmp(At->Value(), value.c_str()) == 0) {
			cout << rootNode->FirstAttribute()->Value() << "已返回" << endl;
			return rootNode;
		}
		At = At->Next();
	}


	//递归 
	//对倒数第二层结点的所有儿子（即叶子结点）从左至右递归
	if (FirstNode == NULL) {
		rootNode = FindNode(value, rootNode->NextSiblingElement());
		return rootNode;
	}

	//由根结点开始从上往下递归，再从左至右递归 
	//从上往下 
	if (FirstNode != NULL) {
		rootNode = FindNode(value, FirstNode);
		//当某结点及其所有儿子均不匹配，则由该结点开始向右递归 
		if (rootNode == NULL) {
			rootNode = FindNode(value, Node->NextSiblingElement());
		}
		return rootNode;
	}
}

// 给元素 node 添加子元素
void addElement(XMLElement* node)
{
	int num = 0;
	color(15);
	cout << "输入插入个数: ";
	cin >> num;

	int j = 0;

	for (;j < num;j++)
	{

		string newLabelname;
		color(15);
		cout << "输入新元素的名字 ：";
		cin >> newLabelname;
		
		XMLElement* t = node->InsertNewChildElement(newLabelname.c_str());
		color(2);
		cout << " √  已成功插入一个子元素  " << t->Value() << endl;
	}
}

//修改元素 node 的名字
void modify_node_name(XMLElement* node)
{
	// 修改
	string newname;
	cout << "输入标签新名子  ： ";
	cin >> newname;

	node->SetValue(newname.c_str());
	color(2);
	cout << "√ 元素修改成功！" << endl;
}

//删除元素 node
void dele_xml(XMLElement* node)
{
	//找删除节点的父节点
	XMLNode* pa = node->Parent();
	pa = node->Parent()->ToElement();
	// 删除
	pa->DeleteChild(node);
	
	color(2);
	cout << "√ 元素删除成功！" << endl;
	return;
}


/*********** 属性 **************/

// 添加元素 node 的属性
void Add_node_at(XMLElement* node)
{
	string atname;
	string atva;
	cout << "输入新属性名字、值 :  ";
	cin >> atname >> atva;
	node->SetAttribute(atname.c_str(), atva.c_str());
	color(2);
	cout << "√ 新属性增加成功！" << endl;
}
// 删除元素 node 的属性 atname = "atva"
void Dele_node_at(XMLElement* node, string atname, string atva)
{
	const XMLAttribute* at = node->FirstAttribute();
	if (at != NULL)
	{
		for (;at;at = at->Next())
		{
			if (strcmp(at->Name(), atname.c_str()) == 0 && strcmp(at->Value(), atva.c_str()) == 0)
				break;
		}

		node->DeleteAttribute(at->Name());
		color(2);
		cout << "√ 已删除属性！" << endl;
	}
	else {
		color(4);
		cout << "× 元素没有对应的属性,删除失败！" << endl;
	}
	return;
}
// 查找属性 atname
void Seaarch_node_at(XMLElement* node, string atname)
{
	int flag = 0;
	const XMLAttribute* at = node->FirstAttribute();
	if (at != NULL)
	{
		for (;at != NULL;at = at->Next())
		{
			if (strcmp(at->Name(), atname.c_str()) == 0)
			{
				flag = 1;
				break;
			}
		}
	}

	if (flag == 1)
	{
		color(2);
		cout << "√ 已找到属性 " << at->Name() << "=" << at->Value() << endl;
	}
	else
	{
		color(4);
		cout << "× 元素没有对应的属性,查找失败！" << endl;
	}

	return;
}
// 修改节点 node 的属性 atname = atvalue
void Modify_node_at(XMLElement* node, string atname, string atvalue)
{
	int flag = 0;
	string new_atname, new_atva;
	color(15);
	cout << "输入属性的新名字、值 ：";
	cin >> new_atname >> new_atva;
	const XMLAttribute* at = node->FirstAttribute();
	if (at != NULL)
	{
		for (;at;at = at->Next())
		{
			if (strcmp(at->Name(), atname.c_str()) == 0 && strcmp(at->Value(), atvalue.c_str()) == 0)
			{
				flag = 1;
				break;
			}
		}

		cout << at->Name() << " " << at->Value() << endl;

	}


	if (flag == 1)
	{
		//		at->SetName(new_atname.c_str());
		//		at->SetValue(new_atva.c_str());
		node->DeleteAttribute(at->Name());
		node->SetAttribute(new_atname.c_str(), new_atva.c_str());
		color(2);
		cout << "√ 已修改属性！" << endl;
		return;
	}


	else {

		color(4);
		cout << "× 修改失败，没有这个属性！" << endl;
		return;
	}

}


                       /************* 菜单 *************/
void Main_Menu()
{
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |-------------------- ";color(1); cout << "请选择操作项目";color(15);cout << " -------------------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |---- ";color(6);cout << "1.更多操作 ";color(15);cout << " --- ";color(6);cout << "2.遍历文件";color(15);cout << " --- ";color(6);cout << "3.结束程序";color(15);cout << " --------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
}
void Sub_Menu()
{
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |---------------------- ";color(1); cout << "请选择功能";color(15);cout << " ---------------------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |---- ";color(6);cout << "1.节点功能 ";color(15);cout << " --- ";color(6);cout << "2.属性功能";color(15);cout << " --- ";color(6);cout << "3.返回上一级";color(15);cout << " ------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
}
void Node_Menu()
{
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |-------------------- ";color(1); cout << "请选择节点功能";color(15);cout << " -------------------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |-";color(6);cout << "1.添加子节点";color(15);cout << "-";color(6);cout << "2.删除该节点";color(15);cout << "-";color(6);cout << "3.查找元素";color(15);cout << "-";color(6);cout << "4.返回上一级";color(15);cout << "-|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
}
void Attribute_Menu()
{
	color(15);cout << "                                    |----------------------------------------------------------|" << endl;
	color(15);cout << "                                    |---------------------- ";color(1); cout << "请选择属性功能";color(15);cout << " --------------------|" << endl;
	color(15);cout << "                                    |----------------------------------------------------------|" << endl;
	color(15);cout << "                                    |-";color(6);cout << "1.添加属性";color(15);cout << "-";color(6);cout << "2.删除属性";color(15);cout << "-";color(6);cout << "3.查找属性";color(15);cout << "-";color(6);cout << "4.修改属性";color(15);cout << "-";color(6);cout << "5.返回上一级";color(15);cout << "-|" << endl;
	color(15);cout << "                                    |----------------------------------------------------------|" << endl;
}


int main()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("D:/java/src/country.xml");

	XMLElement* root = doc.RootElement();

	for (;;)
	{
		Main_Menu();
		cout << "输入选项 ：";
		int input;
		cin >> input;

		if (input == 1)
		  {
			for (;;)
			{
				Sub_Menu();//选择功能
				int getin;
				cout << "输入选项 ：";
				cin >> getin;

				if (getin == 1)
				{
					for (;;)
					{
						Node_Menu();//选择节点功能
						int num1;
						cout << "输入选项 ：";
						cin >> num1;

						//添加元素
						if (num1 == 1)
						{
						    XMLElement* locatElement = nullptr;
							cout << "输入定位元素的属性值 ：";
							string a;
							cin >> a;

							locatElement=FindNode(a.c_str(), root);
							addElement(locatElement);

							doc.SaveFile("D:/java/src/country.xml");
						}
						//删除元素
						else if (num1 == 2)
						{
							XMLElement* locatElement = nullptr;
							cout << "输入定位元素的属性值 ：";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							dele_xml(locatElement);

							doc.SaveFile("D:/java/src/country.xml");
						}
						//查找元素
						else if (num1 == 3)
						{
							XMLElement* locatElement = nullptr;
							cout << "输入查找元素的属性值 ：";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							color(2);
							cout << "元素查找成功 :" << endl;

							cout << locatElement->Name()<<"  ";

							//遍历属性
							const XMLAttribute* at = locatElement->FirstAttribute();
							if (at != NULL)
							{
								for (;at != NULL;at = at->Next())
								{
									cout << at->Name() << "=" << at->Value()<<" | ";
								}
								cout << endl;
							}
						}

						else break;
					}
				}

				else if (getin == 2)
				{
					for (;;)
					{
						//选择属性功能
						Attribute_Menu();
						int num2;
						cout << "输入选项 ：";
						cin >> num2;
						//添加属性
						if (num2 == 1)//添加属性
						{
							XMLElement* locatElement = nullptr;
							cout << "输入定位元素的属性值 ：";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							Add_node_at(locatElement);

							doc.SaveFile("D:/java/src/country.xml");

						}
						//删除属性
						else if (num2 == 2)//删除属性
						{
							XMLElement* locatElement = nullptr;
							cout << "输入定位元素的属性值 ：";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);

							cout << "输入删除属性的属性名、值 ：";
							
							string atname;
							string atva;
							cin >> atname >> atva;
							Dele_node_at(locatElement,atname,atva);

							doc.SaveFile("D:/java/src/country.xml");

						}
						//查找属性
						else if (num2 == 3)//查找属性
						{
							XMLElement* locatElement = nullptr;
							cout << "输入定位元素的属性值 ：";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							
							cout << "输入查找属性的名字 ：";
							string atname;
							cin >> atname;

							Seaarch_node_at(locatElement,atname);
						}
						//修改属性
						else if (num2 == 4)//修改属性
						{
							XMLElement* locatElement = nullptr;
							cout << "输入定位元素的属性值 ：";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							cout << "输入待修改属性的名字、值 ：";

							string atname;
							string atva;
							cin >> atname >> atva;
							Modify_node_at(locatElement, atname,atva);

							doc.SaveFile("D:/java/src/country.xml");
						}
						//返回上一级
						else break;//返回上一级
					}
				}
				//返回上一级
				else break;
			}
		  }
		else if (input == 2)print_xml(root);
		else break;
	}


	cout << endl << endl;
	color(4);
	cout << "程序结束" << endl;

	return 0;
}
