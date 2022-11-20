#pragma once

#include <string.h>
#include <iostream>
#include <assert.h>

using namespace std;

namespace fu
{
	class string
	{
	public:
		typedef char* iterator;

		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}

		/*string()
		{
			_size = _capacity = 0;
			_str[_size] = '\0';
		}*/

		string(const char* str="")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];

			strcpy(_str, str);
		}

		/*string(const string& s)
		string(const string& s)
		{
			_str = new char[s._capacity + 1];
			_capacity = s._capacity;
			_size = s._size;
			strcpy(_str,s._str);
		}*/

		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		string(const string& s)
			:_str(nullptr),
			_size(0),
			_capacity(0)
		{
			string tmp(s._str);
			swap(tmp);
		}

		~string()
		{
			delete[] _str;
			_size = _capacity = 0;
		}

		const char* c_str()const
		{
			return _str;
		}

		size_t size()const
		{
			return _size;
		}


		char& operator[](size_t pos)const
		{
			assert(pos < _size);
			return _str[pos];
		}

		void reserve(size_t n)//修改容量
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = n;
			}
			
		}

		void resize(size_t n, char ch = '\0')//修改size
		{
			if (n <= _size)
			{
				_size = n;
				_str[_size] = '\0';
			}
			else
			{
				reserve(n);
				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}

		void push_back(char ch)
		{
			
			if (_capacity == _size)
			{
				size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newCapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		void append(const char* str)//追加
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;
			//_str[_size] = '\0';
		}

		void clear()
		{
			_size = 0;
			_str[_size] = '\0';
		}

		/*string& operator=(const string& s)
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* tmp = new char[s._capacity + 1];
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
				_capacity = s._capacity;
				_size = s._size;
			}
			return *this;
		}*/

		/*string& operator=(const string& s)
		{
			if (this != &s)
			{
				string tmp(s);
				swap(tmp);
			}
			return *this;
		}*/

		string& operator=(string s)
		{
			swap(s);
			return *this;
		}

		string& operator+=(char ch)
		{
			push_back(ch);
			
			return *this;
		}

		string& operator+=(const char* ch) 
		{
			append(ch);

			return *this;
		}

		void pop_back()
		{
			_str[--_size] = '\0';
		}

		//string& insert(size_t pos,const char* str)
		//{
		//	size_t len = strlen(str);
		//	if (_size + len > _capacity)
		//	{
		//		reserve(_size + len);
		//	}
		//	size_t len1 = len;
		//	while (len1--)
		//	{
		//		size_t end = _size;
		//		while (end > pos)
		//		{
		//			_str[end] = _str[end - 1];
		//			--end;
		//		}
		//		_str[end] = *str;
		//		++pos;
		//		++_size;
		//	}
		//	
		//	_str[_size] = '\0';
		//	return* this;
		//}

		string& insert(size_t pos, const char* str)//插入
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			/*int end = _size;
			while (end <= (int)pos)//注意强转
			{
				_str[end + len] = _str[end];
				--end;
			}*/

			size_t end = _size + len;
			while (end > pos + len -1)
			{
				_str[end] = _str[end - len];
				--end;
			}
			strncpy(_str + pos, str, len);
			_size += len;

			return *this;
		}

		string& erase(size_t pos = 0, size_t len = npos)//删除
		{
			assert(pos < _size);

			if (pos + len >= _size || len == npos)
			{
				_size = pos;
				_str[pos] = '\0';
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			
			return *this;
		}

		size_t find(char ch, size_t pos = 0)const
		{
			assert(pos < _size);
			while (pos <= _size)
			{
				if (_str[pos] == ch)
				{
					return pos;
				}
				++pos;
			}
			return npos;
		}

		size_t find(const char* str, size_t pos = 0)const
		{
			assert(pos < _size);
			const char* ptr = strstr(_str + pos, str);
			if (ptr == nullptr)
			{
				return npos;
			}
			else
			{
				return ptr - _str;
			}
		}

		

	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		const static size_t npos = -1;
	};

	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			out << s[i];
		}
		return out;
	}

	istream& operator>>(istream& in, string& s)
	{
		s.clear();
		char buff[128] = { '\0' };
		char ch = in.get();
		size_t i = 0;
		while (ch != ' ' && ch != '\n')
		{
			if (i == 127)
			{
				s += buff;
				i = 0;
			}
			buff[i++] = ch;
			ch = in.get();
		}
		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return in;
	}

	void test1()
	{
		string s1("abcd");
		//s1.append("efg");
		s1 += "abcd";
		s1.pop_back();
		string s2("abcd");
		s2 += '1';
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		string s3;
		s3 += '1';
		cout << s3.c_str() << endl;
	}
	void test2()
	{
		string s1("abcd");
		//s1.insert(0, "a");
		s1.erase(0,3);
		cout << s1.c_str() << endl;
	}
	void test3()
	{
		string s1("abcdef");
		cout << s1.find('e') << endl;
		cout << s1.find("bcd") << endl;
	}
	void test4()
	{
		string s1("abcdefg");
		s1.resize(2);
		cout << s1.c_str() << endl;
		string s2("abcdefg");
		s2.resize(10,'a');
		cout << s2.c_str() << endl;
	}
	void test5()
	{
		string s1;
		cin >> s1;
		cout << s1 << endl;

	}

	void test6()
	{
		string s("abcde");
		string s1(s);
		string s2 = s;
		cout << s << endl;
		cout << s1 << endl;
		cout << s2 << endl;

	}
};