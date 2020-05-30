#pragma once
#include <type_traits>
#include <stdint.h>
#include <memory>
#include "Pool.h"
#include "ArrayList.h"
namespace HashMapName
{
	template <typename K, typename V, typename Hash, typename Equal>
	class HashMap_Class
	{
	public:
		struct LinkNode
		{
			LinkNode* last = nullptr;
			LinkNode* next = nullptr;
			uint64 arrayIndex;
			K key;
			V value;
			LinkNode() noexcept {}
			LinkNode(uint64 arrayIndex, const K& key, const V& value)  noexcept : key(key), value(value), arrayIndex(arrayIndex) {}
			static void Add(LinkNode*& source, LinkNode* dest) noexcept
			{
				if (!source)
				{
					source = dest;
				}
				else
				{
					if (source->next)
					{
						source->next->last = dest;
					}
					dest->next = source->next;
					dest->last = source;
					source->next = dest;
				}
			}
			/*static void Remove(LinkNode*& node) noexcept
			{
				if (!node->last && !node->next)
				{
					node = nullptr;
				}
				else
				{
					if (node->last)
					{
						node->last->next = node->next;
					}
					if (node->next)
					{
						node->next->last = node->last;
					}
				}
			}*/
		};
		struct Iterator
		{
			friend class HashMap_Class<K, V, Hash, Equal>;
		private:
			const HashMap_Class* map;
			uint64 index;
			HashMap_Class::LinkNode* node;
			inline Iterator(const HashMap_Class* map, uint64 index,
				HashMap_Class::LinkNode* node) noexcept : map(map), index(index), node(node) {}
		public:
			inline bool operator==(const Iterator& a) const noexcept
			{
				return index == a.index && node == a.node;
			}

