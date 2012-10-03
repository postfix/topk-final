/*

	vector <Node *> getChildsNodes(size_t pl,size_t pr)
	{
		vector<Node *> aux;
		size_t next_vl,next_vr;
		cst->FChild(pl,pr,&next_vl,&next_vr);
		if (next_vl == (size_t) - 1 || next_vr == (size_t) - 1)
			return aux;

		while (1)
		{
			cst->NSibling(pl, pr, &next_vl, &next_vr);
			if (next_vl == (size_t) - 1 || next_vr == (size_t) - 1)
			{
				break;
			}
			else
			{
				pl = next_vl;
				pr = next_vr;
				aux.push_back(new Node(pl,pr));
			}
		}
		return aux;
	}

	vector<size_t> getDocsIds(pl,pr)
	{
		vector<size_t> docs;
		if (pl == pr)
		{
			return docs;
		}
		else
		{
			return Nodes[pair(pl,pr)]->docs;
		}
	}


	

	class Node
{
public:
	size_t pl;
	size_t pr;
	size_t level;
	size_t position;
	Node *parent;
	Node *child;
	vector<size_t> documents;
	vector<Node *> childs;
	bool leaf;
	bool active;
	Node (size_t pl, size_t pr)
	{
		this->pl = pl;
		this->pr = pr;
	}
	Node(size_t pl,size_t pr,size_t level)
	{
		this->pl = pl;
		this->pr = pr;
		this->level = level;
		this->active = true;
	}
	Node(size_t pl,size_t pr,size_t level,size_t position)
	{
		this->pl = pl;
		this->pr = pr;
		this->level = level;
		this->position = position;
		this->active = true;
	}

	Node(size_t pl,size_t pr,size_t level,vector<size_t> docs)
	{
		this->pl = pl;
		this->pr = pr;
		this->level = level;
		this->documents = docs;
		this->active = true;
	}

	void addDocument(size_t d)
	{
		this->documents.push_back(d);
	}
	void addDocuments(vector<size_t> docs)
	{
		for (int i = 0 ; i < docs.size();i++)
		{
			for (int j = 0 ; j < this->documents.size(); j++)
			{
				if (this->documents[j] == docs[i])
					continue;
				else
					this->documents.push_back(docs[i]);		
			}
		}
	}
	void setParent(Node *p)
	{
		this->parent = p;
	}
	void addChild(Node *p)
	{
		cout << "received child with pl = " << p->pl << " and pr = " << p->pr << endl;
		this->childs.push_back(p);
	}

};

class Pointer
{
	Node * & origin;
	Node * & destination;
	size_t doc;
	vector<size_t> documents;
	size_t weight;
	size_t depth;
};





	vector<Node *> getAllSiblings(size_t pl,size_t pr)
	{
		vector<Node *> aux;
		size_t next_vl,next_vr;
		while (1)
		{
			cst->NSibling(pl, pr, &next_vl, &next_vr);
			if (next_vl == (size_t) - 1 || next_vr == (size_t) - 1)
			{
				break;
			}
			else
			{
				pl = next_vl;
				pr = next_vr;
				aux.push_back(new Node(pl,pr));
			}
		}
		return aux;
	}
	vector <Node *> getChildsDocs(size_t pl,size_t pr)
	{
		vector<Node *> aux;
		size_t next_vl,next_vr;
		cst->FChild(pl,pr,&next_vl,&next_vr);
		if (next_vl == (size_t) - 1 || next_vr == (size_t) - 1)
			return aux;

		while (1)
		{
			cst->NSibling(pl, pr, &next_vl, &next_vr);
			if (next_vl == (size_t) - 1 || next_vr == (size_t) - 1)
			{
				break;
			}
			else
			{
				pl = next_vl;
				pr = next_vr;
				aux.push_back(new Node(pl,pr));
			}
		}
		return aux;
	}

	markNode(Node *n,size_t pl,size_t pr)
	{
		vector<Node *> nodes;
		vector<Node *> childs;
		Node *n = new Node(pl,pr);
		nodes.push_back(n);
		
		while(nodes.size() != 0 )
		{
			vector<size_t> doc_node;
			vector<size_t>  docs = getChildsDocs(pl,pr);
			vector<size_t>  childs = getChildNodes(pl,pr);
			for (int i = 0 ; i < childs.size();i++)
			{
				nodes.push_back(childs[i])
			}
			for (int i = 0 ; i < docs.size; i++)
			{
				if (docs[i] > 1)
				{
					n->addDocument(docs[i]);
				}
			}
			n = nodes.pop_back();
		}
	}

*/

	
		/*
		cout << "Starting call with: " << pl << " , " << pr << endl;
		size_t next_vl,next_vr;
		if (cst->isRoot(pl,pr))
		{
			cout << "root is = " << pl << " , " << pr << endl;
			level++;
			cst->FChild(pl, pr, &next_vl, &next_vr);
			pl = next_vl;
			pr = next_vr;
			getAllNodes(cst,pl,pr,level);
		}
		size_t ns_l,ns_r;
		cst->NSibling(pl, pr, &ns_l, &ns_r);
		size_t sibling = 1;
		if (ns_l != (size_t)-1 && ns_r != (size_t)-1 )
		{
			cout << "level = " << level << " [ " << ns_l << " , " << ns_r << "]" << endl;
			while(1)
			{
				size_t ns_l_aux,ns_r_aux;
				cst->NSibling(ns_l, ns_r, &ns_l_aux, &ns_r_aux);
				if (ns_l_aux == (size_t)-1 && ns_r_aux == (size_t)-1)
				{
					break;
				}
				else
				{
					sibling ++;
					cout << "sibling = " << sibling << endl;
					ns_l = ns_l_aux;
					ns_r = ns_r_aux;
					cout << "level = " << level << " [ " << ns_l_aux << " , " << ns_r_aux << "]" << endl;
				}
			}
		}
		else
		{
				cst->FChild(pl, pr, &next_vl, &next_vr);
				if (next_vl != (size_t)-1 || next_vr != (size_t)-1)
				{
					level++;
					getAllNodes(cst,next_vl,next_vr,level);
				}
				else
				{
					return;
				}
		}*/

				/*
	vector<Node*> getLocations(char *p)
	{
		vector <Node *> result;
		size_t pl, pr, cl, cr;
		cst->Root(&pl, &pr);
		cout << "root is = " << pl << " , " << pr << endl;
		size_t sa_val;
		size_t i = 0;
		bool flag = false;
		while (p[i]){
			cout << "looking for " << p[i] << " ";
			cst->Child(pl, pr, p[i], &cl, &cr);
			cout << "child is = " << cl << " , " << cr << endl;
			if (cl == (size_t)-1 || cr == (size_t)-1)
			{
				cout << "end!" << endl;
				for (int j = 0 ; j < cst->Count(pl,pr);j++)
				{
					cout << "positions = " << cst->Locate(pl+j,pl+j) << endl;
					result.push_back(new Node(pl+j,pl+j));
				}
				flag = true;
				break;
			}
			pl = cl;
			pr = cr;
			i++;
		}
		if (flag == false)
		{
			for (int j = 0 ; j < cst->Count(pl,pr);j++)
			{
				cout << "positions = " << cst->Locate(pl+j,pl+j) << endl;
				result.push_back(new Node(pl+j,pl+j,cst->TDepth(pl+j,pl+j),cst->Locate(pl+j,pl+j)));
			}
			flag = true;
		}
		return result;
	}*/

		/*
	vector <Node *> getLeafs(size_t pl, size_t pr)
	{
		vector <Node *> aux_result = getAllNodes(pl,pr);
		vector <Node *> result;
		for (int i = 0 ; i < aux_result.size();i++)
		{
			if (aux_result[i]->pl == aux_result[i]->pr)
			{
				result.push_back(aux_result[i]);
			}
		}
		return result;
	}
*/

	/*	
	size_t k = 0;
	pair<uint,uint> aux;

	while((aux = ll->getValue(146,k)).second != 0)
	{

//		cout << " aux = " << aux.first << " ,  " << aux.second << endl;
		k++;
	}
//	cout << "aux 2 = " << aux.first << ", " << aux.second <<endl;
	//ll->listValues(9);

	/*
	SuffixTreeHandler *stp = new SuffixTreeHandler(cst,length);
	vector<Node *> testing = stp->getLocations("magico2");
	for (int i = 0 ; i < testing.size(); i++)
	{
		Node * t = testing[i];
		int j = 0;
		int doc;
		int acum = file_sizes[0];
		while (1)
		{
			cout << "file_size " << acum << " j = " << j << endl;
			if (t->position <= acum)
			{
				doc = j;
				break;
			}
				else
			{
				acum += file_sizes[j];
				j++;
			}
		}
		cout << " found at position :  " << t->position << " doc = " << doc << endl;
	}
	*/