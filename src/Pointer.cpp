class Pointer
{
	public:
		uint depth;
		pair<uint,uint>  node;
	Pointer(uint depth,pair<uint,uint> node)
	{
		this->depth = depth;
		this->node = node;
	}

};