			inline bool operator != (const Iterator& a) const noexcept
			{
				return !operator==(a);
			}
			inline void operator++() noexcept;
			inline void operator++(int) noexcept
			{
				operator++();
			}
			inline K& Key() const noexcept;
			inline V& Value() const noexcept;
		};
	private:
		ArrayList<LinkNode*> allocatedNodes;
		struct HashArray
		{
		private:
			LinkNode** nodesPtr = nullptr;
			uint64 mSize;
		public:
			uint64 size() const noexcept { return mSize; }
			HashArray() noexcept : mSize(0) {}
			void ClearAll()
			{
				memset(nodesPtr, 0, sizeof(LinkNode*) * mSize);
			}
			HashArray(uint64 mSize) noexcept : mSize(mSize)
			{
				nodesPtr = (LinkNode**)malloc(sizeof(LinkNode*) * mSize);
				memset(nodesPtr, 0, sizeof(LinkNode*) * mSize);
			}
			HashArray(HashArray& arr)  noexcept :
				nodesPtr(arr.nodesPtr)
			{

				mSize = arr.mSize;
				arr.nodesPtr = nullptr;
			}
			void operator=(HashArray& arr) noexcept
			{
				nodesPtr = arr.nodesPtr;
				mSize = arr.mSize;
				arr.nodesPtr = nullptr;
			}
			void operator=(HashArray&& arr) noexcept
			{
				operator=(arr);
			}
			~HashArray() noexcept
			{
				if (nodesPtr) free(nodesPtr);
			}
			LinkNode*& operator[](uint64 i) const noexcept
			{
				return nodesPtr[i];
			}
			LinkNode*& operator[](uint64 i) noexcept
			{
				return nodesPtr[i];
			}
		};
		template <typename Func>
		void IterateAll(const Func& func)
		{
			for (uint64 i = 0; i < allocatedNodes.size(); ++i)
			{
				auto& vv = allocatedNodes[i];
				func(vv->key, vv->value);
			}
		}
		HashArray nodeVec;
		StackObject<Pool<LinkNode>> pool;
		inline static Hash hsFunc;
		inline static Equal eqFunc;
		LinkNode* GetNewLinkNode(const K& key, const V& value)
		{
			LinkNode* newNode = pool->New(allocatedNodes.size(), key, value);
			allocatedNodes.push_back(newNode);
			return newNode;
		}
		void DeleteLinkNode(LinkNode* oldNode)
		{
			auto ite = allocatedNodes.end() - 1;
			if (*ite != oldNode)
			{
				(*ite)->arrayIndex = oldNode->arrayIndex;
				allocatedNodes[oldNode->arrayIndex] = *ite;
			}
			allocatedNodes.erase(ite);
			pool->Delete(oldNode);
		}
		inline static uint64 GetPow2Size(uint64 capacity) noexcept
		{
			uint64 ssize = 1;
			while (ssize < capacity)
				ssize <<= 1;
			return ssize;
		}
		inline static uint64 GetHash(uint64 hash, uint64 size) noexcept
		{
			return hash & (size - 1);
		}
		inline static uint64 GetPrime(uint64 n) noexcept
		{
			auto isPrime = [](uint64 n)->bool
			{
				if (n % 2 == 0)
					return false;
				for (uint64 i = 3; (i * i) <= n; i += 2)
					if (n % i == 0)
						return false;
				return true;
			};
			for (; ; ++n)
			{
				if (isPrime(n))
				{
					return n;
				}
			}
		}
		void Resize(uint64 newCapacity) noexcept
		{
			uint64 capacity = nodeVec.size();
			if (capacity >= newCapacity) return;
			newCapacity = GetPow2Size(newCapacity);
			allocatedNodes.reserve(newCapacity);
			HashArray newNode(newCapacity);
			for (uint64 i = 0; i < allocatedNodes.size(); ++i)
			{
				LinkNode* node = allocatedNodes[i];
				auto next = node->next;
				node->last = nullptr;
				node->next = nullptr;
				size_t hashValue = hsFunc(node->key);
				hashValue = GetHash(hashValue, newCapacity);
				LinkNode*& targetHeaderLink = newNode[hashValue];
				if (!targetHeaderLink)
				{
					targetHeaderLink = node;
				}
				else
				{
					node->next = targetHeaderLink;
					targetHeaderLink->last = node;
					targetHeaderLink = node;
				}
			}
			nodeVec = newNode;
		}
		void Resize() noexcept
		{
			Resize(nodeVec.size() * 2);
		}
	public:
		//////////////////Construct & Destruct
		HashMap_Class(uint64 capacity) noexcept
		{
			if (capacity < 3) capacity = 3;
			capacity = GetPow2Size(capacity);
			nodeVec = HashArray(capacity);
			allocatedNodes.reserve(capacity);
			pool.New(capacity);
		}
		~HashMap_Class() noexcept
		{
			for (auto ite = allocatedNodes.begin(); ite != allocatedNodes.end(); ++ite)
			{
				pool->Delete(*ite);
			}
			pool.Delete();
		}
		HashMap_Class()  noexcept : HashMap_Class(17) {}
		///////////////////////
		void Insert(const K& key, const V& value) noexcept
		{
			size_t hashOriginValue = hsFunc(key);
			size_t hashValue = GetHash(hashOriginValue, nodeVec.size());
			for (LinkNode* node = nodeVec[hashValue]; node != nullptr; node = node->next)
			{
				if (eqFunc(node->key, key))
				{
					node->value = value;
					return;
				}

			}
			if (allocatedNodes.size() >= nodeVec.size())
			{
				Resize();
				hashValue = GetHash(hashOriginValue, nodeVec.size());
			}
			LinkNode* newNode = GetNewLinkNode(key, value);
			LinkNode::Add(nodeVec[hashValue], newNode);
		}
		void Reserve(uint64 capacity) noexcept
		{
			Resize(capacity);
		}
		Iterator Find(const K& key) const noexcept
		{
			size_t hashOriginValue = hsFunc(key);
			size_t hashValue = GetHash(hashOriginValue, nodeVec.size());
			for (LinkNode* node = nodeVec[hashValue]; node != nullptr; node = node->next)
			{
				if (eqFunc(node->key, key))
				{
					return Iterator(this, hashValue, node);
				}

			}
			return End();
		}
		void Remove(const K& key) noexcept
		{
			size_t hashOriginValue = hsFunc(key);
			size_t hashValue = GetHash(hashOriginValue, nodeVec.size());
			LinkNode*& startNode = nodeVec[hashValue];
			for (LinkNode* node = startNode; node != nullptr; node = node->next)
			{
				if (eqFunc(node->key, key))
				{
					if (startNode == node)
					{
						startNode = node->next;
					}
					if (node->next)
						node->next->last = node->last;
					if (node->last)
						node->last->next = node->next;
					DeleteLinkNode(node);
					return;
				}

			}
		}

