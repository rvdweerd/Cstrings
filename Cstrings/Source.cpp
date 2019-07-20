#include <fstream>
#include <conio.h>
#include <cmath>

namespace CRog
{
	void print(const char* s)
	{
		//char* p = s;
		/*
		while (*s != 0)
		{
			_putch(*s++);
		}
		*/

		for (; *s != 0; s++)
		{
			_putch(*s);
		}
	}

	void printFixedWidth(const char* s, const int width)
	{
		int count = 0;
		for (; (*s != 0) && (count < width); s++)
		{
			_putch(*s);
			count++;
		}
		for (; count < width; count++)
		{
			_putch(' ');
		}
	}

	void read(char* buff, int maxSize)
	{
		const char* const pEnd = buff + maxSize;
		for (char c = _getch(); (c != 13) && (buff < pEnd - 1); c = _getch(), buff++)
		{
			*buff = c;
			_putch(c);
		}
		*buff = 0;
	}

	void strcpy(char* pSource, char* pTarget)
	{
		for (; *pSource!= 0; pSource++,pTarget++)
		{
			*pTarget= *pSource;
		}
		*pTarget = 0;
	}

	int str2int(const char* const ch)
	{
		int len = 0;
		while ((*(ch + len) >= 48) && (*(ch + len) <= 57))
		{
			len++;
		}
		int total = 0;
		for (int i = len - 1; i >= 0; i--)
		{
			total += ( int(pow(10, len - i - 1))) * (*(ch + i) - int(48) );
		}
		return total;

	}

	int str2int2(const char* const ch)
	{
		// set r pointer 
		const char* r = ch;
		for (; *r >= '0' && *r <= '9'; r++);
		r--;
		// convert factored values and accumulate
		int total = 0;
		int factor = 1;
		for (; r >= ch; r--)
		{
			total += (*r - '0') * factor;
			factor *= 10;
		}
		return total;

	}

	void int2str(int n, char* ch)
	{
		int nDigits = 1;
		int factor = 1;
		//for (; n / factor >= 10; nDigits++, factor *= 10);
		while (n / factor >= 10)
		{
			nDigits++;
			factor *= 10;
		}

		int i = 0;
		for (; factor >= 1; factor /= 10, i++)
		{
			int digit = n / factor;
			ch[i] = digit + '0';
			n -= factor * digit;
		}
		ch[i] = 0;
	}

	void int2str2(int n, char* ch)
	{
		int arr[10] = { 0 };
		int nDigits = 0;
		for (; n > 0; nDigits++)
		{
			arr[nDigits] = n % 10;
			n /= 10;
		}
		//char* p = ch;
		for (int i = 0; i < nDigits; i++, ch++)
		{
			*ch = arr[nDigits - i - 1] + '0';
		}
		*ch = 0;
	}

	void strrev(char* pl)
	{
		char* pr = pl;
		for (; *(pr + 1) != 0; pr++);

		for (; pl < pr; pl++, pr--)
		{
			//std::swap(*str, *pr);
			const char temp = *pl;
			*pl = *pr;
			*pr = temp;
		}
	}

	void int2str3(int n, char* buff, int size)
	{

		char* const pStart = buff;
		char* const pEnd = buff + size;
		for (; n > 0 && (buff + 1 < pEnd) ; n /= 10 , buff++)
		{
			*buff = n % 10 + '0';
		}
		*buff = 0;
		strrev(pStart);
	}

	int fib_rec(int n)
	{
		if (n == 0)
		{
			return 0;
		}
		else if (n == 1)
		{
			return 1;
		}
		else
		{
			return fib_rec(n - 2) + fib_rec(n - 1);
		}
	}

	int fib_it(int n)
	{
		int t0 = 0;
		int t1 = 1;
		for (int i = 0; i < n; i++)
		{
			int temp = t1;
			t1 += t0;
			t0 = temp;
		}
		return t0;
	}

	void readNumber(char* ch)
	{
		print("Enter a number: ");
		read(ch, 5);
	}
}

class CData {
private:
	class Entry {
	public:
		Entry()
		{
			name[0] = 0;
			n = 0;
		}
	public:
		static constexpr int nameBufferSize = 10;
		char name[nameBufferSize];
		int n;
	};

public:
	void SetEntry(const char* p_in, const int n_in)
	{
		char* pName = &entry[nEntries].name[0];
		const char* pEnd = p_in + 10;
		for (; p_in < pEnd - 1 && *p_in != 0; p_in++, pName++)
		{
			*pName = *p_in;
		}
		*pName = 0;
		entry[nEntries].n = n_in;
		nEntries++;
	}
	void GetEntryFromUser()
	{
		CRog::print("Enter name:");
		char buff1[25];
		CRog::read(buff1, 25);
		CRog::print("\n");
		
		int val = 201;
		while (val > 200)
		{
			CRog::print("Enter value:");
			char buff2[10];
			CRog::read(buff2, 10);
			CRog::print("\n");
			val = CRog::str2int2(buff2);
			if (val > 200)
			{
				CRog::print("Value needs to be smaller than 200.\n");
			}
		}
		SetEntry(buff1,val);

	}
	void Print() const
	{
		CRog::print("\n     Beatiful Chart Bitches!\n");
		CRog::print("     -----------------------\n\n");
		for (int i = 0; i < nEntries; i++)
		{
			CRog::printFixedWidth(entry[i].name,10);
			_putch('  |');
			for (int j = 0; j < entry[i].n; j++)
			{
				_putch('=');
			}
			_putch('\n');
		}
	}
	void Save(const char* fileName) 
	{
		std::ofstream out(fileName, std::ios::binary);
		for (int i = 0; i < nEntries; i++)
		{
			out.write(reinterpret_cast<char*>(&entry[i]), sizeof(entry[i]));
		}
	}
	void Load(const char* fileName)
	{
		nEntries = 0;
		std::ifstream in(fileName , std::ios::binary);
		if (!in.good())
		{
			CRog::print("\nError: file not found..\n");
		}
		else
		{
			in.get(); in.seekg(0);
			for (int i = 0; in.good(); i++)
			{
				nEntries++;
				in.read(reinterpret_cast<char*>(&entry[i]), sizeof(entry[0]));
				//entry[0].name[2] = '0';


				in.get(); in.seekg(-1, std::ios::cur);
			}
		}
	}

private:
	static constexpr int maxNumberEntries = 50;
	Entry entry[maxNumberEntries];
	int nEntries = 0;
};

void MenuChoice(char& ch)
{
	CRog::print("\n(l)oad (s)ave (a)dd (q)uit or (p)rint\n");
	ch='0';
	while (ch != 'l' && ch != 's' && ch != 'a' && ch != 'q' && ch  != 'p')
	{
		//CRog::read(&input, 1);
		ch = _getch();
	}
	//ch[1] = 0;
}

int main()
{
	CData dbase;
	
	char ch='0';
	while (ch != 'q')
	{
		MenuChoice(ch);
		char fileName[25];
		switch (ch)
		{
			case 'p':
				dbase.Print();
				break;
			case 'a':
				dbase.GetEntryFromUser();
				break;
			case 's':
				CRog::print("\nFilename: ");
				CRog::read(fileName, 25);
				dbase.Save(fileName);
				break;
			case 'l':
				CRog::print("\nFilename: ");
				CRog::read(fileName, 25);
				dbase.Load(fileName);
				break;
		}
	}
	
	//while (!_kbhit());
	return 0;
}