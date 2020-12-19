#include <iostream>
#include <sstream>

using namespace std;

enum class OutputFormat
{
	preorder,
	inorder,
	postorder
};

class Node
{
public:
	int data;
	Node* left;
	Node* right;
};

class TreeStrategy
{
public:
	virtual void start(ostringstream& oss) = 0;
	virtual void add_items(ostringstream& oss, const Node* items) = 0;
	virtual void end(ostringstream& oss) = 0;
};

class PreorderStrategy : public TreeStrategy
{
public:
	virtual void start(ostringstream& oss) override
	{
		oss << "Preorder Output\n";
	}

	virtual void add_items(ostringstream& oss, const Node* items) override
	{
		if (items != nullptr)
		{
			oss << items->data << " ";
			add_items(oss, items->left);
			add_items(oss, items->right);
		}
	}

	virtual void end(ostringstream& oss) override
	{
		oss << "\nPreorder End\n";
	}
};

class InorderStrategy : public TreeStrategy
{
public:
	virtual void start(ostringstream& oss) override
	{
		oss << "Inorder Output\n";
	}

	virtual void add_items(ostringstream& oss, const Node* items) override
	{
		if (items)
		{
			add_items(oss, items->left);
			oss << items->data << " ";
			add_items(oss, items->right);
		}
	}

	virtual void end(ostringstream& oss) override
	{
		oss << "\nInorder End\n";
	}
};

class PostorderStrategy : public TreeStrategy
{
public:
	virtual void start(ostringstream& oss) override
	{
		oss << "Postorder Output\n";
	}

	virtual void add_items(ostringstream& oss, const Node* items) override
	{
		if (items)
		{
			add_items(oss, items->left);
			add_items(oss, items->right);
			oss << items->data << " ";
		}
	}

	virtual void end(ostringstream& oss) override
	{
		oss << "\nPostorder End\n";
	}
};

class TreeProcessor
{
public:
	void print(const Node* items)
	{
		out_strategy->start(oss);
		out_strategy->add_items(oss, items);
		out_strategy->end(oss);
	}

	void set_output_format(const OutputFormat format)
	{
		oss.str("");
		switch (format)
		{
		case OutputFormat::preorder:
			out_strategy = make_unique<PreorderStrategy>();
			break;
		case OutputFormat::inorder:
			out_strategy = make_unique<InorderStrategy>();
			break;
		case OutputFormat::postorder:
			out_strategy = make_unique<PostorderStrategy>();
			break;
		}
	}

	string str() const { return oss.str(); }
private:
	ostringstream oss;
	unique_ptr<TreeStrategy> out_strategy;
};

int main()
{
	// Binary Tree 초기화
	Node nodes[16];
	for (int i = 1; i < 16; i++)
	{
		nodes[i].data = i;
		nodes[i].left = NULL;
		nodes[i].right = NULL;
	}
	for (int i = 2; i < 16; i++)
		if (i % 2 == 0)
			nodes[i / 2].left = &nodes[i];
		else
			nodes[i / 2].right = &nodes[i];

	// 출력
	TreeProcessor tp;
	// Preorder Sttrate
	tp.set_output_format(OutputFormat::preorder);
	tp.print(&nodes[1]);
	cout << tp.str() << endl;

	// Inorder Sttrate
	tp.set_output_format(OutputFormat::inorder);
	tp.print(&nodes[1]);
	cout << tp.str() << endl;

	// Postorder Sttrate
	tp.set_output_format(OutputFormat::postorder);
	tp.print(&nodes[1]);
	cout << tp.str() << endl;


	return 0;
}