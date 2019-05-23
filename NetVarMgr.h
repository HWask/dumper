#pragma once
#include <Windows.h>
#include <unordered_map>
#include <memory>
#include <tuple>
#include <vector>
#include <string>

#include "Factory.h"

class NetVarMgr
{
private:
	class Node
	{
	public:
		std::unordered_map<std::string, std::tuple<DWORD, Type, RecvProp*>> map;
		std::vector< std::tuple<std::string, DWORD, std::shared_ptr<Node>, RecvProp*>> links;
	};

	//Depth-First-Search
	bool recSearch(std::shared_ptr<Node> pNode, std::string property, DWORD recOffset, DWORD& offset, RecvProp** recvprop)
	{
		if (pNode->map.count(property) > 0)
		{
			offset = recOffset + std::get<0>(pNode->map[property]);
			*recvprop = std::get<2>(pNode->map[property]);
			return true;
		}

		for (auto link : pNode->links)
		{
			if (std::get<0>(link) == property)
			{
				offset = recOffset + std::get<1>(link);
				*recvprop = std::get<3>(link);
				return true;
			}

			auto linkNode = std::get<2>(link);

			if (recSearch(linkNode, property, recOffset + std::get<1>(link), offset, recvprop))
				return true;
		}

		return false;
	}

	void walkTree(CClientClass* anchor)
	{
		while (anchor)
		{
			std::shared_ptr<Node> pnode = std::make_shared<Node>();
			auto recvtable = anchor->GetRecvTable();
			if (recvtable)
			{
				populateNode(recvtable, pnode);
				dump.emplace(std::string(anchor->GetName()), pnode);
			}

			anchor = anchor->GetNextClass();
		}
	}

	void populateNode(RecvTable* recvtable, std::shared_ptr<Node> node)
	{
		for (int i = 0; i < recvtable->NumProps(); i++)
		{
			auto prop = recvtable->GetProperty(i);

			if (prop->GetType() == Type::DPT_DataTable)
			{
				auto pLink = std::make_shared<Node>();
				node->links.push_back(std::make_tuple(std::string(prop->GetName()), prop->GetOffset(),
					pLink, prop));
				populateNode(prop->GetTable(), pLink);
			}
			else
				node->map.emplace(std::string(prop->GetName()), std::make_tuple(prop->GetOffset(), prop->GetType(), prop));
		}
	}
private:
	std::unordered_map<std::string, std::shared_ptr<Node>> dump;
	bool init = false;
	Factory* mpFactory;
public:
	NetVarMgr(Factory* pFactory) : mpFactory(pFactory) {}

	bool GetOffset(std::string className, std::string property, DWORD& offset)
	{
		if (!init)
		{
			auto anchor = mpFactory->m_pClient->GetAllClasses();
			walkTree(anchor);

			init = true;
		}

		if (dump.count(className) == 0)
			return false;

		RecvProp* pRecvProp;
		return recSearch(dump[className], property, 0, offset, &pRecvProp);
	}

	bool GetRecvProp(std::string className, std::string property, RecvProp** pRecvProp)
	{
		if (!init)
		{
			auto anchor = mpFactory->m_pClient->GetAllClasses();
			walkTree(anchor);

			init = true;
		}

		if (dump.count(className) == 0)
			return false;

		DWORD offset;
		return recSearch(dump[className], property, 0, offset, pRecvProp);
	}
};