		void Remove(const Iterator& ite) noexcept
		{
			if (nodeVec[ite.index] == ite.node)
			{
				nodeVec[ite.index] = ite.node->next;
			}
			if (ite.node->last)
				ite.node->last->next = ite.node->next;
			if (ite.node->next)
				ite.node->next->last = ite.node->last;
			DeleteLinkNode(ite.node);
		}
		V& operator[](const K& key) noexcept
		{
			size_t hashOriginValue = hsFunc(key);
			size_t hashValue = GetHash(hashOriginValue, nodeVec.size());
			for (LinkNode* node = nodeVec[hashValue]; node != nullptr; node = node->next)
			{
				if (eqFunc(node->key, key))
				{
					return node->value;
				}
			}
			return *(V*)nullptr;
		}
		bool TryGet(const K& key, V& value) const noexcept
		{
			size_t hashOriginValue = hsFunc(key);
			size_t hashValue = GetHash(hashOriginValue, nodeVec.size());
			for (LinkNode* node = nodeVec[hashValue]; node != nullptr; node = node->next)
			{
				if (eqFunc(node->key, key))
				{
					value = node->value;
					return true;
				}
			}
			return false;
		}
		bool Contains(const K& key) const noexcept
		{
			size_t hashOriginValue = hsFunc(key);
			size_t hashValue = GetHash(hashOriginValue, nodeVec.size());
			for (LinkNode* node = nodeVec[hashValue]; node != nullptr; node = node->next)
			{
				if (eqFunc(node->key, key))
				{
					return true;
				}
			}
			return false;
		}
		void Clear() noexcept
		{
			if (allocatedNodes.empty()) return;
			nodeVec.ClearAll();
			for (auto ite = allocatedNodes.begin(); ite != allocatedNodes.end(); ++ite)
			{
				pool->Delete(*ite);
			}
			allocatedNodes.clear();
		}
		uint64 Size() const noexcept { return allocatedNodes.size(); }

		uint64 GetCapacity() const noexcept { return nodeVec.size(); }
		Iterator End() const noexcept
		{
			return Iterator(this, nodeVec.size(), nullptr);
		}
		Iterator Begin() const noexcept
		{
			for (uint64 i = 0; i < nodeVec.size(); ++i)
			{
				if (nodeVec[i])
				{
					return Iterator(this, i, nodeVec[i]);
				}
			}
			return End();
		}
	};

	template <typename K, typename V, typename Hash, typename Equal>
	inline void HashMap_Class<K, V, Hash, Equal>::Iterator::operator++() noexcept
	{
		node = node->next;
		const HashArray& vec = map->nodeVec;
		while (node == nullptr)
		{
			index++;
			if (index >= vec.size())
			{
				index = vec.size();
				return;
			}
			else
			{
				node = vec[index];
			}
		}
	}
	template <typename K, typename V, typename Hash, typename Equal>
	inline K& HashMap_Class<K, V, Hash, Equal>::Iterator::Key() const noexcept
	{
		return node->key;
	}
	template <typename K, typename V, typename Hash, typename Equal>
	inline V& HashMap_Class<K, V, Hash, Equal>::Iterator::Value() const noexcept
	{
		return node->value;
	}
}

template <typename K, typename V, typename Hash = std::hash<K>, typename Equal = std::equal_to<K>>
using HashMap = typename HashMapName::HashMap_Class<
	std::remove_cv_t<K>,
	std::remove_cv_t<V>,
	std::remove_cv_t<Hash>,
	std::remove_cv_t<Equal>>;