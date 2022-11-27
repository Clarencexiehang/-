#include <iostream>
#include<Windows.h>
#include"tinyxml2.h"

using namespace std;
using namespace tinyxml2;


void createXml()
{
	//------------
	//����Ҫ������xml�ļ�
	//------------
	tinyxml2::XMLDocument xml;
	tinyxml2::XMLDeclaration* declaration = xml.NewDeclaration();
	xml.InsertFirstChild(declaration);

	//------------
	//�������ڵ�
	//------------
	tinyxml2::XMLElement* rootNode = xml.NewElement("computer");
	xml.InsertEndChild(rootNode);

	//------------
	//�����ӽڵ�
	//------------
	tinyxml2::XMLElement* root_1_NodeComputerMonitor = xml.NewElement("ComputerMonitor");
	tinyxml2::XMLElement* root_1_NodeKeyboard = xml.NewElement("Keyboard");
	tinyxml2::XMLElement* root_1_CPU = xml.NewElement("CPU");

	//------------
	//���ӽڵ���������
	//------------
	tinyxml2::XMLText* text_root_1_NodeComputerMonitor = xml.NewText("SAMSUNG");
	root_1_NodeComputerMonitor->InsertFirstChild(text_root_1_NodeComputerMonitor);

	tinyxml2::XMLText* text_root_1_root_1_CPU = xml.NewText("intel");
	root_1_CPU->InsertFirstChild(text_root_1_root_1_CPU);

	//------------
	//���ӽڵ���������
	//------------
	root_1_NodeComputerMonitor->SetAttribute("size", "15");
	root_1_CPU->SetAttribute("series", "XEON");

	//------------
	//�����ӽڵ���ӽڵ�
	//------------
	tinyxml2::XMLElement* root_2_NodeKeyboardAttribute = xml.NewElement("KeyboardAttribute");
	
	//------------
	//���ӽڵ���ӽڵ���������
	//------------
	tinyxml2::XMLText* text_root_2_NodeKeyboardAttribute = xml.NewText("cherry Mechanical Keyboard");
	root_2_NodeKeyboardAttribute->InsertFirstChild(text_root_2_NodeKeyboardAttribute);

	//------------
	//����xml�������ڵ���µ��ӽڵ���
	//------------
	rootNode->InsertEndChild(root_1_NodeComputerMonitor);//childNodeStu��root���ӽڵ�
	rootNode->InsertEndChild(root_1_NodeKeyboard);
	rootNode->InsertEndChild(root_1_CPU);
	//------------
	//����xml�������ڵ���µ��ӽڵ���ӽڵ���
	//------------
	root_1_NodeKeyboard->InsertEndChild(root_2_NodeKeyboardAttribute);

	//------------
	//��xml���浽��ǰ��Ŀ��
	//------------
	xml.SaveFile("computer.xml");
}
 
void deCodeXml()
{
	//------------
	//����
	//------------
	tinyxml2::XMLDocument xml;

	//------------
	//����xml�ļ�
	//------------
	if (xml.LoadFile("computer.xml") != XML_SUCCESS)
	{
		return;
	}

	//------------
	//�ҵ������xml�ĸ��ڵ�
	//------------
	tinyxml2::XMLElement* rootNode = xml.RootElement();
	if (rootNode == NULL) {
		return;
	}

	//------------
	//��ȡ��һ���ӽڵ���Ϣ���Ҵ�ӡ�ڿ���̨��
	//------------
	tinyxml2::XMLElement* root_1_NodeComputerMonitor = rootNode->FirstChildElement("ComputerMonitor");
	std::string text_root_1_NodeComputerMonitor = root_1_NodeComputerMonitor->GetText();
	cout << "text_root_1_NodeComputerMonitor = " << text_root_1_NodeComputerMonitor.c_str()<<endl;

	//------------
	//��ȡ�ڶ����ӽڵ���Ϣ���Ҵ�ӡ�ڿ���̨��
	//------------
	tinyxml2::XMLElement* root_1_NodeKeyboard = rootNode->FirstChildElement("Keyboard");
	tinyxml2::XMLElement* root_2_NodeKeyboardAttribute = root_1_NodeKeyboard->FirstChildElement("KeyboardAttribute");
	std::string text_root_2_NodeKeyboardAttribute = root_2_NodeKeyboardAttribute->GetText();
	cout << "text_root_2_NodeKeyboardAttribute = " << text_root_2_NodeKeyboardAttribute.c_str() << endl;
}

void color(short x)                   //������ɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	//SetConsoleTextAttribute()������һ��API����������ɫ�ͱ���ɫ�ĺ���
}


//��ȡXML�� �����Ԫ�ؼ���
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

//��λ/����Ԫ��
XMLElement* FindNode(string value, XMLElement* rootNode) {
	//�ݹ麯���������� 
	if (rootNode == NULL) {
		return 0;
	}

	/*�ݹ�������ҽ�㣬����˳��Ϊ�ȴ��ϵ����ٴ����ң����ȱ�����Ҷ�ӽ�㣬�ٱ���ͬ������Ҷ�ӽ�㣩*/
	XMLElement* Node = rootNode;   //��¼��ʱ�������Ľ�� 
	XMLElement* FirstNode = rootNode->FirstChildElement();   //��¼�ý���һ�����ӽ��  
	const XMLAttribute* At = rootNode->FirstAttribute();    //��¼�ý�������

	//�����ý�����ԣ���ƥ����ֱ�ӷ��أ�����ƥ����ѭ������ 
	while (At != NULL) {
		if (strcmp(At->Value(), value.c_str()) == 0) {
			cout << rootNode->FirstAttribute()->Value() << "�ѷ���" << endl;
			return rootNode;
		}
		At = At->Next();
	}


	//�ݹ� 
	//�Ե����ڶ���������ж��ӣ���Ҷ�ӽ�㣩�������ҵݹ�
	if (FirstNode == NULL) {
		rootNode = FindNode(value, rootNode->NextSiblingElement());
		return rootNode;
	}

	//�ɸ���㿪ʼ�������µݹ飬�ٴ������ҵݹ� 
	//�������� 
	if (FirstNode != NULL) {
		rootNode = FindNode(value, FirstNode);
		//��ĳ��㼰�����ж��Ӿ���ƥ�䣬���ɸý�㿪ʼ���ҵݹ� 
		if (rootNode == NULL) {
			rootNode = FindNode(value, Node->NextSiblingElement());
		}
		return rootNode;
	}
}

// ��Ԫ�� node �����Ԫ��
void addElement(XMLElement* node)
{
	int num = 0;
	color(15);
	cout << "����������: ";
	cin >> num;

	int j = 0;

	for (;j < num;j++)
	{

		string newLabelname;
		color(15);
		cout << "������Ԫ�ص����� ��";
		cin >> newLabelname;
		
		XMLElement* t = node->InsertNewChildElement(newLabelname.c_str());
		color(2);
		cout << " ��  �ѳɹ�����һ����Ԫ��  " << t->Value() << endl;
	}
}

//�޸�Ԫ�� node ������
void modify_node_name(XMLElement* node)
{
	// �޸�
	string newname;
	cout << "�����ǩ������  �� ";
	cin >> newname;

	node->SetValue(newname.c_str());
	color(2);
	cout << "�� Ԫ���޸ĳɹ���" << endl;
}

//ɾ��Ԫ�� node
void dele_xml(XMLElement* node)
{
	//��ɾ���ڵ�ĸ��ڵ�
	XMLNode* pa = node->Parent();
	pa = node->Parent()->ToElement();
	// ɾ��
	pa->DeleteChild(node);
	
	color(2);
	cout << "�� Ԫ��ɾ���ɹ���" << endl;
	return;
}


/*********** ���� **************/

// ���Ԫ�� node ������
void Add_node_at(XMLElement* node)
{
	string atname;
	string atva;
	cout << "�������������֡�ֵ :  ";
	cin >> atname >> atva;
	node->SetAttribute(atname.c_str(), atva.c_str());
	color(2);
	cout << "�� ���������ӳɹ���" << endl;
}
// ɾ��Ԫ�� node ������ atname = "atva"
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
		cout << "�� ��ɾ�����ԣ�" << endl;
	}
	else {
		color(4);
		cout << "�� Ԫ��û�ж�Ӧ������,ɾ��ʧ�ܣ�" << endl;
	}
	return;
}
// �������� atname
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
		cout << "�� ���ҵ����� " << at->Name() << "=" << at->Value() << endl;
	}
	else
	{
		color(4);
		cout << "�� Ԫ��û�ж�Ӧ������,����ʧ�ܣ�" << endl;
	}

	return;
}
// �޸Ľڵ� node ������ atname = atvalue
void Modify_node_at(XMLElement* node, string atname, string atvalue)
{
	int flag = 0;
	string new_atname, new_atva;
	color(15);
	cout << "�������Ե������֡�ֵ ��";
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
		cout << "�� ���޸����ԣ�" << endl;
		return;
	}


	else {

		color(4);
		cout << "�� �޸�ʧ�ܣ�û��������ԣ�" << endl;
		return;
	}

}


                       /************* �˵� *************/
void Main_Menu()
{
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |-------------------- ";color(1); cout << "��ѡ�������Ŀ";color(15);cout << " -------------------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |---- ";color(6);cout << "1.������� ";color(15);cout << " --- ";color(6);cout << "2.�����ļ�";color(15);cout << " --- ";color(6);cout << "3.��������";color(15);cout << " --------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
}
void Sub_Menu()
{
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |---------------------- ";color(1); cout << "��ѡ����";color(15);cout << " ---------------------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |---- ";color(6);cout << "1.�ڵ㹦�� ";color(15);cout << " --- ";color(6);cout << "2.���Թ���";color(15);cout << " --- ";color(6);cout << "3.������һ��";color(15);cout << " ------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
}
void Node_Menu()
{
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |-------------------- ";color(1); cout << "��ѡ��ڵ㹦��";color(15);cout << " -------------------|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
	color(15);cout << "                                    |-";color(6);cout << "1.����ӽڵ�";color(15);cout << "-";color(6);cout << "2.ɾ���ýڵ�";color(15);cout << "-";color(6);cout << "3.����Ԫ��";color(15);cout << "-";color(6);cout << "4.������һ��";color(15);cout << "-|" << endl;
	color(15);cout << "                                    |-------------------------------------------------------|" << endl;
}
void Attribute_Menu()
{
	color(15);cout << "                                    |----------------------------------------------------------|" << endl;
	color(15);cout << "                                    |---------------------- ";color(1); cout << "��ѡ�����Թ���";color(15);cout << " --------------------|" << endl;
	color(15);cout << "                                    |----------------------------------------------------------|" << endl;
	color(15);cout << "                                    |-";color(6);cout << "1.�������";color(15);cout << "-";color(6);cout << "2.ɾ������";color(15);cout << "-";color(6);cout << "3.��������";color(15);cout << "-";color(6);cout << "4.�޸�����";color(15);cout << "-";color(6);cout << "5.������һ��";color(15);cout << "-|" << endl;
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
		cout << "����ѡ�� ��";
		int input;
		cin >> input;

		if (input == 1)
		  {
			for (;;)
			{
				Sub_Menu();//ѡ����
				int getin;
				cout << "����ѡ�� ��";
				cin >> getin;

				if (getin == 1)
				{
					for (;;)
					{
						Node_Menu();//ѡ��ڵ㹦��
						int num1;
						cout << "����ѡ�� ��";
						cin >> num1;

						//���Ԫ��
						if (num1 == 1)
						{
						    XMLElement* locatElement = nullptr;
							cout << "���붨λԪ�ص�����ֵ ��";
							string a;
							cin >> a;

							locatElement=FindNode(a.c_str(), root);
							addElement(locatElement);

							doc.SaveFile("D:/java/src/country.xml");
						}
						//ɾ��Ԫ��
						else if (num1 == 2)
						{
							XMLElement* locatElement = nullptr;
							cout << "���붨λԪ�ص�����ֵ ��";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							dele_xml(locatElement);

							doc.SaveFile("D:/java/src/country.xml");
						}
						//����Ԫ��
						else if (num1 == 3)
						{
							XMLElement* locatElement = nullptr;
							cout << "�������Ԫ�ص�����ֵ ��";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							color(2);
							cout << "Ԫ�ز��ҳɹ� :" << endl;

							cout << locatElement->Name()<<"  ";

							//��������
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
						//ѡ�����Թ���
						Attribute_Menu();
						int num2;
						cout << "����ѡ�� ��";
						cin >> num2;
						//�������
						if (num2 == 1)//�������
						{
							XMLElement* locatElement = nullptr;
							cout << "���붨λԪ�ص�����ֵ ��";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							Add_node_at(locatElement);

							doc.SaveFile("D:/java/src/country.xml");

						}
						//ɾ������
						else if (num2 == 2)//ɾ������
						{
							XMLElement* locatElement = nullptr;
							cout << "���붨λԪ�ص�����ֵ ��";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);

							cout << "����ɾ�����Ե���������ֵ ��";
							
							string atname;
							string atva;
							cin >> atname >> atva;
							Dele_node_at(locatElement,atname,atva);

							doc.SaveFile("D:/java/src/country.xml");

						}
						//��������
						else if (num2 == 3)//��������
						{
							XMLElement* locatElement = nullptr;
							cout << "���붨λԪ�ص�����ֵ ��";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							
							cout << "����������Ե����� ��";
							string atname;
							cin >> atname;

							Seaarch_node_at(locatElement,atname);
						}
						//�޸�����
						else if (num2 == 4)//�޸�����
						{
							XMLElement* locatElement = nullptr;
							cout << "���붨λԪ�ص�����ֵ ��";
							string a;
							cin >> a;

							locatElement = FindNode(a.c_str(), root);
							cout << "������޸����Ե����֡�ֵ ��";

							string atname;
							string atva;
							cin >> atname >> atva;
							Modify_node_at(locatElement, atname,atva);

							doc.SaveFile("D:/java/src/country.xml");
						}
						//������һ��
						else break;//������һ��
					}
				}
				//������һ��
				else break;
			}
		  }
		else if (input == 2)print_xml(root);
		else break;
	}


	cout << endl << endl;
	color(4);
	cout << "�������" << endl;

	return 0;
}
